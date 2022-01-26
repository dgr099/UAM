from ethernet import *
from arp import *
from fcntl import I_POP, ioctl
import subprocess
from math import ceil, floor

SIOCGIFMTU = 0x8921
SIOCGIFNETMASK = 0x891b
#Diccionario de protocolos. Las claves con los valores numéricos de protocolos de nivel superior a IP
#por ejemplo (1, 6 o 17) y los valores son los nombres de las funciones de callback a ejecutar.
protocols={}
#Valor inicial para el IPID
IPID = 0
#Valor de ToS por defecto
DEFAULT_TOS = 0
#Tamaño mínimo de la cabecera IP
IP_MIN_HLEN = 20
#Tamaño máximo de la cabecera IP
IP_MAX_HLEN = 60
#Valor de TTL por defecto
DEFAULT_TTL = 64

def chksum(msg):
    '''
        Nombre: chksum
        Descripción: Esta función calcula el checksum IP sobre unos datos de entrada dados (msg)
        Argumentos:
            -msg: array de bytes con el contenido sobre el que se calculará el checksum
        Retorno: Entero de 16 bits con el resultado del checksum en ORDEN DE RED
    '''
    s = 0       
    for i in range(0, len(msg), 2):
        if (i+1) < len(msg):
            a = msg[i] 
            b = msg[i+1]
            s = s + (a+(b << 8))
        elif (i+1)==len(msg):
            s += msg[i]
        else:
            raise 'Error calculando el checksum'
    s = s + (s >> 16)
    s = ~s & 0xffff

    return s

def getMTU(interface):
    '''
        Nombre: getMTU
        Descripción: Esta función obteiene la MTU para un interfaz dada
        Argumentos:
            -interface: cadena con el nombre la interfaz sobre la que consultar la MTU
        Retorno: Entero con el valor de la MTU para la interfaz especificada
    '''
    s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
    ifr = struct.pack('16sH', interface.encode("utf-8"), 0)
    mtu = struct.unpack('16sH', ioctl(s,SIOCGIFMTU, ifr))[1]
   
    s.close()
   
    return mtu
   
def getNetmask(interface):
    '''
        Nombre: getNetmask
        Descripción: Esta función obteiene la máscara de red asignada a una interfaz 
        Argumentos:
            -interface: cadena con el nombre la interfaz sobre la que consultar la máscara
        Retorno: Entero de 32 bits con el valor de la máscara de red
    '''
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ip = fcntl.ioctl(
        s.fileno(),
       SIOCGIFNETMASK,
        struct.pack('256s', (interface[:15].encode('utf-8')))
    )[20:24]
    s.close()
    return struct.unpack('!I',ip)[0]


def getDefaultGW(interface):
    '''
        Nombre: getDefaultGW
        Descripción: Esta función obtiene el gateway por defecto para una interfaz dada
        Argumentos:
            -interface: cadena con el nombre la interfaz sobre la que consultar el gateway
        Retorno: Entero de 32 bits con la IP del gateway
    '''
    p = subprocess.Popen(['ip r | grep default | awk \'{print $3}\''], stdout=subprocess.PIPE, shell=True)
    dfw = p.stdout.read().decode('utf-8')
    print(dfw)
    return struct.unpack('!I',socket.inet_aton(dfw))[0]



def process_IP_datagram(us,header,data,srcMac):
    '''
        Nombre: process_IP_datagram
        Descripción: Esta función procesa datagramas IP recibidos.
            Se ejecuta una vez por cada trama Ethernet recibida con Ethertype 0x0800
            Esta función debe realizar, al menos, las siguientes tareas:
                -Extraer los campos de la cabecera IP (includa la longitud de la cabecera)
                -Calcular el checksum sobre los bytes de la cabecera IP
                    -Comprobar que el resultado del checksum es 0. Si es distinto el datagrama se deja de procesar
                -Analizar los bits de de MF y el offset. Si el offset tiene un valor != 0 dejar de procesar el datagrama (no vamos a reensamblar)
                -Loggear (usando logging.debug) el valor de los siguientes campos:
                    -Longitud de la cabecera IP
                    -IPID
                    -Valor de las banderas DF y MF
                    -Valor de offset
                    -IP origen y destino
                    -Protocolo
                -Comprobar si tenemos registrada una función de callback de nivel superior consultando el diccionario protocols y usando como
                clave el valor del campo protocolo del datagrama IP.
                    -En caso de que haya una función de nivel superior registrada, debe llamarse a dicha funciñón 
                    pasando los datos (payload) contenidos en el datagrama IP.
        
        Argumentos:
            -us: Datos de usuario pasados desde la llamada de pcap_loop. En nuestro caso será None
            -header: cabecera pcap_pktheader
            -data: array de bytes con el contenido del datagrama IP
            -srcMac: MAC origen de la trama Ethernet que se ha recibido
        Retorno: Ninguno
    '''

    # si la cabecera no es de tipo IP, no la tratamos
    #if header.caplen < IP_MIN_HLEN or header.caplen > IP_MAX_HLEN:
    #    return

    # captura de los campos de la cabecera
    #print("procesando")
    version = "{:08b}".format(int(data[0:1].hex(),16))[:4] #version será del primer byte los 4 primers bits
    ihl = "{:08b}".format(int(data[0:1].hex(),16))[4:] #los 4 siguiente son el ihl
    ihl=int(ihl, 2)
    #print(ihl)

    """for i in (data[:(ihl*4)]):
        print(hex(i), end=" ") 
        print()
    """

   # comprobamos checksum para saber si continuamos con el datagrama
    """print(chksum(data[:(ihl*4)]))
    a = chksum(data[:10] + data[12:ihl*4])
    print(a.to_bytes(2, byteorder='big').hex())
    print(chksum(a.to_bytes(2, byteorder='big') + data[:10] + data[12:ihl*4]))
    print()"""

    if chksum(data[:10] + data[12:ihl*4]).to_bytes(2, byteorder='little') != data[10:12]: #comprobamos que el checksum de la cabecera sea 0
        return
    type_of_service = data[1:2] #el segundo byte completo es para el type of service
    total_length = data[2:4] #los dos siguientes indican el total lengt
    IPID = data[4:6]
    flags = "{:08b}".format(int(data[6:7].hex(),16))[:3]
    fragment_offset = "{:08b}".format(int(data[6:8].hex(),16))[3:]
    ttl = data[8:9]
    protocol = data[9:10]
    checksum = data[10:12]
    src_address = data[12:16]
    dst_address = data[16:20]
    # captura de posible campo options (tam variable)
    header_offset = 20     #iniciamos en el ultimo byte recogido
    options = bytearray()   
    while header_offset < ihl*4:    #hasta que lleguemos al tam de cabecera
        options += data[header_offset:header_offset + 4]
        header_offset +=4     #opcs de 4 bytes

    payload = data[ihl*4:]
    """for i in (payload):
        print(hex(i), end=" ")
    print()"""

    fragment_offset=int(fragment_offset, 2)
    # comprobamos el bit MF y el offset == 0
    if fragment_offset != 0:
        return
    # loggeamos tam cabecera, identification, flags (DF y MF), offset, src_ip, dst_ip y protocol
    dst = "" #ponemos ip destino con mejor formato lo mismo en ip origen
    ori = ""
    for b in range(4):
        dst+=str(dst_address[b])
        dst+='.'
        ori+=str(src_address[b])
        ori+='.'
    dst = dst[:-1]
    ori = ori[:-1]

    logging.debug('Longitud de la cabecera IP: ' + str(ihl*4))
    logging.debug('IPID: ' + str(IPID.hex()))
    logging.debug('Valor de la bandera DF: ' + flags[1])
    logging.debug('Valor de la bandera MF: ' + flags[2])
    logging.debug('Valor de offset: ' + str(fragment_offset))
    logging.debug('IP origen: ' + ori)
    logging.debug('IP destino: ' + dst)
    logging.debug('Protocolo: ' + str(protocol.hex()))

    # comprobamos si tenemos registrado el protocolo en el diccionario de protocolos
    # en caso de tenerlo, ejecutarlo con el payload
    protocol = int.from_bytes(protocol, byteorder='big')
    if protocol in protocols.keys():
        protocols[protocol](us, header, payload, src_address)


def registerIPProtocol(callback,protocol):
    '''
        Nombre: registerIPProtocol
        Descripción: Esta función recibirá el nombre de una función y su valor de protocolo IP asociado y añadirá en la tabla 
            (diccionario) de protocolos de nivel superior dicha asociación. 
            Este mecanismo nos permite saber a qué función de nivel superior debemos llamar al recibir un datagrama IP  con un 
            determinado valor del campo protocolo (por ejemplo TCP o UDP).
            Por ejemplo, podemos registrar una función llamada process_UDP_datagram asociada al valor de protocolo 17 y otra 
            llamada process_ICMP_message asocaida al valor de protocolo 1. 
        Argumentos:
            -callback_fun: función de callback a ejecutar cuando se reciba el protocolo especificado. 
                La función que se pase como argumento debe tener el siguiente prototipo: funcion(us,header,data,srcIp):
                Dónde:
                    -us: son los datos de usuarios pasados por pcap_loop (en nuestro caso este valor será siempre None)
                    -header: estructura pcap_pkthdr que contiene los campos len, caplen y ts.
                    -data: payload del datagrama IP. Es decir, la cabecera IP NUNCA se pasa hacia arriba.
                    -srcIP: dirección IP que ha enviado el datagrama actual.
                La función no retornará nada. Si un datagrama se quiere descartar basta con hacer un return sin valor y dejará de procesarse.
            -protocol: valor del campo protocolo de IP para el cuál se quiere registrar una función de callback.
        Retorno: Ninguno 
    '''
    global protocols
    protocols[protocol] = callback


def initIP(interface,opts=None):
    global myIP, MTU, netmask, defaultGW,ipOpts, defaultMac
    '''
        Nombre: initIP
        Descripción: Esta función inicializará el nivel IP. Esta función debe realizar, al menos, las siguientes tareas:
            -Llamar a initARP para inicializar el nivel ARP
            -Obtener (llamando a las funciones correspondientes) y almacenar en variables globales los siguientes datos:
                -IP propia
                -MTU
                -Máscara de red (netmask)
                -Gateway por defecto
            -Almacenar el valor de opts en la variable global ipOpts
            -Registrar a nivel Ethernet (llamando a registerCallback) la función process_IP_datagram con el Ethertype 0x0800
        Argumentos:
            -interface: cadena de texto con el nombre de la interfaz sobre la que inicializar ip
            -opts: array de bytes con las opciones a nivel IP a incluir en los datagramas o None si no hay opciones a añadir
        Retorno: True o False en función de si se ha inicializado el nivel o no
    '''

    # Inicializar ARP
    if initARP(interface):
        return False

    # Obtener campos para inicializar y almacenar en las variables globales
    myIP = getIP(interface)
    MTU = getMTU(interface)
    netmask = getNetmask(interface)
    defaultGW = getDefaultGW(interface)
    defaultMac = ARPResolution(defaultGW)
    """print("Default mac:")
    for i in bytearray(defaultMac):
        print(hex(i) + ":", end="")
    print()"""
    # guardamos las opciones
    ipOpts = opts

    # Registramos el proceso IP
    registerCallback(process_IP_datagram, 0x0800)

    return True

def sendIPDatagram(dstIP,data,protocol):
    global IPID,MTU, ipOpts, defaultGW, defaultMac
    '''
        Nombre: sendIPDatagram
        Descripción: Esta función construye un datagrama IP y lo envía. En caso de que los datos a enviar sean muy grandes la función
        debe generar y enviar el número de fragmentos IP que sean necesarios.
        Esta función debe realizar, al menos, las siguientes tareas:
            -Determinar si se debe fragmentar o no y calcular el número de fragmentos
            -Para cada datagrama o fragmento:
                -Construir la cabecera IP con los valores que corresponda.Incluir opciones en caso de que ipOpts sea distinto de None
                -Calcular el checksum sobre la cabecera y añadirlo a la cabecera en la posición correcta
                -Añadir los datos a la cabecera IP
                -En el caso de que sea un fragmento ajustar los valores de los campos MF y offset de manera adecuada
                -Enviar el datagrama o fragmento llamando a sendEthernetFrame. Para determinar la dirección MAC de destino
                al enviar los datagramas:
                    -Si la dirección IP destino está en mi subred:
                        -Realizar una petición ARP para obtener la MAC asociada a dstIP y usar dicha MAC
                    -Si la dirección IP destino NO está en mi subred:
                        -Realizar una petición ARP para obtener la MAC asociada al gateway por defecto y usar dicha MAC
            -Para cada datagrama (no fragmento):
                -Incrementar la variable IPID en 1.
        Argumentos:
            -dstIP: entero de 32 bits con la IP destino del datagrama 
            -data: array de bytes con los datos a incluir como payload en el datagrama
            -protocol: valor numérico del campo IP protocolo que indica el protocolo de nivel superior de los datos
            contenidos en el payload. Por ejemplo 1, 6 o 17.
        Retorno: True o False en función de si se ha enviado el datagrama correctamente o no
          
    '''
    tamTotal= len(data)
    IHL = 5 #para el base, el ihl es 5 (20/4)
    
    if(ipOpts is not None):
        tamOpc=len(ipOpts)/4
        if(tamOpc<=10):
            IHL += tamOpc #sumamos al IHL el número de opciones, cada opción son 4 bytes
    # Calculamos el numero de fragmentos necesario (si num_fragments == 1 => no fragmentacion)
    tamEfectivo = MTU-(IHL*4) #si IHL es el bas de 5->la cabecera mide 20, si x ej MTU=1500, tamEfectivo=1480
    # A continuación debemos comprobar si esta cantidad máxima de datos útiles es múltiplo de 8
    tamEfectivo = floor(tamEfectivo/8)*8
    # Calculamos el número de fragmentos a enviar. Para ello dividimos el total de datos a enviar/cantidad máxima de datos útiles
    num_fragments = ceil(tamTotal / tamEfectivo)

     # ponemos el header
    header1 = bytearray()
    # Version (4) + IHL
    header1 += int((4<<4) + IHL).to_bytes(1, byteorder='big')
    # Type Of Service (0)
    header1 += int(0).to_bytes(1, byteorder='big')
    #este campo varía en cada paquete
    # Total Length (si hay fragmentación, todos ocupan el máximo (tam efectivo + cabecera))
    header1 += int(tamEfectivo+IHL*4).to_bytes(2, byteorder='big')
    # Identification
    header1 += int(IPID).to_bytes(2, byteorder='big')
    # Flags (001) + Offset flag 001 para indicar que hay paquetes posteriores
    #el offset está en palabras de 8 bytes por tanto tamEfectivo*i/8
    #tam paquete * número de paquete/8
    #empieza con offset 0
    #este campo también cambia con cada paquete
    header1 += int((1 << 13)).to_bytes(2, byteorder='big')
    #Time to live
    header1 += int(64).to_bytes(1, byteorder='big')
    #Protocol
    header1 += protocol.to_bytes(1, byteorder='big')
    #la header 2 no cambia nunca
    header2 = bytearray()
    # myIP como origen
    header2 += myIP.to_bytes(4, byteorder='big')
    # el destIP se pasa por arg
    header2 += dstIP.to_bytes(4, byteorder='big')
    # por último las opciones
    if(ipOpts is not None):
        header2 += ipOpts
    mac = ARPResolution(dstIP) #solicitamos la MAC de la IP dest
    if(mac is None): #si da None, empleamos la mac de la salida por defecto
        mac = defaultMac

    #A continuación debemos comprobar si esta cantidad máxima de datos útiles es múltiplo de 8
    for i in range(num_fragments - 1):
        #vamos cambiando el valor del offset
        offset = tamEfectivo*i
        header1[6:8] = int((1 << 13) + (offset/8)).to_bytes(2, byteorder='big')
        #en este punto ya hemos terminado de formar la cabecera IP, juntamos con la data y enviamos
        data_toSend = data[offset:offset+tamEfectivo]
        checkSum = chksum(header1+header2).to_bytes(2, byteorder='little')
        trama = header1 + checkSum + header2 + data_toSend
        #enviamos el paquete
        sendEthernetFrame(trama, len(trama), 0x0800, mac)


    # el tamaño del último será lo restante tras enviar 
    # tamTotal guarda el total de data a enviar, le restas los enviados en los otros fragmentos y le sumas el tam de cabecera
    header1[2:4] = int((tamTotal-(tamEfectivo)*(num_fragments-1))+IHL*4).to_bytes(2, byteorder='big')

    offset=tamEfectivo*(num_fragments-1)
    header1[6:8] = int((offset/8)).to_bytes(2, byteorder='big') #solo el offset sin bandera porq es el último
    checkSum = chksum(header1+header2).to_bytes(2, byteorder='little')
    data_toSend = data[offset:offset+tamEfectivo]
    trama = header1 + checkSum + header2 + data_toSend
    #enviamos el paquete
    """print("Enviando último paquete")
    print("Cabecera IP:")
    for i in bytearray(header1 + checkSum + header2):
        print(hex(i), end=" ")

    print()"""
    sendEthernetFrame(trama, len(trama), 0x0800, mac)
    #incrementamos la variable
    IPID+=1


