from cgitb import reset
from pickle import TRUE
from cv2 import split
from utils import user
from threading import Thread
import time
from appJar import gui
from PIL import Image, ImageTk
import cv2
import socket
import math
import numpy as np

#función para controlar recibir llamada
Buff_len = 100000 #el buffer para guardar la imagen
video_paused = False #variable para si el video está pausado
pausa = False #variable por si soy yo quien pauso (para el resume y tal)

def call_change_stat(vc):
    global pausa
    if(pausa==True):
        pausa=False
        cmd = "CALL_RESUME " + vc.local_user['nick']
    else:
        pausa=True
        cmd = "CALL_HOLD " + vc.local_user['nick']
    try:
        vc.sockllamada2.send(cmd.encode()) #le mandamos el fin de llamada
    except Exception as e: 
            print("Change_stat " + str(e))

def call_managed(vc, user):
        #simplemente muestra quien está llamando
        vc.app.setImageData("video2", ImageTk.PhotoImage(Image.open("imgs/call.jpg")), fmt='PhotoImage')
        vc.app.showSubWindow("Llamada") #mostramos la pantalla de llamada
        vc.app.setLabel("quienLlama", "Llamada com: " + user['nick'])
#cuando acepte la llamada
def accept_call(vc):
    cmd = "CALL_ACCEPTED " + vc.local_user['nick'] + " " + vc.local_user['UDPport']
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(5)
    print(vc.usuario2)
    try:
        #intentamos conectar con la persona a llamar
        sock.connect((vc.usuario2['ip'], int(vc.usuario2['port'])))
        print("Se envio " + cmd)
        sock.send(cmd.encode()) #le enviamos que le estamos llamando
    except Exception as e: 
            print(e)
            sock.close()
            return False
    
    vc.sockllamada2=sock

#cuando cuelga la llamada
def end_call(vc):
    global endcall
    cmd = "CALL_END " + vc.local_user['nick']
    try:
        vc.sockllamada2.send(cmd.encode()) #le mandamos el fin de llamada
        vc.sockllamada2.close() #cerramos nuestro socket de llamada
    except Exception as e: 
            print("End call " + str(e))
    endcall = TRUE
    #volvemos a poner la otra imagen
    vc.app.hideSubWindow("Llamada")

def deny_call(vc):
    global endcall
    cmd = "CALL_DENIED " + vc.local_user['nick']
    endcall=True
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(5)
        #intentamos conectar con la persona a llamar
        sock.connect((vc.usuario2['ip'], int(vc.usuario2['port'])))
        sock.send(cmd.encode()) #le enviamos que le estamos llamando
    except Exception as e: 
            print("Call denied " + str(e))
    try:
        sock.close()
        vc.app.hideSubWindow("Llamada") #quitamos el menu de llamada
    except Exception as e: 
            print(e)

# Establece la resolución de la imagen capturada
def setImageResolution(vc, resolution):
        # Se establece la resolución de captura de la webcam
        # Puede añadirse algún valor superior si la cámara lo permite
        # pero no modificar estos
        if resolution == "LOW":
            vc.cap_env.set(cv2.CAP_PROP_FRAME_WIDTH, 160)
            vc.cap_env.set(cv2.CAP_PROP_FRAME_HEIGHT, 120)
        elif resolution == "MEDIUM":
            vc.cap_env.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
            vc.cap_env.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
        elif resolution == "HIGH":
            vc.cap_env.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
            vc.cap_env.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

def sendFrames(vc):
    #mientras la llamada no termine y la app esté abierta
    numS = 0 #ponemos el # de secuencia a 0
    fps = 15
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #abrimos socket udp
    sock.settimeout(5)
    global endcall
    global pausa
    #cambiar
    vc.cap_env = cv2.VideoCapture(vc.webcam) #capt encargada del envio
    while not endcall and vc.app.alive:
        vc.app.setPollTime(20)
        if pausa: #si tengo la pausa puesta
            continue
        # Capturamos un frame de la cámara o del vídeo
        ret, img = vc.cap_env.read() # lectura de un frame de vídeo
        if(img is None):
            vc.cap_env = cv2.VideoCapture(vc.webcam)
            continue
        encode_param = [cv2.IMWRITE_JPEG_QUALITY,50]
        result,encimg = cv2.imencode('.jpg',img,encode_param)
        if result == False: 
            print('Error al codificar imagen')
            continue
        img = encimg.tobytes()
        #cabecera Número de orden#Timestamp#Resolución video#FPS#Datos...
        data = bytes(str(numS) + '#' + str(time.time()) + '#' + vc.res + '#' + str(fps) + '#', 'UTF') + img
        server_address = (vc.usuario2['ip'], int(vc.usuario2['UDPport']))
        sock.sendto(data, (server_address)) #mandamos la imagen
        numS = numS+1
    sock.close()
    vc.app.setPollTime(20)
    return 

#inserta ordenado en función del tS del item
def insertarOrdenado(array, item):
    last = 0
    index=0
    for i in array:
        if(last<item[0] and i[0]>item[0]):
            aux = array[index:len(array)]
            array[index]=item
            array[index+1:]=aux
            return
        index=index+1
        last=i[0]
    array.append(item)

def updateTimeInfo(vc):
    global fotograms
    global seconds
    while(True):
        global stop_threads
        if stop_threads:
            break
        horas = math.floor(seconds/60)
        aSeconds = seconds%60
        vc.app.setLabel("tllamada", "Duración " + str(horas) + ":" + str(aSeconds))
        time.sleep(1)
        vc.app.setLabel("fps", "FPS: " + str(float(fotograms)))
        fotograms=0
        seconds=seconds+1


def receiveFrames(vc):
    #vamos a 15 fps, 30 slots buffer
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(5)
    sock.bind((vc.local_user['ip'], int(vc.local_user['UDPport'])))
    numSecuencia = 0
    fps=15
    buffer = []
    posBuffer = 0
    global fotograms
    global seconds
    global endcall
    global video_paused
    fotograms = 0
    t_foto=0
    seconds = 0
    #vamos a tener un retraso de 10 fotogramas para q el buffer se vaya llenando
    #hilo para reiniciar el contador de fps
    global stop_threads
    stop_threads = False
    #lanzo el thread para actualizar info de tiempo y fps
    t1 = Thread(target = updateTimeInfo, args =([vc]))
    t1.start()
    q = 0.0
    while not endcall and vc.app.alive:
        if(len(buffer)>0 and numSecuencia>=10): #primero vemos si se puede mostrar info
            item = buffer.pop(0)
            #if(time.time()-item[0]>1): #si tiene 1seg de diferencia con ahora, descartamos
            #    continue #pasamos de el por el retraso
             
            img = item[1] #cojemos la imagen que toque
            img = cv2.resize(img, (640, 480)) #lo reescalamos al tam de la pantalla
            cv2_im = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
            img_tk = ImageTk.PhotoImage(Image.fromarray(cv2_im))
            #print("Cambiando imagen")
            vc.app.setImageData("video2", img_tk, fmt='PhotoImage')
        #despues ya si que pasamos a recepción de datos
        if(video_paused): #si tiene la pausa no está enviando nada
            continue
        try:
            data, serverAddress = sock.recvfrom(Buff_len)
        except Exception as e:
            continue
        fotograms=fotograms+1
        t_foto=t_foto+1
        #cabecera Número de orden#Timestamp#Resolución video#FPS#Datos...
        """unp = data.split(b'#')
        print(len(unp))
        numSecuencia = int(unp[0].decode('UTF'))
        tS = float(unp[1].decode('UTF'))
        res = str(unp[2].decode('UTF'))
        fps = int(unp[3].decode('UTF'))
        print(tS, res, fps)
        encimg = b''
        encimg = encimg.join(unp[4:])"""
        numSecuencia, tS, res, fps, encimg = data.split(b'#', 4)
        numSecuencia=int(numSecuencia.decode('UTF'))
        res = str(res.decode('UTF'))
        tS=float(tS.decode('UTF'))
        fps=int(fps.decode('UTF'))
        #if(t_foto==1): #si es la 1º imagen que recibe calcula q
        #    rr = time.time()- tS #retraso de red
        #    q = rr+1 #le añades un retraso fijo de 400ms
        #elif(time.time()<tS+q): #si se recibe en un momento post a cuando se debio reproducir
        #    continue
        #tiempo en que se recibe
        if(time.time()- tS > 1): #si tiene mas de 1 seg descartamos
            continue
        #se recoge la img del paquete
        #encimg es la foto pero comprimida
        decimg = cv2.imdecode(np.frombuffer(encimg,np.uint8), 1)
        if(decimg is None):
            print("None")
            return
        if(len(buffer)>30): #si el buffer está lleno
            #buffer = []
            buffer.pop(0) #cambiamos la más antigua por la nueva
        #insertamos ordenado por el ts
        item = [tS, decimg]
        insertarOrdenado(buffer, item)
    stop_threads=True #terminamos hilo q actualiza fps y tiempo
    t1.join()
    sock.close() #terminamos cerrando el socket
    return


def call(vc):
    global video_paused 
    video_paused = False #iniciamos el pausado a false
    global endcall
    endcall = False
    #lanzamos hilos de envio y recepción de frames
    thread = Thread(target=sendFrames, args=(vc,))
    thread.start()
    thread = Thread(target=receiveFrames, args=(vc,))
    thread.start()


def manage_rec_calls(vc):
    sock=vc.sockllamada
    #ponemos el sock a esperar conexiones
    sock.listen(2)
    global endcall
    global pausa
    global video_paused
    while (vc.app.alive): #mientras la app siga abierta
        try: #intenta aceptar la conexion
                csock, caddres = sock.accept()
        except socket.timeout:
            continue
        except Exception as e:
            print(e)
            continue #vuelve a esperar conexion

        #tendriamos que hacer una función para que el resto de conexiones diga que está en llamada
        #bucle cuando estamos en llamada
        #hasta que termine 
        endcall=False
        vc.usuario2 = vc.usuario
        while vc.app.alive and endcall==False:
            try:
                response = csock.recv(Buff_len).decode('utf-8')
            except Exception as e:
                if(str(e) == "timed out"):
                    continue
                print(e)
                break #vuelve a esperar conexion
            if(response==""): #si no recibe info
                continue
            print(response)
            response = response.split(" ")
            #control de mensaje recibido
            if(response[0] == "CALL_END" and response[1] == vc.usuario2['nick']):
                endcall=True #indico que ha terminado a los hilos
                vc.app.hideSubWindow("Llamada") #quito la llamada
                vc.in_llamada=False #le indico q termino la llamada
                #terminar llamada
                break #salimos del bucle pq la llamada terminó
            #si se pide pausar la llamada
            elif(response[0] == "CALL_HOLD" and response[1] == vc.usuario2['nick']):
                video_paused = True #ponemos la variable de pausa del otro
    
            #pide continuar
            elif(response[0] == "CALL_RESUME" and response[1] == vc.usuario2['nick']):
                video_paused = False #false, se vuelve a enviar imagen
            
            #si recibe petición de comenzar la llamada y no fue redirigido al busy
            elif(response[0] == "CALLING"):
                vc.usuario2['nick'] = response[1] #cojo el nick
                vc.usuario2['UDPport'] = int(response[2]) #cojo el puerto udp
                ans = user.query(vc.sockfd, vc.usuario2['nick'])#preguntas por el vc.usuario2 para obtener ip
                if ans is None:
                    break
                vc.usuario2['nick'], vc.usuario2['ip'], vc.usuario2['port'], vc.usuario2['protocols'] = ans
                #func de respuesta de llamada
                call_managed(vc, vc.usuario2) #muestras pantalla de llamada para q pueda decidir si aceptar
            elif response[0] == "CALL_BUSY":
                vc.app.infoBox("Usuario ocupado","El vc.usuario2 al que ha intentado llamar se encuentrá ocupado")
                vc.in_llamada = False
                vc.app.hideSubWindow("Llamada") #quito la llamada
                break
            elif response[0] == "CALL_DENIED" and response[1] == vc.usuario2['nick']:
                vc.app.infoBox("Llamada rechazada",vc.usuario2['nick']+ " rechazó la llamada")
                vc.in_llamada = False
                vc.app.hideSubWindow("Llamada") #quito la llamada
                break

            #si acepta la llamada
            elif response[0] == "CALL_ACCEPTED" and response[1] == vc.usuario['nick']:
                vc.usuario2['nick'] = response[1] #cojo el nick
                vc.usuario2['UDPport'] = int(response[2]) #cojo el puerto
                #func para empezar llamada
                call(vc)

        csock.close() #cerramos el socket de conexión con el otro   
    sock.close() #en el momento en que se cierre la conexión cierra el socket
    return