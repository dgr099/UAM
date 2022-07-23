import requests, json, sys, os
from Crypto.Util.Padding import pad, unpad
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.Signature import PKCS1_v1_5
from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256
from Crypto import Random
from utils.utils import check

BS = AES.block_size # Tamano de bloque
SK_LEN = 32         # Tamano de la clave simetrica en bytes (256 bits)
CSK_LEN = 256       # Tamano de la clave simetrica cifrada en bytes
SIGN_LEN = 256      # Tamano de la firma

token = "6BDe8cF4b931EaCd"
headers = {"Authorization": "Bearer " + token,
            "Content-Type":"application/json"}

# Archivo para almacenar la clave asimetrica privada
privateKeyFile = "key.priv"

# Ruta base de la api
api_base_url = "http://vega.ii.uam.es:8080/api"

# Ruta relativa para obtener la clave publica de un usuario
public_key_url = "/users/getPublicKey"

def encrypt(fileName, dest_id, dataToEncrypt=None):
    if os.path.exists(fileName) == False:
        sys.exit("Error en encrypt\nFichero inexistente")
        
    # Conseguimos la clave publica del destinatario
    data = {'userID': dest_id}
    
    r = requests.post(api_base_url+public_key_url, data=json.dumps(data), headers=headers)
    check(r, "encrypt")

    print("--> Recuperando clave publica de ID#" + dest_id + " ... OK")
    destPublicKey = RSA.importKey(r.json()['publicKey'])

    if dataToEncrypt == None:
        # Leemos el fichero a encriptar
        with open(fileName, "rb") as f:
            dataToEncrypt = f.read()

    dataToEncrypt = pad(dataToEncrypt, BS)
    iv = Random.new().read(BS)

    # Conseguimos la clave simetrica con 32 bytes aleatorios
    simetricKey = Random.get_random_bytes(SK_LEN)

    # Generamos el cifrador simetrico con encadenamiento CBC
    cipher = AES.new(simetricKey, AES.MODE_CBC, iv)
    cipherData = cipher.encrypt(dataToEncrypt)

    # Ciframos con la clave publica del destinatario la clave asimetrica
    encryptor = PKCS1_OAEP.new(destPublicKey)
    simetricKeyEncrypted = encryptor.encrypt(simetricKey)
    
    cipheredText = iv + simetricKeyEncrypted + cipherData
    print("--> Cifrando fichero ... OK")

    with open(fileName, 'wb') as f:
        f.write(cipheredText)

    return cipheredText

def sign(fileName):
    if os.path.exists(fileName) == False:
        sys.exit("Error en sign\nFichero inexistente")
        
    # Recogemos el fichero que queremos firmar
    with open(fileName, "rb") as f:
        data = f.read()

    # Recuperamos nuestra clave privada
    with open(privateKeyFile, "r") as f:
        privateKey = RSA.importKey(f.read())

    # Realizamos el proceso de firma
    hasher = SHA256.new(data)

    # Generamos el encriptador y firmamos
    signer = PKCS1_v1_5.new(privateKey)
    signedData = signer.sign(hasher)
    
    # Juntamos firma y mensaje
    signedText = signedData + data
    print("--> Firmando fichero ... OK")

    with open(fileName, 'wb') as f:
        f.write(signedText) 

    return signedText
    
def encsign(fileName, dest_id):
    signedData = sign(fileName)
    encryptedData = encrypt(fileName, dest_id, dataToEncrypt=signedData)

    return encryptedData 

def decrypt(cipheredText, asimetricKey):
    iv = cipheredText[:BS]

    decryptor = PKCS1_OAEP.new(asimetricKey)
    simetricKeyEncripted = cipheredText[BS:BS+CSK_LEN]
    try:
        simetricKey = decryptor.decrypt(simetricKeyEncripted)
    except (ValueError):
        sys.exit('ERROR: El fichero esta enviado a otro usuario. No puedes desencriptarlo.')

    cipher = AES.new(simetricKey, AES.MODE_CBC, iv)
    text = unpad(cipher.decrypt(cipheredText[BS+CSK_LEN:]), BS)

    return text
    
def check_sign(signedText, asimetricKey):
    signedData = signedText[:SIGN_LEN]
    data = signedText[SIGN_LEN:]

    hasher = SHA256.new(data)
    verifier = PKCS1_v1_5.new(asimetricKey)
    return verifier.verify(hasher, signedData)