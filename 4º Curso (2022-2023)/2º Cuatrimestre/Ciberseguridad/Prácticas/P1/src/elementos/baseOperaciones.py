from Crypto.PublicKey import RSA
from datetime import datetime
from src.utils.crypto import encsign, decrypt, check_sign

import threading, signal, os, sys, json, socket

IDS_FILE = "./data/ids.json"
BO_STATUS_FOLDER = "./data/status/"

BUFFER_SIZE = 1024
ASIMETRIC_KEY_SIZE = 2048

BO_LISTEN_QUEUE_SIZE = 10

class baseOperaciones:
    def __init__(self, boID: str, puerto: int):
        try: 
            # Crea socket
            self.serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Permite reusar el puerto
            
            # Abre puerto
            self.serverSocket.bind(("localhost", puerto))
            
        except socket.error as exc:
            self.close_and_finish("Caught exception socket.error: " + str(exc), self.serverSocket)
        
        # Atributos de la base
        self.id = boID
        self.puerto = puerto
        
        # Atributos de conexion
        self.etsLinked = {} # {'ET01': [port, publicKey, socket, sessionKey]}
        
        # Instrucciones soportadas para server
        self.instr = ["LINK", "UNLINK", "SEND_MSG", "SEND_FILE"]

        # Atributos de gestion
        self.stopThreads = False    # Flag para hilos

        with open(IDS_FILE, "r+") as f: #escribo mi puerto en el fichero de datos 
            data = json.load(f)
            data["bases"][self.id] = self.puerto
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
            self.serverSocket.listen(BO_LISTEN_QUEUE_SIZE)
            while True:
                clientSocket, _ = self.serverSocket.accept()
                
                # Damos respuesta como servidor
                serverThread = threading.Thread(target=self.server, args=[clientSocket])
                serverThread.start()
                    
        except Exception as e:
            self.close_and_finish("Caught Error while listen: " + str(e), self.serverSocket)

    ####### Métodos Genéricos ####################
    def server(self, clientSocket):
        # Leer todo el mensaje
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
                
                if 'Instruction' not in msgData or 'etID' not in msgData:
                    clientSocket.sendall("Incorrect Message Format".encode())
                    return
                
                if msgData['etID'] not in self.etsLinked:
                    clientSocket.sendall("Error: object not linked".encode())
                    return
                
                sourcePublicKey = self.etsLinked[msgData['etID']][1]
                if check_sign(signedMsgData, encodedMsgData, sourcePublicKey) == False:
                    clientSocket.sendall("Verification error: Corrupted message".encode())
                    return
            else:
                msgData = msg["data"]
                
                if 'Instruction' not in msgData or 'etID' not in msgData:
                    clientSocket.sendall("Incorrect Message Format".encode())
                    return
            
            print("At Server BO: %s" % msgData["Instruction"])

            if msgData["Instruction"] not in self.instr:
                clientSocket.sendall(msgData["Instruction"] + " Instruction not supported".encode())
                return
            if (msgData["Instruction"] != "LINK" and msgData["etID"] not in self.etsLinked):
                    clientSocket.sendall("Cliente no conocido".encode())
                    print(f"Mensaje recibido de cliente no conocido {msgData['etID']}")
                    return
                
            responseData = {
                "Instruction": msgData["Instruction"],
                "baseID": self.id
            }
            
            if msgData["Instruction"] == "LINK":
                responseData["response"] = self.recv_link(msgData, responseData, sessionKey)
            elif msgData["Instruction"] ==  "UNLINK":
                responseData["response"] = self.recv_unlink(msgData)
            elif msgData["Instruction"] ==  "SEND_MSG":
                responseData["response"] = self.recv_msg(msgData)
            elif msgData["Instruction"] ==  "SEND_FILE":
                responseData["response"] = self.recv_file(msgData)
            
            responseData = json.dumps(responseData)
            responseData = responseData.encode()
            if msg['ciphered'] == True:
                responseData, _ = encsign(responseData, self.privateKey, sourcePublicKey, sessionKey)
            clientSocket.sendall(responseData)

        print("Finish Comunication")   
        clientSocket.close()


    def client(self):
        import re
        while True:
            try:
                comand = input("Write command BO " + self.id + ": ")
                if self.stopThreads:
                    print("Drone client thread closing...")
                    break
                pattern = "(((--send_file) [^ -]\S* [^ -]\S*)|(--send_msg) [^ -]\S* \"[\w\s]*\")|(--\S+ [^ -]\S*)|(--get_status)|(--shutdown)|(--close)|(--help)"
                if(re.match(pattern, comand)):
                    for m in re.finditer(pattern, comand):
                        aux = m.group(0).split(" ")
                        if aux[0]=="--fly":
                            self.fly(aux[1])
                        if aux[0]=="--land":
                            self.land(aux[1])
                        if aux[0]=="--get_status":
                            self.get_status()
                        if aux[0]=="--shutdown":
                            self.shutdown()
                        if aux[0]=="--send_msg":
                            self.send_msg(aux[1], " ".join(aux[2:]))
                        if aux[0]=="--send_file":
                            self.send_file(aux[1], aux[2])
                        if aux[0]=="--close":
                            self.close()
                            return #debería desconectarse de todos sus drones
                        if aux[0]=="--help":
                            print("""usage: estacionTerrestre.py [--help] [--link LINK] [--unlink UNLINK] [--connect CONNECT]
                [--disconnect] [--close] [--send_msg destID "[msg]"] [--send_file destID, filename]""")
                else:
                        print("No good formed command detected")
                
            except Exception as e:
                import traceback
                traceback.print_exc()
                print(
                    "Error on command client: " + str(e)
                )


    def close(self):
        #cerramos todas las conexiones
        self.stopThreads = True
        for et in list(self.etsLinked.keys()):
            self.etsLinked[et][2].close()
            #self.dronesConnected[dr][2].close()
        self.etsLinked.clear()
        os.kill(os.getpid(), signal.SIGINT)


    def close_and_finish(self, errorMsg, socket):
        print(errorMsg)
        socket.close()
        try:
            self.stopThreads = True
        except Exception as e:
            print("Error on close threads " + str(e))
        sys.exit()


    def signal_handler(self, nsignal, frame):
        self.close_and_finish("\nShutdown Estación Terrestre " + self.id, self.serverSocket)
    
    
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

##################### Metodos Server #####################

    def recv_link(self, msg, responseData, sessionKey):
        if(not ("etID" in msg and "etPort" in msg and "publicKey" in msg)):
            return False
        
        etID = msg["etID"]
        etPort = msg["etPort"]
        publicKey = msg["publicKey"]
        
        #compruebo si droneID y puertos son correctos
        with open(IDS_FILE, "r+") as f:
            data = json.load(f)
            
        #si la info no coincide con lo del fichero
        if(data["ets"][etID] != etPort):
            return False
        
        self.etsLinked[etID] = [etPort, publicKey, None, None]
        
        if sessionKey == None:
            responseData["etPort"] = self.puerto
            responseData["publicKey"] = self.publicKey.decode('utf-8')
            return True
        
        #caso contrario
        try:
            clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            clientSocket.connect(("localhost", etPort))
            
            self.etsLinked[etID][2:] = [clientSocket, sessionKey]

            return True
        
        except Exception as e:
            print("Error on link ET: " + str(e))
            return False


    def recv_unlink(self, msg):        
        etID = msg["etID"]
        if(etID not in self.etsLinked):
            return False
        
        #cerramos la conexión
        self.etsLinked[etID][2].close()
        self.etsLinked.pop(etID)
        return True


    def recv_msg(self, msg):
        if(not ("destID" in msg and "msg" in msg and "sourceID" in msg)):
            print("mal formed")
            return False
        
        if msg["destID"] in self.etsLinked:
            etID = msg["destID"]
            print(f"Redirecting msg to {etID}...")
            
            etPublicKey = self.etsLinked[etID][1]
            try:
                data = ("{\"Instruction\": \"SEND_MSG\", " + \
                         "\"baseID\": \"" + str(self.id) + "\", " + \
                         "\"sourceID\": \"" + msg["sourceID"] + "\",  " + \
                         "\"destID\": \"" + etID + "\", " + \
                         "\"msg\": \"" + msg["msg"] + "\"}").encode()
                data, _ = encsign(data, self.privateKey, etPublicKey, self.etsLinked[etID][3])
                
                newMsg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
                self.etsLinked[etID][2].sendall(newMsg)
                
                data = self.recv_all_data(self.etsLinked[etID][2])
                signedData, data, _ = decrypt(data, self.privateKey)
                if check_sign(signedData, data, etPublicKey) == False:
                    print("Verification error: Corrupted message")
                    return

                try:
                    msg = json.loads(data, strict=False)
                    return msg["response"]
                
                except Exception as e:
                    print("Exception on send_msg "+ etID + ": " + str(e))
                    return False
                
            except socket.error as exc:
                print("Error on send message " + etID + "...")
                return False
            
        elif msg["destID"] == self.id:
            print("Message from: " + msg["sourceID"] +  " received: " + msg["msg"])
            return True
        
        else:
            return False
        
        
    def recv_file(self, msg):
        if(not ("destID" in msg and "sourceID" in msg and "fileName" in msg and "data" in msg)):
            print("mal formed")
            return False
        
        if msg["destID"] in self.etsLinked:
            etID = msg["destID"]
            print(f"Redirecting file to {etID}...")
            
            etPublicKey = self.etsLinked[etID][1]
            try:
                data = ("{\"Instruction\": \"SEND_FILE\", " + \
                         "\"baseID\": \"" + str(self.id) + "\", " + \
                         "\"sourceID\": \"" + msg["sourceID"] + "\", " + \
                         "\"destID\": \"" + etID + "\", " + \
                         "\"fileName\": \"" + msg["fileName"] + "\", " + \
                         "\"data\": \"" + msg["data"] + "\"}").encode()
                data, _ = encsign(data, self.privateKey, etPublicKey, self.etsLinked[etID][3])
                
                newMsg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
                self.etsLinked[etID][2].sendall(newMsg)
               
                data = self.recv_all_data(self.etsLinked[etID][2])
                signedData, data, _ = decrypt(data, self.privateKey)
                if check_sign(signedData, data, etPublicKey) == False:
                    print("Verification error: Corrupted message")
                    return
                
                try:
                    msg = json.loads(data, strict=False)
                    return msg["response"]
                
                except Exception as e:
                    print("Exception on send_msg "+ etID + ": " + str(e))
                    return False
                
            except socket.error as exc:
                print("Error on send message " + etID + "...")
                return False
            
        elif msg["destID"] == self.id:
            with open(msg["fileName"], "wb") as f:
                f.write(bytes(msg["data"], 'utf-8'))
            return True
        
        else:
            return False
    
##################### Metodos Cliente #####################
    
    def fly(self, droneID):
        for et in self.etsLinked.values():
            etPublicKey = et[1]
            data = ("{\"Instruction\": \"FLY\", " + \
                    "\"baseID\": \"" + str(self.id) + "\", " + \
                    "\"destID\": \"" + str(droneID) + "\"}").encode()
            data, _ = encsign(data, self.privateKey, etPublicKey, et[3])
                
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            et[2].sendall(msg)
            
            data = self.recv_all_data(et[2])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, etPublicKey) == False:
                print("Verification error: Corrupted message")
                return

            try:
                msg = json.loads(data, strict=False)
                if msg["response"] == True:
                    return
                
            except Exception as e:
                print("Exception on fly "+ droneID + ": " + str(e))
                return
        return


    def land(self, droneID):
        for et in self.etsLinked.values():
            etPublicKey = et[1]
            data = ("{\"Instruction\": \"LAND\", " + \
                     "\"baseID\": \"" + str(self.id) + "\", " + \
                     "\"destID\": \"" + str(droneID) + "\"}").encode()
            data, _ = encsign(data, self.privateKey, etPublicKey, et[3])
                
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            et[2].sendall(msg)
            
            data = self.recv_all_data(et[2])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, etPublicKey) == False:
                print("Verification error: Corrupted message")
                return
            
            try:
                msg = json.loads(data, strict=False)
                if msg["response"]==True:
                    return
                
            except Exception as e:
                print("Exception on land "+ droneID + ": " + str(e))
                return
            
        return


    def send_msg(self, etID, msg):
        if(etID not in self.etsLinked):
            return
        
        etPublicKey = self.etsLinked[etID][1]
        try:
            data = ("{\"Instruction\": \"SEND_MSG\", " + \
                     "\"baseID\": \"" + str(self.id) + "\", " + \
                     "\"sourceID\": \"" + self.id + "\", " + \
                     "\"destID\": \"" + etID + "\", " + \
                     "\"msg\": " + msg + "}").encode()
            data, _ = encsign(data, self.privateKey, etPublicKey, self.etsLinked[etID][3])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            self.etsLinked[etID][2].sendall(msg)
            
            data = self.recv_all_data(self.etsLinked[etID][2])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, etPublicKey) == False:
                print("Verification error: Corrupted message")
                return

            try:
                msg = json.loads(data, strict=False)
                return
            
            except Exception as e:
                print("Exception on send_msg "+ msg["destID"] + ": " + str(e))
                return
            
        except socket.error as exc:
            print("Error on send message " + msg["destID"] + "...")
            return


    def send_file(self, etID, fileName):
        if(etID not in self.etsLinked):
            return
        
        etPublicKey = self.etsLinked[etID][1]
        try:
            with open(fileName, "rb") as f:
                bytes_read = f.read() #leemos el fichero a mandar
                if(not bytes_read):
                    return
                
            data = ("{\"Instruction\": \"SEND_MSG\", " + \
                     "\"baseID\": \"" + str(self.id) + "\", " + \
                     "\"sourceID\": \"" + self.id + "\", " + \
                     "\"destID\": \"" + etID + "\", " + \
                     "\"fileName\": \"" + fileName + "\", " + \
                     "\"data\": \"").encode() + bytes_read + "\"}".encode()
            data, _ = encsign(data, self.privateKey, etPublicKey, self.etsLinked[etID][3])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            self.etsLinked[etID][2].sendall(msg)
            
            data = self.recv_all_data(self.etsLinked[etID][2])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, etPublicKey) == False:
                print("Verification error: Corrupted message")
                return

            try:
                msg = json.loads(data, strict=False)
                return
            
            except Exception as e:
                print("Exception on send_msg "+ etID + ": " + str(e))
                return
            
        except socket.error as exc:
            print("Error on send message " + etID + "...")
            return


    def get_status(self):
        data = ("{\"Instruction\": \"GET_STATUS\", " + \
                 "\"baseID\": \"" + str(self.id) + "\"}").encode()
        
        #pregunto a cada una de las et por su estado
        for etID in self.etsLinked:
            etPublicKey = self.etsLinked[etID][1]
            data, _ = encsign(data, self.privateKey, etPublicKey, self.etsLinked[etID][3])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            self.etsLinked[etID][2].sendall(msg)
            
            data = self.recv_all_data(self.etsLinked[etID][2])
            signedData, data, _ = decrypt(data, self.privateKey)
            if check_sign(signedData, data, etPublicKey) == False:
                print("Verification error: Corrupted message")
                return
            
            try:
                msg = json.loads(data.decode("utf-8"), strict=False)
                print(msg)
                
                if(not os.path.exists(BO_STATUS_FOLDER)):
                    os.makedirs(BO_STATUS_FOLDER)
                with open(BO_STATUS_FOLDER + "status.log", "a+") as f:
                    f.write(datetime.now().strftime("%Y-%m-%d %H:%M:%S") + " " + data.decode("utf-8") + "\n")
                    
            except Exception as e:
                print("Exception on get_status "+ msg["destID"] + ": " + str(e))
                return

        
    def shutdown(self):
        data = ("{\"Instruction\": \"SHUTDOWN\", " + \
                 "\"baseID\": \"" + str(self.id) + "\"}").encode()
        
        #pregunto a cada una de las et por su estado
        for etID in self.etsLinked:
            etPublicKey = self.etsLinked[etID][1]
            data, _ = encsign(data, self.privateKey, etPublicKey, self.etsLinked[etID][3])
            
            msg = "{\"ciphered\": true, \"data\": \"".encode() + data + "\"}".encode()
            self.etsLinked[etID][2].sendall(msg)
            
            data = self.recv_all_data(self.etsLinked[etID][2])
                        
            self.etsLinked[etID][2].close()
        return
    

if __name__ == "__main__":
    
    if len(sys.argv) != 3:
        sys.exit("ERROR: faltan argumentos\n" +
            f"Sintaxis: python {sys.argv[0]} [id] [puerto]")

    ################################################
    #     Aqui va la restauracion del estado
    #
    #   Si existe estado anterior: Restaurarlo
    ################################################

    id, puerto = sys.argv[1], int(sys.argv[2])
    drone = baseOperaciones(id, puerto)

    ################################################
    #       Aqui va el guardado del estado
    #
    #   Si usuario quiere guardar estado: Guardar
    ################################################