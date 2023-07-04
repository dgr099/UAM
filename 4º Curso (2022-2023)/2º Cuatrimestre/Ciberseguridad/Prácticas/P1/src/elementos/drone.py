from Crypto.PublicKey import RSA
from src.utils.crypto import encsign, decrypt, check_sign

import socket, json, time, sys, signal, threading, os

IDS_FILE = "./data/ids.json"
BUFFER_SIZE = 1024
ASIMETRIC_KEY_SIZE = 2048
DRONE_LISTEN_QUEUE_SIZE = 5

class Drone:
    def __init__(self, drID: str, puerto: int):
        
        try: 
            # Crea socket
            self.serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Permite reusar el puerto
            
            # Abre puerto
            self.serverSocket.bind(("localhost", puerto))
            
        except socket.error as exc:
            self.close_and_finish("Caught exception socket.error: " + str(exc), self.serverSocket)
            
        # Atributos del drone
        self.id = drID
        self.puerto = puerto    
        self.battery = 100
        self.flying = False
        
        # Atributos de conexion
        self.etConnected = (None, -1, None, None, None) # (etID, puerto, publicKey, socket, sessionKey)
        self.etsLinked = {}                             # {'etID': [puerto, publicKey]}
        
        # Instrucciones soportadas para server
        self.instr = ["FLY", "LAND", "DISCONNECT"]
        
        # Atributos de gestion
        self.stopThreads = False    # Flag para hilos
        
        # Registro del drone en el fichero de ids
        with open(IDS_FILE, "r+") as f:
            data = json.load(f)
            data["drones"][self.id] = self.puerto
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
            self.serverSocket.listen(DRONE_LISTEN_QUEUE_SIZE)
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
            
            sourcePublicKey, sessionKey = None, None
            if msg['ciphered'] is True:
                signedMsgData, encodedMsgData, sessionKey = decrypt(msg['data'], self.privateKey)
                msgData = json.loads(encodedMsgData.decode('utf-8'), strict=False)
                
                if sessionKey != self.etConnected[4] and self.etConnected[4] != None:
                    clientSocket.sendall("Incorrect session key")
                
                if 'Instruction' not in msgData and 'etID' not in msgData:
                    clientSocket.sendall("Incorrect Message Format".encode())
                    return
                
                etID = msgData["etID"]
                
                if etID not in self.etsLinked:
                    clientSocket.sendall("Error: object not linked".encode())
                    return
                
                sourcePublicKey = self.etsLinked[etID][1]
                if check_sign(signedMsgData, encodedMsgData, sourcePublicKey) == False:
                    clientSocket.sendall("Verification error: Corrupted message".encode())
                    return
            else:
                msgData = msg["data"]
                
                if 'Instruction' not in msgData and 'etID' not in msgData:
                    clientSocket.sendall("Incorrect Message Format".encode())
                    return
            
            if msgData["Instruction"] not in self.instr:
                clientSocket.sendall((msgData["Instruction"] + " Instruction not supported").encode())
                return
            
            responseData = {
                'Instruction': msgData["Instruction"],
                'droneID': self.id
            }
            
            print("At Server Drone: %s" % msgData["Instruction"])
            if msgData["Instruction"] == "FLY":
                responseData["response"] = self.recv_fly()
            elif msgData["Instruction"] ==  "LAND":
                responseData["response"] = self.recv_land()
            elif msgData["Instruction"] == "DISCONNECT": 
                responseData["response"] = self.recv_disconnect(msgData)
            
            responseData = json.dumps(responseData)
            responseData = responseData.encode()
            if msg["ciphered"] == True:
                responseData, _ = encsign(responseData, self.privateKey, sourcePublicKey, sessionKey)
            clientSocket.sendall(responseData)

        print("Finish Comunication")
        clientSocket.close()


    def client(self):
        import re
        while True:
            try:
                comand = input("Write command Dr " + self.id + ": ")
                if self.stopThreads:
                    print("Drone client thread closing...")
                    break
                pattern = "(--\S+ [^ -]\S*)|(--disconnect)|(--close)|(--help)"
                if(re.match(pattern, comand)):
                    for m in re.finditer(pattern, comand):
                        aux = m.group(0).split(" ")
                        if aux[0]=="--link":
                            self.link(aux[1])
                        if aux[0]=="--unlink":
                            self.unlink(aux[1])
                        if aux[0]=="--connect":
                            self.connect(aux[1])
                        if aux[0]=="--disconnect":
                            self.disconnect()
                        if aux[0]=="--close":
                            self.close()
                            return
                        if aux[0]=="--help":
                            print("""usage: drone.py [--help] [--link LINK] [--unlink UNLINK] [--connect CONNECT]
                [--disconnect] [--close]""")
                else:
                        print("No good formed command detected")
                
            except Exception as e:
                print(
                    "Error on command client: " + str(e)
                )

    def close(self):
        self.stopThreads = True
        self.disconnect() #primero llama a desconectar
        os.kill(os.getpid(), signal.SIGINT) #para que pare el server

    def close_and_finish(self, errorMsg, socket):
        print(errorMsg)
        socket.close()
        try:
            self.stopThreads = True
        except Exception as e:
            print("Error on close threads " + str(e))
        sys.exit()


    def signal_handler(self, nsignal, frame):
        self.close_and_finish("\nShutdown drone " + self.id, self.serverSocket)
        
        
    def recv_all_data(self, recvSocket):
        data = b""
        
        recvSocket.setblocking(False) # Si no hay datos para leer, crea excepcion
        
        # Espera a leer algo
        while not self.stopThreads and data == b"":
            try:
                data += recvSocket.recv(BUFFER_SIZE)
            except socket.error:
                pass
        
        # Lee todo
        try:
            while not self.stopThreads:
                data += recvSocket.recv(BUFFER_SIZE)
        except socket.error:
            pass
        
        return data

##################### Metodos Servidor #####################

    def recv_fly(self):
        if self.flying == True:
            return False
        
        self.battery = 100
        self.flying = True
        
        # Lanzamos un hilo para el discharge
        batteryThread = threading.Thread(target=self.discharge)
        batteryThread.start()
        return True     

    def recv_land(self):
        if self.flying == False:
            return False
        
        self.flying = False
        return True
    
    
    def recv_disconnect(self, msg):
        if msg["etID"] != self.etConnected[0]:
            return False
        
        self.etConnected[3].close()
        self.etConnected = (None, -1, None, None, None)
        return True

##################### Metodos Cliente #####################

    def link(self, etID: str):
        print("Linking to ET " + etID + "...")
        
        # Comprobar si ya esta vinculada
        if etID in self.etsLinked:
            print(f"Error linking with et {etID}. Already registered")
            return
        
        # Buscar id en fichero de ids
        with open(IDS_FILE, "r+") as f:
            data = json.load(f)
        if etID not in data["ets"]:
            print(f"Error linking with et {etID}. Not registered in file {IDS_FILE}")
            return
        
        etPort = data["ets"][etID]
        clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            clientSocket.connect(("localhost", etPort)) #me intento conectar con la ET
            
            data = ("{\"Instruction\": \"LINK\", " + \
                     "\"droneID\": \"" + str(self.id) + "\", " + \
                     "\"dronePort\": " +  str(self.puerto) + ", " + \
                     "\"publicKey\": \"").encode() + self.publicKey + "\"}".encode()
            
            msg = "{\"ciphered\": false, \"data\": ".encode() + data + "}".encode()
            clientSocket.sendall(msg)
            
            data = self.recv_all_data(clientSocket)
            data = json.loads(data.decode("utf-8"), strict=False)
            
            self.etsLinked[data['etID']] = [int(data['etPort']), data['publicKey']]            

        except Exception as e:
            print("Error trying to link to ET " + etID + ": " + str(e))
            
        clientSocket.close()


    def unlink(self, etID: str):
        print("Unlinking from ET " + etID + "...")
        
        if etID not in self.etsLinked:
            print(f"Error unlinked et {etID}. Not linked")
            return
        etPublicKey = self.etsLinked[etID][1]
    
        clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            clientSocket.connect(("localhost", self.etsLinked[etID][0]))
            
            data = ("{\"Instruction\": \"UNLINK\", " + \
                     "\"droneID\": \"" + str(self.id) + "\"}").encode()
            if etID in self.etConnected:
                data, _ = encsign(data, self.privateKey, etPublicKey, self.etConnected[4])
                msg = "{\"ciphered\": true, \"data\": ".encode() + data + "}".encode()
            else:
                msg = "{\"ciphered\": false, \"data\": ".encode() + data + "}".encode() # Borrar cuando cifrado
            clientSocket.sendall(msg)
            
            data = self.recv_all_data(clientSocket)
            if etID in self.etConnected:
                signedData, data, _ = decrypt(data, self.etConnected[2])
                if check_sign(signedData, data, self.etConnected[2]) == False:
                    print("Verification error: Corrupted message")
                    return
                print("Desconecting from ET...")
                self.etConnected(None, -1, None, None, None)
            data = json.loads(data.decode('utf-8'), strict=False)
                        
            self.etsLinked.pop(etID)
        
        except Exception as e:
            print("Error trying to unlink from ET " + etID + ": " + str(e))

        clientSocket.close()



    def connect(self, etID: str):
        print("Connecting to ET " + etID + "...")
        
        if(etID not in self.etsLinked):
            print("Connect error, ET not linked")
            return False
        etPort = self.etsLinked[etID][0] #obtengo el puerto de la ET a la que quiero escribir
        etPublicKey = self.etsLinked[etID][1]

        if self.etConnected[0] == None:
            clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            try:
                clientSocket.connect(("localhost", etPort)) #me intento conectar con la ET
                data = ("{\"Instruction\": \"CONNECT\", " + \
                         "\"droneID\": \"" + str(self.id) + "\" }").encode()
                data, sessionKey = encsign(data, self.privateKey, etPublicKey, None)
            
                msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
                clientSocket.sendall(msg)
                
                data = self.recv_all_data(clientSocket)
                
                signedData, data, _ = decrypt(data, self.privateKey)
                if check_sign(signedData, data, self.etsLinked[etID][1]) == False:
                    print("Verification error: Corrupted message")
                    return
                
                msg = json.loads(data.decode('utf-8'), strict=False)
                
                if "response" not in msg or msg["response"] == False:
                    print("Connecting error...")
                    return
                
                self.etConnected = (etID, etPort, self.etsLinked[etID][1], clientSocket, sessionKey)
                telemetryThread = threading.Thread(target=self.telemetry)
                telemetryThread.start()
                return
            
            except Exception as e:
                print("Error trying to connect with ET " + etID + "... " + str(e))
                return
        else:
            print("Drone " + self.id + " is connected to the ET " + self.etConnected[0])
            return

    
    # Si lo recibe por el otro puerto, sirve para confirmar la desconexion
    def disconnect(self):
        if self.etConnected[0] != None:
            print("Disconnecting from ET " + self.etConnected[0] + "...")
            try: 
                data = ("{\"Instruction\": \"DISCONNECT\", " + \
                         "\"droneID\": \"" + str(self.id) + "\"}").encode()
                data, _ = encsign(data, self.privateKey, self.etConnected[2], self.etConnected[4])
                
                msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
                self.etConnected[3].sendall(msg)
                
                data = self.recv_all_data(self.etConnected[3])
                
                self.etConnected[3].close()
                self.etConnected = (None, -1, None, None, None)
            except Exception as e:
                print("Error trying to disconnect from ET " + self.etConnected[0] + "... " + str(e))
                return False
        else:
            print("Drone " + self.id + " is not connected to a ET")
            return False
        
    
    def telemetry(self):
        print("sending telemetry to: " + self.etConnected[0] +"...")
        while self.etConnected[0] != None and not self.stopThreads:
            try:
                data = "{\"Instruction\": \"TELEMETRY\", \"droneID\": \"" + str(self.id) + "\", \"flying\": " + str(self.flying).lower() + ", \"battery\": " + str(self.battery) + "}"
                self.etConnected[3].send("{\"ciphered\": false, \"data\": ".encode() + data.encode() + " }".encode())
                time.sleep(2)
            except Exception as e:
                print("Error sending telemtry to ET " + str(self.etConnected[0]) + "..." + str(e))
                return
                #break
        print("Telemetry finished")
        
        
    def discharge(self):
        while self.flying is True and self.battery > 0.0:
            time.sleep(60/100)
            self.battery -= 1 # Baja un 1%
        self.flying = False

        
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
    drone = Drone(id, puerto)

    ################################################
    #       Aqui va el guardado del estado
    #
    #   Si usuario quiere guardar estado: Guardar
    ################################################
