# import the library
from random import randint
import threading
from appJar import gui
from PIL import Image, ImageTk
import numpy as np
import cv2
import socket
from threading import Thread
from utils import util
from sqlalchemy import false, null
from utils import user
from time import sleep
from utils import calls

class VideoClient(object):
    in_llamada = False
    # El fichero que se muestra al abrir la GUI, o 0 si es la webcam.
    res = "High"
    webcam = 'imgs/webcam.gif'
    fichero_wait = 'imgs/loading.gif'
    homescreen = "imgs/homeScreen.gif"
    usuario = {}  #diccionario con los valores del usuario a llamar
    usuario2 = {}  #diccionario con los valores del usuario a llamar
    local_user = {} #diccionario con tus valores
    #función para conectar
    sockfd = None #sock de servidor de descubrimiento
    #control para pasar pantalla de conexión
    controlCarg = false
    sockllamada = None #sock recibir llamada
    sockllamada2 = None #sock enviar llamada 
    #función para crear el socket que recibe llamadas llamada

    def createServerLLamada(self):
        self.sockllamada = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sockllamada.settimeout(10)
            # Bind del serverSocket.
        try:
            self.sockllamada.bind((self.app.getEntry("IP\t"), int(self.app.getEntry("PORT\t"))))
        except Exception as e:
            self.app.infoBox("Error", "No se pudo completar el bind; " + str(e))
            return False
        t = Thread(target=calls.manage_rec_calls, args=(self, ))
        t.setDaemon(True)
        t.start()
        return True
    
    

    def connectDiscoverServer(self):
        val = True
        try:
            self.sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sockfd.settimeout(5) #time out de 10s
            serverIP = socket.gethostbyname('vega.ii.uam.es')
            self.sockfd.connect((serverIP, 8000))
            self.sockfd.connect(('vega.ii.uam.es', 8000))
        except Exception as e: 
            print(e)
            val = self.app.retryBox("ErrorConexion", "No se ha podido establecer la conexión con el servidor, ¿Desea reintentar?", parent=None)
            while val == True:
                try:
                    self.sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    self.sockfd.connect(('vega.ii.uam.es', 8000))
                    break #sale del bucle
                except Exception as e: 
                    print(e)
                    val = self.app.retryBox("ErrorConexion", "No se ha podido establecer la conexión con el servidor, Desea reintentar?", parent=None)
        

        if val == False: #no ha podido establecer conexión
            self.sockfd=None
            self.app.stop()
        #debug
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            s.bind((self.app.getEntry("IP\t"), int(self.app.getEntry("PORT\t"))))
        except Exception as e:
            self.app.setEntry("PORT\t", "1027")
            self.app.setEntry("UDP PORT\t", "1028")
            self.app.setEntry("NICK\t", "nombre_prueba_1")
        s.close
        self.app.prevFrame("Pages") #pasamos a la siguiente pág



    def __init__(self, window_size):
        # Creamos una variable que contenga el GUI principal
        self.app = gui("Redes2 - P2P", window_size)
        self.app.setGuiPadding(10, 10)
        # Preparación del interfaz
        self.app.addLabel("title", "Cliente Multimedia P2P - Redes2 ")
        #pantalla de llamadas
        self.app.startSubWindow("Llamada", modal=False)
        self.app.startFrame("callHeader")
        self.app.addLabel("fps", "FPS: 0", column=0, row=0)
        self.app.addLabel("tllamada", "Duración 00:00", row=0, column=1)
        self.app.stopFrame()
        self.app.startFrame("VideoCall")
        self.cap = cv2.VideoCapture(self.webcam) #cap para mostrar lo que estoy mandando
        #self.cap = cv2.VideoCapture(0)
        self.mode_webcam = False
        self.app.setPollTime(20)
        self.app.registerEvent(self.capturaVideo)
        #tu
        self.app.addImage("video", self.webcam, row=2, column=0)
        #el otro
        self.app.addImageData("video2", ImageTk.PhotoImage(Image.open("imgs/call.jpg")), fmt="PhotoImage", row=2, column=1)
        
        
        self.app.stopFrame()
        self.app.addLabel("quienLlama", "Nick te está llamando")
        self.app.addButtons(
            ["Colgar", "Aceptar", "Cambiar fuente", "Pausar/Continuar", "Calidad Alta", "Calidad Media", "Calidad Baja"], self.buttonsCallback)
        self.app.stopSubWindow()
        self.app.startFrameStack("Pages")
        self.app.startFrame("Main")
        #ponemos por defecto el fichero de video
        self.app.startTabbedFrame("TabbedFrame")
        self.app.startTab("Main")
        self.app.addLabel("HomeLabel", "HomeScreen")
        self.app.addImage("videoHome", self.homescreen)
        # Registramos la función de captura de video
        # Esta misma función también sirve para enviar un vídeo
        # Añadir los botones
        self.app.addButtons(
            ["Conectar", "Llamar", "Salir"], self.buttonsCallback)
        # Barra de estado
        # Debe actualizarse con información útil sobre la llamada (duración, FPS, etc...)
        self.app.stopTab()


        self.app.startTab("Lista Usuarios")
        self.app.addListBox("UList")
        #list_users = user.user_list(self.sockfd)
        #self.app.updateListBox("ULista", list_users, False)
        self.app.addButtons(
            ["Refresh", "Select"], self.buttonsCallback)
        
        self.app.stopTab()
        self.app.startTab("Tab3")
        self.app.addLabel("l3", "Tab 3 Label")
        self.app.stopTab()
        self.app.stopTabbedFrame()
        self.app.stopFrame()

        self.app.startFrame("Register")
        self.app.addLabelEntry("NICK\t", 0, 0)
        self.app.addLabelSecretEntry("PASSWORD", 0, 1)
        self.app.addLabelEntry("IP\t", 1, 0)
        self.app.addLabelEntry("PORT\t", 1, 1)
        self.app.addLabelEntry("UDP PORT\t", 2, 0)
        self.app.addLabelOptionBox("PROTOCOL", ["0", "1",], 2, 1)
        #ponemos valores por defecto
        self.app.setEntry("NICK\t", "nombre_prueba")
        self.app.setEntry("PASSWORD", "pass_prueba")
        #try to get my ip para ponerla por defecto
        hostname = socket.gethostname()
        ip_address = socket.gethostbyname(hostname)
        self.app.setEntry("IP\t", str(ip_address))
        #puerto por defecto el 1025 porque si y no pide privilegios
        self.app.setEntry("PORT\t", "1025")
        self.app.setEntry("UDP PORT\t", "1026")
        self.app.addButtons(
            ["REGISTER"], self.buttonsCallback, 3, 0)
        self.app.addButtons(
            ["CDebug"], self.buttonsCallback, 3, 1)


        self.app.stopFrame()
        self.app.startFrame("Wait")
        self.app.addLabel("Waiting text", "Esperando conexión con el servidor...")
        self.app.addImage("Pantalla Wait", self.fichero_wait)
        #photo = ImageTk.PhotoImage(Image.open("imgs/wait.jpg"))
        #self.app.addImageData("pic", photo, fmt="PhotoImage")
        self.app.addButtons(
            ["Next"], self.buttonsCallback)
        self.app.stopFrame()
        self.app.stopFrameStack()

    def start(self):
        #hilo para conexión
        t = Thread(target=self.connectDiscoverServer)
        t.setDaemon(True)
        t.start()
        #hilo para actualizar lista de usuarios
        #self.app.setStartFunction(self.connectDiscoverServer)
        #función para    print(users) garantizar que se cierran los sockets
        self.app.setStopFunction(self.checkStop)
        self.app.go()

    # Función que captura el frame a mostrar en cada momento
    def capturaVideo(self):
        #actualizas tu pantalla
        # Capturamos un frame de la cámara o del vídeo
        ret, frame = self.cap.read()
        #si deja de recibir info ponemos el video
        if frame is None:
            self.cap = cv2.VideoCapture(self.webcam)
            return
        frame = cv2.resize(frame, (640, 480))
        cv2_im = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        img_tk = ImageTk.PhotoImage(Image.fromarray(cv2_im))
        
        #if frame is None:
        #    self.cap = cv2.VideoCapture(self.webcam)
        #    return

        # Lo mostramos en el GUI
        self.app.setImageData("video", img_tk, fmt='PhotoImage')

        # Aquí tendría que el código que envia el frame a la red
        # ...
    

    # Función que gestiona los callbacks de los botones
    def checkStop(self):
        if self.app.yesNoBox("Confirmar salida", "Seguro que desea cerrar la aplicación?"):
            #si desea salir
            if(self.sockfd!=None):
                user.quit(self.sockfd)
            if(self.sockllamada!=None):
                self.sockllamada.close()
            return True


    def buttonsCallback(self, button):
        if button == "Salir":
            """if(self.sockfd!=None):
                user.quit(self.sockfd)
            if(self.sockllamada!=None):
                self.sockllamada.close()"""          
            self.app.stop()#podemos cerrar pq tenemos el check
        
        elif button == "Conectar":
            # Entrada del nick del usuario a conectar
            nick = self.app.textBox("Conexión",
                                    "Introduce el nick del usuario a buscar")
            ans = user.query(self.sockfd, nick)
            if(ans == None):
                self.app.warningBox("Error", "Usuario no encontrado")
                return
            self.usuario['nick'], self.usuario['ip'], self.usuario['port'], self.usuario['protocols'] = ans
            print(self.usuario)       

        elif button == "REGISTER":
            dict ={}
            dict['nick'] = self.app.getEntry("NICK\t")
            dict['password'] = self.app.getEntry("PASSWORD")
            dict['ip'] = self.app.getEntry("IP\t")
            dict['port'] = self.app.getEntry("PORT\t")
            dict['UDPport'] = self.app.getEntry("UDP PORT\t")
            dict['protocol'] = self.app.getOptionBox("PROTOCOL")
            res = True
            if util.checker(self.app.getEntry("PORT\t"), 'PORT') == False:
                self.app.warningBox("Datos incorrectos", "UDP Puerto incorrecto", parent=None)
            res = user.register(self.sockfd, dict)
            """if res == 'nick':
                self.app.warningBox("Datos incorrectos", "Nick ya existente", parent=None)
            el"""
            if res == 'ip':
              self.app.warningBox("Datos incorrectos", "IP incorrecta", parent=None)
            elif res == 'port':
                self.app.warningBox("Datos incorrectos", "Puerto incorrecto", parent=None)
            elif res == 'protocol':
                self.app.warningBox("Datos incorrectos", "Protocolo incorrecto", parent=None)
            elif res == 'password':
                self.app.warningBox("Datos incorrectos", "Contraseña incorrecta", parent=None)        
            elif self.createServerLLamada()!=False: #si no hay error en la creación del socket
                self.app.prevFrame("Pages")
                self.local_user = dict #guardamos los datos locales
                #list_users = user.user_list(self.sockfd)
                #self.app.updateListBox("UList", list_users, False)
                #self.app.prevFrame("Pages") #pasamos a la siguiente pág

        elif button == "Refresh":
            list_users=[]
            #debug
            #nombre=["nick", "pedro", "juan", "pablo", "david", "dani", "andrea"]
            #for i in range (1000):
                #ui = (f"-> Nick: " + nombre[randint(0, 6)] + str(i) + "\n   IP: 127.0.0.2 \n   Puerto: 1026\n")
                #list_users.append((f"-> Nick:  {nombre[randint(0, 6)]}{str(i)};   IP: 127.0.0.2;   Puerto: 1026"))
            list_users = user.user_list(self.sockfd)
            self.app.updateListBox("UList", list_users, False)

        elif button == "Select": #si seleccionamos select, actualizamos diccionario de user
            if self.app.getListBox("UList") != []: #si el valor seleccionado no es vacio
                usuario = (self.app.getListBox("UList")[0])
                campos = usuario.split(';')
                self.usuario['nick'] = campos[0].split('-> Nick: ')[1]
                self.usuario['ip'] = campos[1].split("IP: ")[1]
                self.usuario['port'] = campos[2].split("Puerto: ")[1]
                print(self.usuario)
        elif button == "Aceptar": #si seleccionamos select, actualizamos diccionario de user
            if self.in_llamada == False: #no puedes aceptar a otro si ya estás en llamada
                self.in_llamada=True
                calls.accept_call(self)
                calls.call(self)
            else:
                self.app.warningBox("Error", "No puedes empezar una llamada porque ya estas en llamada")

        elif button == "Cambiar fuente": #para rotar entre webcam y video
            if(self.webcam=="0"):
                self.webcam = "imgs/webcam.gif"
            else:
                self.webcam="0"
        elif button == "Calidad Alta":
            calls.setImageResolution(self, "HIGH")
        elif button == "Calidad Media":
            calls.setImageResolution(self, "MEDIUM")
        elif button == "Calidad Baja":
            calls.setImageResolution(self, "LOW")
        elif button == "Pausar/Continuar":
            calls.call_change_stat(self)
        elif button == "Colgar":
            if(self.in_llamada==False):
                calls.deny_call(self) #si aun no estamos en llamada la denegamos
            else:
                calls.end_call(self)
                self.in_llamada=False


        elif button == "Llamar":
            if (self.usuario=={}):
                self.app.warningBox("Error", "No ha seleccionado usuario a llamar")
                return
            if (self.usuario['nick']==self.local_user['nick']):
                self.app.warningBox("Error", "No se permite llamarse a uno mismo")
                return
            if self.in_llamada == False: #si ya estas en llamada no puedes llamar otra vez
                self.app.setImageData("video2", ImageTk.PhotoImage(Image.open("imgs/call.jpg")), fmt='PhotoImage')
                self.app.setLabel("tllamada", "Duración " + "00:00")
                self.app.setLabel("fps", "FPS: 0")
                if(user.call(self.local_user, self.usuario, self.sockllamada2)==False): #mandamos petición de llamada
                    self.app.warningBox("Error", "No se pudo llamar al usuario")
                    return
                calls.call_managed(self, self.usuario) #cambiamos a ventana de llamar
                self.in_llamada=True
            else:
                self.app.warningBox("Error", "Estas aún en llamada con otro")
                return
        else:
            self.app.prevFrame("Pages")
if __name__ == '__main__':
    vc = VideoClient("640x520")
    vc.start()
    #my_video_thread = threading.Thread(target=vc.start(), daemon=True)
    #my_video_thread.start()
