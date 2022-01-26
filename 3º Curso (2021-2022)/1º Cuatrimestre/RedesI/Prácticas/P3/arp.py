'''
    arp.py
    Implementación del protocolo ARP y funciones auxiliares que permiten realizar resoluciones de direcciones IP.
    Autor: Javier Ramos <javier.ramos@uam.es>
    2019 EPS-UAM
'''



from ethernet import *
import logging
import socket
import struct
import fcntl
import time
from threading import Lock
from expiringdict import ExpiringDict

#Semáforo global 
globalLock =Lock()
#Dirección de difusión (Broadcast)
broadcastAddr = bytes([0xFF]*6)
#Cabecera ARP común a peticiones y respuestas. Específica para la combinación Ethernet/IP
ARPHeader = bytes([0x00,0x01,0x08,0x00,0x06,0x04])
#longitud (en bytes) de la cabecera común ARP
ARP_HLEN = 6

#Variable que alamacenará que dirección IP se está intentando resolver
requestedIP = None
#Variable que alamacenará que dirección MAC resuelta o None si no se ha podido obtener
resolvedMAC = None
#Variable que alamacenará True mientras estemos esperando una respuesta ARP
awaitingResponse = False

#Variable para proteger la caché
cacheLock = Lock()
#Caché de ARP. Es un diccionario similar al estándar de Python solo que eliminará las entradas a los 10 segundos
cache = ExpiringDict(max_len=100, max_age_seconds=10)



def getIP(interface:str) -> int:
    '''
        Nombre: getIP
        Descripción: Esta función obtiene la dirección IP asociada a una interfaz. Esta funció NO debe ser modificada
        Argumentos:
            -interface: nombre de la interfaz
        Retorno: Entero de 32 bits con la dirección IP de la interfaz
    '''
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ip = fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', (interface[:15].encode('utf-8')))
    )[20:24]
    s.close()
    return struct.unpack('!I',ip)[0]

def printCache()->None:
    '''
        Nombre: printCache
        Descripción: Esta función imprime la caché ARP
        Argumentos: Ninguno
        Retorno: Ninguno
    '''
    print('{:>12}\t\t{:>12}'.format('IP','MAC'))
    with cacheLock:
        for k in cache:
            if k in cache:
                print ('{:>12}\t\t{:>12}'.format(socket.inet_ntoa(struct.pack('!I',k)),':'.join(['{:02X}'.format(b) for b in cache[k]])))



def processARPRequest(data:bytes,MAC:bytes)->None:
    '''
        Nombre: processARPRequest
        Decripción: Esta función procesa una petición ARP. Esta función debe realizar, al menos, las siguientes tareas:
            -Extraer la MAC origen contenida en la petición ARP
            -Si la MAC origen de la trama ARP no es la misma que la recibida del nivel Ethernet retornar
            -Extraer la IP origen contenida en la petición ARP
            -Extraer la IP destino contenida en la petición ARP
            -Comprobar si la IP destino de la petición ARP es la propia IP:
                -Si no es la propia IP retornar
                -Si es la propia IP:
                    -Construir una respuesta ARP llamando a createARPReply (descripción más adelante)
                    -Enviar la respuesta ARP usando el nivel Ethernet (sendEthernetFrame)
        Argumentos:
            -data: bytearray con el contenido de la trama ARP (después de la cabecera común)
            -MAC: dirección MAC origen extraída por el nivel Ethernet
        Retorno: Ninguno
    '''
    senderETH = data[2:8]
    if(MAC != senderETH): #si no concuerdan los valores de la trama ARP y Ethernet
        return
    senderIP = data[8:12] #ip origen
    #targetETH = dataSinCabecera[12:18] no necesario, tendrá la dirección nula
    targetIP = data[18:22] #ip destino
    if(targetIP != myIP.to_bytes(4, byteorder='big')): #compruebo si está preguntando por mi :3
        return
    request = createARPReply(senderIP, senderETH) #si es la propia construir una respuesta ARP llamando a createARPReply
    sendEthernetFrame(request, len(request), 0x0806, senderETH) #mando un paquete ethernet con la respuesta

def processARPReply(data:bytes,MAC:bytes)->None:
    '''
        Nombre: processARPReply
        Decripción: Esta función procesa una respuesta ARP. Esta función debe realizar, al menos, las siguientes tareas:
            -Extraer la MAC origen contenida en la petición ARP
            -Si la MAC origen de la trama ARP no es la misma que la recibida del nivel Ethernet retornar
            -Extraer la IP origen contenida en la petición ARP
            -Extraer la MAC destino contenida en la petición ARP
            -Extraer la IP destino contenida en la petición ARP
            -Comprobar si la IP destino de la petición ARP es la propia IP:
                -Si no es la propia IP retornar
                -Si es la propia IP:
                    -Comprobar si la IP origen se corresponde con la solicitada (requestedIP). Si no se corresponde retornar
                    -Copiar la MAC origen a la variable global resolvedMAC
                    -Añadir a la caché ARP la asociación MAC/IP.
                    -Cambiar el valor de la variable awaitingResponse a False
                    -Cambiar el valor de la variable requestedIP a None
        Las variables globales (requestedIP, awaitingResponse y resolvedMAC) son accedidas concurrentemente por la función ARPResolution y deben ser protegidas mediante un Lock.
        Argumentos:
            -data: bytearray con el contenido de la trama ARP (después de la cabecera común)
            -MAC: dirección MAC origen extraída por el nivel Ethernet
        Retorno: Ninguno
    '''
    global requestedIP,resolvedMAC,awaitingResponse,cache
    senderETH = data[2:8]
    if(MAC != senderETH): #si no concuerdan los valores de la trama ARP y Ethernet
        return
    senderIP = data[8:12] #ip origen
    targetIP = data[18:22] #ip destino
    targetETH = data[12:18] #mac destino
    if(targetIP != myIP.to_bytes(4, byteorder='big')): #si soy la ip destino es decir me han respondido
        return
        
    with globalLock:
        if(requestedIP != int.from_bytes(senderIP, byteorder='big')): #compruebo si la ip solicitada es la ip origen
            return
        resolvedMAC = senderETH #copio la MAC origen en la variable resolvedMAC
        awaitingResponse = False #ya no espera respuesta pq ya la tiene
        with cacheLock:
            cache[requestedIP] = resolvedMAC #pongo el valor en la cache
        
        requestedIP = None #pongo la requested ip a none para que se pueda volver a hacer otra solicitud ARP 



def createARPRequest(ip:int) -> bytes:
    '''
        Nombre: createARPRequest
        Descripción: Esta función construye una petición ARP y devuelve la trama con el contenido.
        Argumentos: 
            -ip: dirección a resolver 
        Retorno: Bytes con el contenido de la trama de petición ARP
    '''

    global myMAC,myIP
    frame = bytes()
    #ponemos la cabecera del ARP
    frame += ARPHeader
    frame += bytes([0x00, 0x01]) #opcode, en este caso petición (Request) este campo vale 0x0001
    frame +=myMAC #Dirección Ethernet del emisor del paquete ARP.
    frame += myIP.to_bytes(4, byteorder='big') #Dirección IP del emisor del paquete ARP.
    frame += bytes([0x00]*6)#Dirección Ethernet del receptor del paquete ARP. [dirección nula (6 bytes a 0) ya que no se conoce cuál]
    frame += ip.to_bytes(4, byteorder='big')
    return frame

    
def createARPReply(IP:int ,MAC:bytes) -> bytes:
    '''
        Nombre: createARPReply
        Descripción: Esta función construye una respuesta ARP y devuelve la trama con el contenido.
        Argumentos: 
            -IP: dirección IP a la que contestar
            -MAC: dirección MAC a la que contestar
        Retorno: Bytes con el contenido de la trama de petición ARP
    '''
    global myMAC,myIP
    frame = bytes()
    frame += ARPHeader
    frame += bytes([0x00, 0x02]) #opcode, en este caso petición (Reply) este campo vale 0x0002
    frame +=myMAC #Dirección Ethernet del emisor del paquete ARP.
    frame += myIP.to_bytes(4, byteorder='big') #Dirección IP del emisor del paquete ARP.
    frame += MAC #dirección mac del receptor
    #frame += IP.to_bytes(4, byteorder='big')
    frame += IP
    return frame


def process_arp_frame(us:ctypes.c_void_p,header:pcap_pkthdr,data:bytes,srcMac:bytes) -> None:
    '''
        Nombre: process_arp_frame
        Descripción: Esta función procesa las tramas ARP. 
            Se ejecutará por cada trama Ethenet que se reciba con Ethertype 0x0806 (si ha sido registrada en initARP). 
            Esta función debe realizar, al menos, las siguientes tareas:
                -Extraer la cabecera común de ARP (6 primeros bytes) y comprobar que es correcta
                -Extraer el campo opcode
                -Si opcode es 0x0001 (Request) llamar a processARPRequest (ver descripción más adelante)
                -Si opcode es 0x0002 (Reply) llamar a processARPReply (ver descripción más adelante)
                -Si es otro opcode retornar de la función
                -En caso de que no exista retornar
        Argumentos:
            -us: Datos de usuario pasados desde la llamada de pcap_loop. En nuestro caso será None
            -header: cabecera pcap_pktheader
            -data: array de bytes con el contenido de la trama ARP
            -srcMac: MAC origen de la trama Ethernet que se ha recibido
        Retorno: Ninguno
    '''
    cabecera = data[0:ARP_HLEN] #recogemos los valores de la cabecera
    if(cabecera != ARPHeader): #si no se trata de una cabecera de tipo ARP
        return
    dataSinCabecera = data[ARP_HLEN:]
    opcode = dataSinCabecera[0:2] 
    if(opcode == bytes([0x00, 0x01])): #si recibe una de tipo ARPRequest
        processARPRequest(dataSinCabecera, srcMac)
    elif(opcode == bytes([0x00, 0x02])): #si recibe una de tipo ARPReply
        processARPReply(dataSinCabecera, srcMac)
    else: #si no es ninguna de las dos
        return



def initARP(interface:str) -> int:
    '''
        Nombre: initARP
        Descripción: Esta función construirá inicializará el nivel ARP. Esta función debe realizar, al menos, las siguientes tareas:
            -Registrar la función del callback process_arp_frame con el Ethertype 0x0806
            -Obtener y almacenar la dirección MAC e IP asociadas a la interfaz especificada
            -Realizar una petición ARP gratuita y comprobar si la IP propia ya está asignada. En caso positivo se debe devolver error.
            -Marcar la variable de nivel ARP inicializado a True
    '''
    global myIP,myMAC,arpInitialized
    #TODO implementar aquí
    if('arpInitialized' in globals() and arpInitialized is True):
        return -1
    myIP = getIP(interface)
    myMAC = getHwAddr(interface)
    #llamamos a la función de ethernet para regustrar el callback
    registerCallback(process_arp_frame, 0x0806)
    #realizar petición ARP gratuita
    if (ARPResolution(myIP) is not None): #busco la MAC asociada a mi IP, si responde alguien, esa IP está ocupada 
        return -1 #error, alguien en la red ya tiene mi IP -\(-_-)/-
    arpInitialized = True #pongo a true el arp initialized
    return 0 #todo bien, todo correcto y yo que me alegro

def ARPResolution(ip:int) -> bytes:
    '''
        Nombre: ARPResolution
        Descripción: Esta función intenta realizar una resolución ARP para una IP dada y devuelve la dirección MAC asociada a dicha IP 
            o None en caso de que no haya recibido respuesta. Esta función debe realizar, al menos, las siguientes tareas:
                -Comprobar si la IP solicitada existe en la caché:
                -Si está en caché devolver la información de la caché
                -Si no está en la caché:
                    -Construir una petición ARP llamando a la función createARPRequest (descripción más adelante)
                    -Enviar dicha petición
                    -Comprobar si se ha recibido respuesta o no:
                        -Si no se ha recibido respuesta reenviar la petición hasta un máximo de 3 veces. Si no se recibe respuesta devolver None
                        -Si se ha recibido respuesta devolver la dirección MAC
            Esta función necesitará comunicarse con el la función de recepción (para comprobar si hay respuesta y la respuesta en sí) mediante 3 variables globales:
                -awaitingResponse: indica si está True que se espera respuesta. Si está a False quiere decir que se ha recibido respuesta
                -requestedIP: contiene la IP por la que se está preguntando
                -resolvedMAC: contiene la dirección MAC resuelta (en caso de que awaitingResponse) sea False.
            Como estas variables globales se leen y escriben concurrentemente deben ser protegidas con un Lock
    '''
    global requestedIP,awaitingResponse,resolvedMAC
    #TODO implementar aquí
    if('arpInitialized' in globals() and arpInitialized is True): #si pude inicializar el arp (por temas del arp gratuito y tal)
        if(ip == myIP): #si estoy preguntando por mi mismo
            with cacheLock:
                cache[ip] = myMAC
            return myMAC #mando mi mac
    #si pregunto por otro que está ya en la cache
    with cacheLock:
        if(ip in cache): #compruebo si la ip está en la cache
            return cache[ip] #retorno la MAC asociada en la ip mediante la cache
    request = createARPRequest(ip)
    with globalLock: #solicito el semáforo dado que voy a modificar variables globales
        #cuando tenga acceso se ejecuta esta parte
        awaitingResponse = True #voy a esperar una respuesta
        requestedIP = ip #quiero esta ip
        resolvedMAC = 0 #simplemente para debugear


    for i in range(3): #tres intentos para recibir respuesta
        #mando la petición al nivel de enlace (mando la petición, ethertype el de ARP y la dirección broadcast para que todos respondan)
        sendEthernetFrame(request,len(request), 0x0806, broadcastAddr) #mando la petición para que me resondan con la MAC de esa ip
        time.sleep(0.1)#un tiempo de espera para que puedan responder
        with globalLock:
            if awaitingResponse is False: #si alguien me respondió
                return resolvedMAC #devuelvo la respuesta recibida
    #si no hay respuesta en los 3 intentos
    return None
