import sys
import requests, json
from Crypto.PublicKey import RSA
from utils.utils import check
from utils import crypto

SIGN_LEN = 256      # Tamano de la firma

token = "6BDe8cF4b931EaCd"
headers = {"Authorization": "Bearer " + token,
            "Content-Type":"application/json"}

# Archivo para almacenar la clave asimetrica privada
privateKeyFile = "key.priv"

# Ruta base de la api
api_base_url = "http://vega.ii.uam.es:8080/api"

# Rutas relativas para la gestion de ficheros
upload_url = "/files/upload"        # Sube un fichero al sistema
download_url = "/files/download"    # Descarga un fichero
list_url = "/files/list"            # Lista todos los ficheros pertenecientes a un usuario
delete_f_url = "/files/delete"      # Borra un fichero

# Ruta relativa para obtener la clave publica de un usuario
public_key_url = "/users/getPublicKey"

def list_files():
    r = requests.post(api_base_url+list_url, headers=headers)
    check(r, 'list_files')
    print('Accediendo a la lista de archivos ... OK')

    if r.json()['num_files'] == 0:
        print('No hay archivos')
    else:
        print('Lista de archivos:')
    for i in range(r.json()['num_files']):
        print('[' + str(i) + '] FileID#' + r.json()['files_list'][i]['fileID'],
                ', FileName:', r.json()['files_list'][i]['fileName'])

def delete_file(id):
    data = {'file_id': id}

    r = requests.post(api_base_url+delete_f_url, data=json.dumps(data), headers=headers)
    check(r, 'delete_file')

    print('Archivo con ID#' + r.json()['file_id'] + ' borrado exitosamente')

def upload_file(fileName, dest_id):
    print('Solicitando envio de fichero a SecureBox')

    crypto.encsign(fileName, dest_id)
    file = {'ufile': open(fileName, "rb")}
    headers.pop('Content-Type')

    r = requests.post(api_base_url+upload_url, files=file, headers=headers)
    check(r, "upload_file")
    print('--> Subiendo fichero a servidor ... OK')

    print('Subida realizada correctamente, ID del fichero:', r.json()['file_id'])

def download_file(fileID, source_id):
    data = {'file_id': fileID}

    r = requests.post(api_base_url+download_url, data=json.dumps(data), headers=headers)
    check(r, "download_file")

    fileName = r.headers['Content-Disposition'].split("filename=", 1)[1][1:-1]

    print('Descargando fichero de SecureBox ... OK')
    fileContent = r.content
    print('-->', len(fileContent), 'bytes descargados correctamente')

    # Recuperamos nuestra clave privada
    with open(privateKeyFile, "r") as f:
        privateKey = RSA.importKey(f.read())

    # Desciframos
    signedText = crypto.decrypt(fileContent, privateKey)
    print('--> Descifrando fichero ... OK')

    # Conseguimos la clave publica del destinatario
    data = {'userID': source_id}
    
    r = requests.post(api_base_url+public_key_url, data=json.dumps(data), headers=headers)
    check(r, "download_file")

    print("--> Recuperando clave publica de ID#" + source_id + " ... OK")
    sourcePublicKey = RSA.importKey(r.json()['publicKey'])

    if crypto.check_sign(signedText, sourcePublicKey) == True:
        print('--> Verificando firma ... OK')
        with open(fileName, 'w') as f:
            f.write(signedText[SIGN_LEN:].decode())
        print("Fichero '" + fileName + "' descargado y verificado correctamente")
    else:
        print('Fichero corrupto, verficación fallida')