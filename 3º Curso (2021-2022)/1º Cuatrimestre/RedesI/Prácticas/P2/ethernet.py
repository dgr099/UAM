'''
    ethernet.py
    Implementación del nivel Ethernet y funciones auxiliares para el envío y recepción de tramas Ethernet
    Autor: Javier Ramos <javier.ramos@uam.es>
    2019 EPS-UAM
'''

from rc1_pcap import *
import logging
import socket
import struct
from binascii import hexlify
import struct 
import threading 
#Tamaño máximo de una trama Ethernet (para las prácticas)
ETH_FRAME_MAX = 1514
#Tamaño mínimo de una trama Ethernet
ETH_FRAME_MIN = 60
PROMISC = 1
NO_PROMISC = 0
TO_MS = 10
#Dirección de difusión (Broadcast)
broadcastAddr = bytes([0xFF]*6)
#Diccionario que alamacena para un Ethertype dado qué función de callback se debe ejecutar
upperProtos = {}

def getHwAddr(interface:str):
    '''
        Nombre: getHwAddr
        Descripción: Esta función obtiene la dirección MAC asociada a una interfaz
        Argumentos:
            -interface: Cadena con el nombre de la interfaz
        Retorno:
            -Dirección MAC de la itnerfaz
    '''
    s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
    s.bind((interface,0))
    mac =  (s.getsockname()[4])
    s.close()
    return mac


def process_Ethernet_frame(us:ctypes.c_void_p,header:pcap_pkthdr,data:bytes) -> None:
    '''
        Nombre: process_Ethernet_frame
        Descripción: Esta función se ejecutará cada vez que llegue una trama Ethernet. 
            Esta función debe realizar, al menos, las siguientes tareas:
                -Extraer los campos de dirección Ethernet destino, origen y ethertype
                -Comprobar si la dirección destino es la propia o la de broadcast. En caso de que la trama no vaya en difusión o no sea para nuestra interfaz la descartaremos (haciendo un return).
                -Comprobar si existe una función de callback de nivel superior asociada al Ethertype de la trama:
                    -En caso de que exista, llamar a la función de nivel superior con los parámetros que corresponde:
                        -us (datos de usuario)
                        -header (cabecera pcap_pktheader)
                        -payload (datos de la trama excluyendo la cabecera Ethernet)
                        -dirección Ethernet origen
                    -En caso de que no exista retornar
        Argumentos:
            -us: datos de usuarios pasados desde pcap_loop (en nuestro caso será None)
            -header: estructura pcap_pkthdr que contiene los campos len, caplen y ts.
            -data: bytearray con el contenido de la trama Ethernet
        Retorno:
            -Ninguno
    ''' 
    dest = data[0:6] #los primeros 6 bytes de data se corresponden al destino
    origin = data[6:12] #los siguientes 6 bytes corresponden al origen
    ethertype = data[12:14] #finalmente 2 bytes del ethertype 
    if(dest == broadcastAddr or dest == macAddress): #si es para direccion de broadcast o para mi
        ethertypeInt = int.from_bytes(ethertype, byteorder='big')
        if(ethertypeInt in upperProtos):
            return upperProtos[ethertypeInt](us, header, data[14:], origin)

    return #si no es paramua :(
    #TODO: Implementar aquí el código que procesa una trama Ethernet en recepción
    

def process_frame(us:ctypes.c_void_p,header:pcap_pkthdr,data:bytes) -> None:
    '''
        Nombre: process_frame
        Descripción: Esta función se pasa a pcap_loop y se ejecutará cada vez que llegue una trama. La función
        ejecutará la función process_Ethernet_frame en un hilo nuevo para evitar interbloqueos entre 2 recepciones
        consecutivas de tramas dependientes. Esta función NO debe modifciarse
        Argumentos:
            -us: datos de usuarios pasados desde pcap_loop (en nuestro caso será None)
            -header: estructura pcap_pkthdr que contiene los campos len, caplen y ts.
            -data: bytearray con el contenido de la trama Ethernet
        Retorno:
            -Ninguno
    '''
    threading.Thread(target=process_Ethernet_frame,args=(us,header,data)).start()


class rxThread(threading.Thread): 
    ''' Clase que implementa un hilo de recepción. De esta manera al iniciar el nivel Ethernet
        podemos dejar un hilo con pcap_loop que reciba los paquetes sin bloquear el envío.
        En esta clase NO se debe modificar código
    '''
    def __init__(self): 
        threading.Thread.__init__(self) 
              
    def run(self): 
        global handle
        #Ejecuta pcap_loop. OJO: handle debe estar inicializado con el resultado de pcap_open_live
        if handle is not None:
            pcap_loop(handle,-1,process_frame,None)
    def stop(self):
        global handle
        #Para la ejecución de pcap_loop
        if handle is not None:
            pcap_breakloop(handle)



   

def registerCallback(callback_func: Callable[[ctypes.c_void_p,pcap_pkthdr,bytes],None], ethertype:int) -> None:
    '''
        Nombre: registerCallback
        Descripción: Esta función recibirá el nombre de una función y su valor de ethertype asociado y añadirá en la tabla 
            (diccionario) de protocolos de nivel superior el dicha asociación. 
            Este mecanismo nos permite saber a qué función de nivel superior debemos llamar al recibir una trama de determinado tipo. 
            Por ejemplo, podemos registrar una función llamada process_IP_datagram asociada al Ethertype 0x0800 y otra llamada process_arp_packet 
            asocaida al Ethertype 0x0806. 
        Argumentos:
            -callback_fun: función de callback a ejecutar cuando se reciba el Ethertype especificado. 
                La función que se pase como argumento debe tener el siguiente prototipo: funcion(us,header,data,srcMac)
                Dónde:
                    -us: son los datos de usuarios pasados por pcap_loop (en nuestro caso este valor será siempre None)
                    -header: estructura pcap_pkthdr que contiene los campos len, caplen y ts.
                    -data: payload de la trama Ethernet. Es decir, la cabecera Ethernet NUNCA se pasa hacia arriba.
                    -srcMac: dirección MAC que ha enviado la trama actual.
                La función no retornará nada. Si una trama se quiere descartar basta con hacer un return sin valor y dejará de procesarse.
            -ethertype: valor de Ethernetype para el cuál se quiere registrar una función de callback.
        Retorno: Ninguno 
    '''
    global upperProtos
    upperProtos[ethertype] = callback_func
    #upperProtos es el diccionario que relaciona función de callback y ethertype

def startEthernetLevel(interface:str) -> int:
    '''
        Nombre: startEthernetLevel
        Descripción: Esta función recibe el nombre de una interfaz de red e inicializa el nivel Ethernet. 
            Esta función debe realizar , al menos, las siguientes tareas:
                -Comprobar si el nivel Ethernet ya estaba inicializado (mediante una variable global). Si ya estaba inicializado devolver -1.
                -Obtener y almacenar en una variable global la dirección MAC asociada a la interfaz que se especifica
                -Abrir la interfaz especificada en modo promiscuo usando la librería rc1-pcap
                -Arrancar un hilo de recepción (rxThread) que llame a la función pcap_loop. 
                -Si todo es correcto marcar la variable global de nivel incializado a True
        Argumentos:
            -Interface: nombre de la interfaz sobre la que inicializar el nivel Ethernet
        Retorno: 0 si todo es correcto, -1 en otro caso
    '''
    global macAddress,handle,levelInitialized,recvThread
    handle = None
    #TODO: implementar aquí la inicialización de la interfaz y de las variables globales
    if('levelInitialized' in globals() and levelInitialized is True):
        return -1;
    macAddress = getHwAddr(interface) #obtenemos nuestra dirección mac
    errbuf = bytearray() #inicializamos el buffer para indicar errores
    handle = pcap_open_live(interface, ETH_FRAME_MAX, PROMISC, TO_MS, errbuf)
    if (handle is None): #abrimos la traza para captura en vivo con los valores dados
            logging.error('Error en la apertura de la interfaz') #si da error se lo hacemos saber
            print(errbuf) #imprimimos el mensaje de error
            return -1
    #Una vez hemos abierto la interfaz para captura y hemos inicializado las variables globales (macAddress, handle y levelInitialized) arrancamos
    #el hilo de recepción
    recvThread = rxThread() #creamos hilo
    recvThread.daemon = True
    recvThread.start() #iniciamos el hilo
    levelInitialized = True #actualizamos el valor de la variable de levelInitialized
    return 0

def stopEthernetLevel()->int:
    global macAddress,handle,levelInitialized,recvThread
    '''
        Nombre: stopEthernetLevel
        Descripción_ Esta función parará y liberará todos los recursos necesarios asociados al nivel Ethernet. 
            Esta función debe realizar, al menos, las siguientes tareas:
                -Parar el hilo de recepción de paquetes 
                -Cerrar la interfaz (handle de pcap)
                -Marcar la variable global de nivel incializado a False
        Argumentos: Ninguno
        Retorno: 0 si todo es correcto y -1 en otro caso
    '''
    if(levelInitialized is False): #compruebo que esté inicializado
        return -1

    #procedo a parar el hilo
    if (recvThread is not None): #compruebo que exista hilo
        recvThread.stop() #paro el hilo
    else:
        return -1 #si no existe hilo algo raro pasó pq se inicializa en el start y el levelInitialized está a 1
    if(handle is not None): #lo mismo comprobamos el handle
        pcap.close(handle) #cerramos el handle
    else:
        return -1
    levelInitialized = False #ponemos el inicializado a 0
    return 0 #retornamos ok
    
def sendEthernetFrame(data:bytes,length:int,etherType:int,dstMac:bytes) -> int:
    '''
        Nombre: sendEthernetFrame
        Descripción: Esta función construirá una trama Ethernet con lo datos recibidos y la enviará por la interfaz de red. 
            Esta función debe realizar, al menos, las siguientes tareas:
                -Construir la trama Ethernet a enviar (incluyendo cabecera + payload). Los campos propios (por ejemplo la dirección Ethernet origen) 
                    deben obtenerse de las variables que han sido inicializadas en startEthernetLevel
                -Comprobar los límites de Ethernet. Si la trama es muy pequeña se debe rellenar con 0s mientras que 
                    si es muy grande se debe devolver error.
                -Llamar a pcap_inject para enviar la trama y comprobar el retorno de dicha llamada. En caso de que haya error notificarlo
        Argumentos:
            -data: datos útiles o payload a encapsular dentro de la trama Ethernet
            -length: longitud de los datos útiles expresada en bytes
            -etherType: valor de tipo Ethernet a incluir en la trama
            -dstMac: Dirección MAC destino a incluir en la trama que se enviará
        Retorno: 0 si todo es correcto, -1 en otro caso
    '''
    global macAddress,handle
    #macAddres -> direccion ethernet de origen
    #comprobamos el máximo (la cabecera son 14 [MAC destino + MAC origen + Ethertype])
    if((len(data)+14)>ETH_FRAME_MAX): #comprobamos si la trama al añadir los datos excede el máximo
        return -1
    #comprobamos el mínimo
    if((len(data)+14)<ETH_FRAME_MIN): #comprobamos el mínimo
            size = ETH_FRAME_MIN - (len(data)+14)
            data += bytes([0x00]*size)

    #1º construimos la trama Ethernet
    #trama = cabecera + datos
    trama = bytes()
    trama += dstMac
    trama += macAddress
    trama += etherType.to_bytes(2, byteorder='big')
    trama += data
    #comprobamos si se injecto toda la trama
    ret = pcap_inject(handle, trama, len(trama))
    if(ret!=len(trama)):
        print("Error en inject enviados" + str(ret) + "/" + str(tam))
        return -1
    return 0
    
        
