from Crypto.PublicKey import RSA
from datetime import datetime
from src.utils.crypto import encsign, decrypt, check_sign

import json, socket, sys, signal, threading, os

IDS_FILE = "./data/ids.json"
ET_TELEMETRY_FOLDER = "./data/telemetries/"

BUFFER_SIZE = 1024
ASIMETRIC_KEY_SIZE = 2048

ET_LISTEN_QUEUE_SIZE = 20

class estacionTerrestre:
    def __init__(self, etID: str, puerto: int):
        
        try: 
            # Crea socket
            self.serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Permite reusar el puerto
            
            # Abre puerto
            self.serverSocket.bind(("localhost", puerto))
            
        except socket.error as exc:
            self.close_and_finish("Caught exception socket.error: " + str(exc), self.serverSocket)
            
        # Atributos del drone
        self.id = etID
        self.puerto = puerto
        
        # Atributos de conexion
        self.dronesLinked = {}                          # {'droneID': [puerto, publicKey])
        self.dronesConnected = {}                       # {'droneID': [flying, battery, socket, sessionKey]}
        self.baseLinked = (None, -1, None, None, None)  # (baseID, puerto, publicKey, socket, sessionKey)
        
        # Instrucciones soportadas para server
        self.instr = ["LINK", "UNLINK", "CONNECT", "DISCONNECT", "TELEMETRY", "FLY", "LAND", "SEND_MSG", "SEND_FILE", "GET_STATUS", "SHUTDOWN"]
        
        # Atributos de gestion
        self.stopThreads = False            # Flag para hilos
        self.writeLock = threading.Lock()   # Semaforo de escritura
        
        # Registro de la et en el fichero de ids
        with open(IDS_FILE, "r+") as f:
            data = json.load(f)
            data["ets"][self.id] = self.puerto
            f.seek(0)
            json.dump(data, f, indent=4)
            f.close()
        
        # Claves asimetricas
        self.privateKey = RSA.generate(ASIMETRIC_KEY_SIZE)
        self.publicKey = self.privateKey.publickey()
        self.privateKey = self.privateKey.exportKey("PEM")
        self.publicKey = self.publicKey.exportKey("PEM")

        # Para acabar correctamente el programa con Ctrl+C
        signal.signal(signal.SIGINT, self.signal_handler)
        
        # Hilo encargado de comunicacion con usuario
        self.clientThread = threading.Thread(target=self.client)
        self.clientThread.start()
        
        try:
            self.serverSocket.listen(ET_LISTEN_QUEUE_SIZE)
            while True:
                clientSocket, _ = self.serverSocket.accept()
                
                # Damos respuesta como servidor
                serverThread = threading.Thread(target=self.server, args=[clientSocket])
                serverThread.start()
                    
        except Exception as e:
            self.close_and_finish("Caught Error while listen: " + str(e), self.serverSocket)

##################### Metodos Genericos #####################
            
    def server(self, clientSocket):
        while not self.stopThreads:
            data = self.recv_all_data(clientSocket)     
            
            if self.stopThreads or data == b"":
                print(f"Server thread stopping...")
                break
            
            msg = json.loads(data.decode('utf-8'), strict=False)
            
            if 'ciphered' not in msg:
                clientSocket.sendall("Incorrect Message Format".encode())
                return
            
            sessionKey = None
            if msg['ciphered'] is True:
                signedMsgData, encodedMsgData, sessionKey = decrypt(msg['data'], self.privateKey)
                msgData = json.loads(encodedMsgData.decode('utf-8'), strict=False)
                
                if 'Instruction' not in msgData or ('droneID' in msgData and 'baseID' in msgData) \
                    or ('droneID' not in msgData and 'baseID' not in msgData):
                        clientSocket.sendall("Incorrect Message Format".encode())
                        return
                
                source, linkedDict = None, None
                if "droneID" in msgData:
                    source, linkedDict = "droneID", self.dronesLinked
                else: # "baseID" in msgData
                    source, linkedDict = "baseID", self.baseLinked
                
                if msgData[source] not in linkedDict:
                    clientSocket.sendall("Error: object not linked".encode())
                    return
                
                sourceID = msgData[source]                
                
                if (sourceID in self.dronesConnected and sessionKey != self.dronesConnected[sourceID][3] and self.dronesConnected[sourceID][3] != None) \
                    or (sourceID in self.baseLinked and sessionKey != self.baseLinked[4] and self.baseLinked[4] != None):
                        clientSocket.sendall("Incorrect session key")
                        return
                
                sourcePublicKey = linkedDict[msgData[source]][1] if source == "droneID" else linkedDict[2]
                if check_sign(signedMsgData, encodedMsgData, sourcePublicKey) == False:
                    clientSocket.sendall("Verification error: Corrupted message".encode())
                    return
            else:
                msgData = msg["data"]
                
                if 'Instruction' not in msgData or ('droneID' in msgData and 'baseID' in msgData) \
                    or ('droneID' not in msgData and 'baseID' not in msgData):
                        clientSocket.sendall("Incorrect Message Format".encode())
                        return
            
            if msgData["Instruction"] != "TELEMETRY":
                print("At Server ET: %s" % msgData["Instruction"])

            if msgData["Instruction"] not in self.instr:
                clientSocket.sendall(msgData["Instruction"] + " Instruction not supported".encode())
                return
            
            source = "droneID" if "droneID" in msgData else "baseID"
            
            if (msgData["Instruction"] == "TELEMETRY" and msgData["droneID"] not in self.dronesConnected) or \
                (msgData["Instruction"] != "LINK" and msgData[source] not in self.dronesLinked and msgData[source] not in self.baseLinked):
                    clientSocket.sendall("Cliente no conocido".encode())
                    print(f"Mensaje recibido de cliente no conocido {msgData[source]}")
                    return
                
            responseData = {
                "Instruction": msgData["Instruction"],
                "etID": self.id
            }
            
            if source == "droneID":
                if msgData["Instruction"] == "LINK":
                    responseData["response"] = self.recv_link(msgData, responseData)
                elif msgData["Instruction"] ==  "UNLINK":
                    responseData["response"] = self.recv_unlink(msgData)
                elif msgData["Instruction"] ==  "CONNECT":
                    responseData["response"] = self.recv_connect(msgData, sessionKey)
                elif msgData["Instruction"] ==  "DISCONNECT":
                    responseData["response"] = self.recv_disconnect(msgData)
                elif msgData["Instruction"] ==  "TELEMETRY":
                    responseData["response"] = self.recv_telemetry(msgData)
            else:   # source == "baseID"
                if msgData["Instruction"] ==  "FLY":
                    responseData["response"] = self.recv_fly(msgData)
                elif msgData["Instruction"] ==  "LAND":
                    responseData["response"] = self.recv_land(msgData)
                elif msgData["Instruction"] ==  "GET_STATUS":
                    responseData["response"] = self.recv_get_status(msgData, responseData)
                elif msgData["Instruction"] ==  "SHUTDOWN":
                    responseData["response"] = self.recv_shutdown(msgData)
                elif msgData["Instruction"] ==  "SEND_MSG":
                    responseData["response"] = self.recv_msg(msgData)
                elif msgData["Instruction"] ==  "SEND_FILE":
                    responseData["response"] = self.recv_file(msgData)
            
            responseData = json.dumps(responseData)
            responseData = responseData.encode()
            if msg["ciphered"] == True and msgData["Instruction"] != "LINK":
                responseData, _ = encsign(responseData, self.privateKey, sourcePublicKey, sessionKey)
            if msgData["Instruction"] != "TELEMETRY":
                clientSocket.sendall(responseData)

        print("Finish Comunication")        
        clientSocket.close()      


    def client(self):
        import re
        while True:
            try:
                comand = input("Write command ET " + self.id + ": ")
                if self.stopThreads:
                    print("Drone client thread closing...")
                    break
                pattern = "(((--send_file) \d+ [^ -]\S* [^ -]\S*)|(--send_msg) \d+ [^ -]\S* \"[\w\s]*\")|(--\S+ [^ -]\S*)|(--disconnect)|(--close)|(--help)"
                if(re.match(pattern, comand)):
                    for m in re.finditer(pattern, comand):
                        aux = m.group(0).split(" ")
                        if aux[0]=="--fly":
                            self.fly(aux[1])
                        if aux[0]=="--land":
                            self.land(aux[1])
                        if aux[0]=="--disconnect":
                            self.disconnect(aux[1])
                        if aux[0]=="--link":
                            self.link(aux[1])
                        if aux[0]=="--unlink":
                            self.unlink(aux[1])
                        if aux[0]=="--send_msg":
                            self.send_msg(aux[1], aux[2], " ".join(aux[3:]))
                        if aux[0]=="--send_file":
                            self.send_file(aux[1], aux[2], aux[3])
                        if aux[0]=="--close":
                            self.close()
                            return #debería desconectarse de todos sus drones
                        if aux[0]=="--help":
                            print("""usage: estacionTerrestre.py [--help] [--link LINK] [--unlink UNLINK] [--connect CONNECT]
                [--disconnect] [--close] [--send_msg [0:base, 1:et] destID "[msg]"] [--send_file [0:base, 1:et] destID , filename]""")
                else:
                        print("No good formed command detected")
                
            except Exception as e:
                print(
                    "Error on command client: " + str(e)
                )

    def close(self):
        #cerramos todas las conexiones
        self.stopThreads = True
        for dr in list(self.dronesConnected.keys()):
            print(dr)
            self.disconnect(dr)
        self.dronesConnected.clear()
        if self.baseLinked[3]!=None:
            self.baseLinked[3].close()
        os.kill(os.getpid(), signal.SIGINT)

        
    def close_and_finish(self, errorMsg, socket):
        print(errorMsg)
        socket.close()
        try:
            self.stopThreads = True
        except Exception as e:
            print("Error on close threads " + str(e))
        #os.kill(os.getpid(), signal.SIGINT)
        sys.exit()
    
    
    def signal_handler(self, nsignal, frame):
        self.close_and_finish("\nShutdown Estación Terrestre " + self.id, self.serverSocket)
    
    
    def recv_all_data(self, recvSocket):
        data = b""
        
        #recvSocket.setblocking(False) # Si no hay datos para leer, crea excepcion
        
        # Espera a leer algo
        while not self.stopThreads and data == b"":
            try:
                data += recvSocket.recv(BUFFER_SIZE)
                recvSocket.setblocking(False)
            except socket.error:
                pass
        
        # Lee todo
        try:
            while not self.stopThreads:
                data += recvSocket.recv(BUFFER_SIZE)
                recvSocket.setblocking(False)
        except socket.error:
            pass
        
        return data
    
##################### Metodos Server #####################

        ################# Drone #################

    def recv_link(self, msg, responseData):
        # Comprobar entradas opcionales
        if "dronePort" not in msg and "publicKey" not in msg:
            return False
        
        drID = msg["droneID"]
        dronePort = msg["dronePort"]
        publicKey = msg["publicKey"]

        # Comprobar si droneID y puertos son correctos
        with open(IDS_FILE, "r+") as f:
            data = json.load(f)
            
        if drID not in data["drones"] or data["drones"][drID] != dronePort:
            return False
        
        responseData["etPort"] = self.puerto
        responseData["publicKey"] = self.publicKey.decode('utf-8')
        
        # Añadir entrada al diccionario
        self.dronesLinked[drID] = [dronePort, publicKey]

        return True


    def recv_unlink(self, msg):
        # Comprobar que drone esta vinculado
        if msg["droneID"] not in self.dronesLinked:
            return False
        
        drID = msg["droneID"]
        self.dronesLinked.pop(drID) #quitamos ese drone de la lista de drones linkeados
        
        return True
    
    
    def recv_connect(self, msg, sessionKey):
        drID = msg["droneID"]
        if(not drID in self.dronesLinked):
            return False
        
        clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        clientSocket.connect(("localhost", self.dronesLinked[drID][0]))
        
        #añadimos el dron al set de drones conectados
        self.dronesConnected[drID] = [False, -1, clientSocket, sessionKey]
        return True
        

    def recv_disconnect(self, msg):
        #compruebo que estén todos los parámetros que necesito
        if(not ("droneID" in msg)):
            return False
        drID = msg["droneID"]
        if( not drID in self.dronesConnected):
            return False
        #eliminamos ese dron de la lista de drones conextados
        self.dronesConnected[drID][2].close()
        self.dronesConnected.pop(drID)
        return True
        

    def recv_telemetry(self, msg):
        if(not ("droneID" in msg and "flying" in msg and "battery" in msg)):
            return False
        if(not msg["droneID"] in self.dronesConnected):
            return False
        path = ET_TELEMETRY_FOLDER + self.id
        self.dronesConnected[msg["droneID"]][:2] = [msg["flying"], msg["battery"]]
        #si no existe la carpeta de telemetría de está et
        #cambiar a un solo fichero
        if(not os.path.exists(path)):
            os.makedirs(path) #creo la carpeta de telemetría de esta ET
        with self.writeLock:
            with open(path + "/" + msg["droneID"], "a+") as f:
                f.write(datetime.now().strftime("%Y-%m-%d %H:%M:%S") + " " + str(msg["flying"]) + " " + str(msg["battery"]) + "\n")
        return True

        ################# Base #################
        
    def recv_fly(self, msg):     
        if(not ("baseID" in msg and "destID" in msg)):
            return False
        
        if(msg["baseID"] != self.baseLinked[0] or msg["destID"] not in self.dronesConnected):
            return False
        
        return self.fly(msg["destID"])
    

    def recv_land(self, msg):
        if(not ("baseID" in msg and "destID" in msg)):
            return False
        
        if(msg["baseID"] != self.baseLinked[0] or msg["destID"] not in self.dronesConnected):
            return False
        
        return self.land(msg["destID"])
    

    def recv_msg(self, msg):
        if(not ("baseID" in msg and "destID" in msg and "msg" in msg)):
            return False
        
        if(msg["baseID"]!=self.baseLinked[0] or msg["destID"]!=self.id):
                return False
            
        print("Message from: " + msg["sourceID"] +  " received: " + msg["msg"])
        return True


    def recv_file(self, msg):
        if(not ("baseID" in msg and "destID" in msg and "msg" in msg and "fileName" in msg and "data" in msg)):
            return False
        
        if(msg["baseID"]!=self.baseLinked[0] or msg["destID"]!=self.id):
                return False
            
        with open(msg["filename"], "wb") as f:
            f.write(bytes(msg["data"], 'utf-8'))
            
        return True


    def recv_get_status(self, msg, responseData):
        if(self.baseLinked[0] == None):
            return False
        
        drConnected = ""
        drLinked = ""
        for dr in self.dronesConnected:
            drConnected += dr + ": Flying=" + str(self.dronesConnected[dr][0]) + ", battery=" + str(self.dronesConnected[dr][1]) + "\n"
        for dr in self.dronesLinked:
            drLinked += str(self.dronesLinked[dr][0]) + "\n"
        
        responseData["Dr connected"] = drConnected
        responseData["Dr linked"] = drLinked
        return True
    
    
    def recv_shutdown(self, msg):
        if(self.baseLinked[0] == None):
            print("Done shutdown")
            return True
        
        #hacemos que todos los drones aterricen y se desconecten
        for dr in list(self.dronesConnected.keys()):
            self.land(dr)
            self.disconnect(dr)
            
        self.dronesConnected.clear()
        return True

##################### Metodos Cliente #####################

        ################# Drone #################
        
    def fly(self, droneID):
        if(not droneID in self.dronesConnected):
            print("Drone with id: " + droneID + " not connected with ET")
            return
        
        dronePublicKey = self.dronesLinked[droneID][1]
        try:   
            data = ("{\"Instruction\": \"FLY\", " + \
                     "\"etID\": \"" + str(self.id) + "\"}").encode()
            data, _ = encsign(data, self.privateKey, dronePublicKey, self.dronesConnected[droneID][3])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            self.dronesConnected[droneID][2].sendall(msg)
            
            data = self.recv_all_data(self.dronesConnected[droneID][2])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, dronePublicKey) == False:
                print("Verification error: Corrupted message")
                return
            
            try:
                msg = json.loads(data.decode("utf-8"), strict=False)
                print(msg)
                return
            
            except Exception as e:
                print("Exception on fly "+ droneID + ": " + str(e))
                return
            
        except socket.error as exc:
            print("Error trying to fly from Drone " + droneID + "...")
            return
        
        
    def land(self, droneID):
        if(not droneID in self.dronesConnected):
            print("Drone with id: " + droneID + " not connected with ET")
            return False
        
        dronePublicKey = self.dronesLinked[droneID][1]
        try: 
            data = ("{\"Instruction\": \"LAND\", " + \
                     "\"etID\": \"" + str(self.id) + "\"}").encode()
            data, _ = encsign(data, self.privateKey, dronePublicKey, self.dronesConnected[droneID][3])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode() # Borrar cuando cifrado
            self.dronesConnected[droneID][2].sendall(msg)
            
            data = self.recv_all_data(self.dronesConnected[droneID][2])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, dronePublicKey) == False:
                print("Verification error: Corrupted message")
                return
            try:
                msg = json.loads(data.decode("utf-8"), strict=False)
                return msg["response"]
            except Exception as e:
                print("Exception on land "+ droneID + ": " + str(e))
                return False
        except socket.error as exc:
            print("Error trying to land from Drone " + droneID + "...")
            return False
        
        
    def disconnect(self, droneID):
        if(not droneID in self.dronesConnected):
            print("Drone with id: " + droneID + " not connected with ET")
            return
        
        dronePublicKey = self.dronesLinked[droneID][1]
        try:    
            data = ("{\"Instruction\": \"DISCONNECT\", " + \
                     "\"etID\": \"" + str(self.id) + "\"}").encode()
            data, sessionKey = encsign(data, self.privateKey, dronePublicKey, self.dronesConnected[droneID][3])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            self.dronesConnected[droneID][2].sendall(msg)
            
            data = self.recv_all_data(self.dronesConnected[droneID][2])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, dronePublicKey) == False:
                print("Verification error: Corrupted message")
                return
            
            self.dronesConnected[droneID][2].close()
            self.dronesConnected.pop(droneID)
            
            try:
                msg = json.loads(data, strict=False)
                return
            
            except Exception as e:
                print("Exception on disconnect "+ droneID + ": " + str(e))
                return
            
        except socket.error as exc:
            print("Error trying to disconect from Drone " + droneID + "...")
            return

        ################# Base #################
        
    def link(self, baseID):
        with open(IDS_FILE, "r+") as f:
            data = json.load(f)   
        basePort = data["bases"][baseID]
        
        #abrimos socket de cliente
        clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            #nos conectamos
            clientSocket.connect(("localhost", basePort))
            
            # Primero envia sin cifrar para darse a conocer
            data = ("{\"Instruction\": \"LINK\", " + \
                     "\"etID\": \"" + str(self.id) + "\", " + \
                     "\"etPort\":" + str(self.puerto) + ", " + \
                     "\"publicKey\": \"").encode() + self.publicKey +  "\"}".encode()

            msg = "{\"ciphered\": false, \"data\": ".encode() + data + "}".encode()
            clientSocket.sendall(msg)
            
            data = self.recv_all_data(clientSocket)
            try:
                msg = json.loads(data.decode("utf-8"), strict=False)
                if msg["response"] == True:
                    basePublicKey = msg["publicKey"]
                    self.baseLinked = (baseID, basePort, basePublicKey, clientSocket, None)
                else:
                    print("Link failure")
                    return
                
            except Exception as e:
                print("Exception on link "+ baseID + ": " + str(e))
                return
            
            # Luego cifra el mensaje con los mismos datos para que pueda entrar al metodo
            # que recibe la info de link
            data = ("{\"Instruction\": \"LINK\", " + \
                     "\"etID\": \"" + str(self.id) + "\", " + \
                     "\"etPort\":" + str(self.puerto) + ", " + \
                     "\"publicKey\": \"").encode() + self.publicKey +  "\"}".encode()
            data, sessionKey = encsign(data, self.privateKey, basePublicKey, None)
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            clientSocket.sendall(msg)
            
            data = self.recv_all_data(clientSocket)
            
            signedData, data, _ = decrypt(data, self.privateKey)            
            if check_sign(signedData, data, basePublicKey) == False:
                print("Verification error: Corrupted message")
                return
            
            try:
                msg = json.loads(data.decode("utf-8"), strict=False)
                if msg["response"] == True:
                    self.baseLinked = (baseID, basePort, basePublicKey, clientSocket, sessionKey)
                else:
                    print("Link failure")
                    self.baseLinked = (None, -1, None, None, None)
                    return
                
            except Exception as e:
                print("Exception on link "+ baseID + ": " + str(e))
                return
            
        except socket.error as exc:
            print("Error trying to link from BO " + baseID + "...")
            return
    
    
    def unlink(self, baseID):
        if(baseID != self.baseLinked[0]):
            return
        
        basePublicKey = self.baseLinked[2]
        try:
            data = ("{\"Instruction\": \"UNLINK\", " + \
                     "\"etID\": \"" + str(self.id) + "\"}").encode()
            data, _ = encsign(data, self.privateKey, basePublicKey, self.baseLinked[4])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            self.baseLinked[3].sendall(msg)
            
            data = self.recv_all_data(self.baseLinked[3])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, basePublicKey) == False:
                print("Verification error: Corrupted message")
                return
            
            try:
                msg = json.loads(data, strict=False)
                
                self.baseLinked[3].close()
                self.baseLinked = (None, -1, None, None, None)
                return
            
            except Exception as e:
                print("Exception on unlink "+ baseID + ": " + str(e))
                return
            
        except socket.error as exc:
            print("Error trying to unlink from Drone " + baseID + "...")
            return
        
        
    def send_msg(self, dest, destID, msg):
        dest = int(dest)
        
        if(dest==0 and destID != self.baseLinked[0]):
            print("Base dest id does not match with linked base id")
            return False
        
        if(not dest in range(2)):
            print("Dest code not in range [0: base, 1:other et]")
            return False
    
        basePublicKey = self.baseLinked[2]
        try:
            data = ("{\"Instruction\": \"SEND_MSG\", " + \
                     "\"etID\": \"" + str(self.id) + "\", " + \
                     "\"sourceID\": \"" + str(self.id) + "\", " + \
                     "\"destID\": \"" + str(destID) + "\", " + \
                     "\"msg\": " + msg + "}").encode()
            data, _ = encsign(data, self.privateKey, basePublicKey, self.baseLinked[4])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            self.baseLinked[3].sendall(msg)
            
            data = self.recv_all_data(self.baseLinked[3])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, basePublicKey) == False:
                print("Verification error: Corrupted message")
                return
            
            try:
                msg = json.loads(data, strict=False)
                return
            
            except Exception as e:
                print("Exception on send_msg "+ destID + ": " + str(e))
                return
            
        except socket.error as exc:
            print("Error on send message " + destID + "...")
            return
        

    def send_file(self, dest, destID, fileName):
        dest = int(dest)
        
        if(dest==0 and destID!=self.baseLinked[0]):
            print("Base dest id does not match with linked base id")
            return False
        
        if(not dest in range(2)):
            print("Dest code not in range [0: base, 1:other et]")
            return False
        
        basePublicKey = self.baseLinked[2]
        try:
            with open(fileName, "rb") as f:
                bytes_read = f.read() #leemos el fichero a mandar
                if(not bytes_read):
                    return False
        
            data = ("{\"Instruction\": \"SEND_FILE\", " + \
                     "\"etID\": \"" + str(self.id) + "\", " +
                     "\"sourceID\": \"" + str(self.id) + "\", " + \
                     "\"destID\": \"" + str(destID) + "\", " + \
                     "\"fileName\": \"" + fileName + "\", " + \
                     "\"data\": \"").encode() + bytes_read + "\"}".encode()
            data, _ = encsign(data, self.privateKey, basePublicKey, self.baseLinked[4])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            self.baseLinked[3].sendall(msg)
            
            data = self.recv_all_data(self.baseLinked[3])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, basePublicKey) == False:
                print("Verification error: Corrupted message")
                return
            
            try:
                msg = json.loads(data, strict=False)
                return
            
            except Exception as e:
                print("Exception on send_file "+ destID + ": " + str(e))
                return            
            
        except socket.error as exc:
            print("Error on send file " + destID + "...")
            return
        
        
if __name__ == '__main__':

    if len(sys.argv) != 3:
        sys.exit("ERROR: faltan argumentos\n" +
            f"Sintaxis: python {sys.argv[0]} [id] [puerto]")

    ################################################
    #     Aqui va la restauracion del estado
    #
    #   Si existe estado anterior: Restaurarlo
    ################################################

    id, puerto = sys.argv[1], int(sys.argv[2])
    drone = estacionTerrestre(id, puerto)

    ################################################
    #       Aqui va el guardado del estado
    #
    #   Si usuario quiere guardar estado: Guardar
    ################################################
