from Crypto.Util.Padding import pad, unpad
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.Signature import PKCS1_v1_5
from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256
from Crypto import Random

import base64

BLOCK_SIZE = AES.block_size         # Tamano de bloque
SIMETRIC_KEY_LEN = 32               # Tamano de la clave simetrica en bytes (256 bits)
CIPHERED_SIMETRIC_KEY_LEN = 256     # Tamano de la clave simetrica cifrada en bytes
SIGN_LEN = 256                      # Tamano de la firma

def encrypt(data:bytes, destPublicKey:bytes, simetricKey:bytes=None):    
    
    publicKey = RSA.importKey(destPublicKey)    
    data = pad(data, BLOCK_SIZE)
    iv = Random.new().read(BLOCK_SIZE)

    # Conseguimos la clave simetrica con 32 bytes aleatorios
    if simetricKey == None:
        simetricKey = Random.get_random_bytes(SIMETRIC_KEY_LEN)

    # Generamos el cifrador simetrico con encadenamiento CBC
    cipher = AES.new(simetricKey, AES.MODE_CBC, iv)
    cipherData = cipher.encrypt(data)

    # Ciframos con la clave publica del destinatario la clave asimetrica
    encryptor = PKCS1_OAEP.new(publicKey)
    simetricKeyEncrypted = encryptor.encrypt(simetricKey)

    cipherText = iv + simetricKeyEncrypted + cipherData

    return base64.b64encode(cipherText), simetricKey

def sign(data:bytes, sourcePrivateKey:bytes):
    # Realizamos el proceso de firma
    hasher = SHA256.new(data)
    privateKey = RSA.importKey(sourcePrivateKey)

    # Generamos el encriptador y firmamos
    signer = PKCS1_v1_5.new(privateKey)
    signedData = signer.sign(hasher)
    
    # Juntamos firma y mensaje
    signedText = signedData + data

    return signedText
    
    
def encsign(data:bytes, sourcePrivateKey:bytes, destPublicKey:bytes, simetricKey:bytes=None):
    signedData = sign(data, sourcePrivateKey)
    encryptedData, simetricKey = encrypt(signedData, destPublicKey, simetricKey)
    return encryptedData, simetricKey


def decrypt(cipheredText:bytes, destPrivateKey:bytes):
    cipheredText = base64.b64decode(cipheredText)
    iv = cipheredText[:BLOCK_SIZE]
    privateKey = RSA.importKey(destPrivateKey)

    decryptor = PKCS1_OAEP.new(privateKey)
    simetricKeyEncripted = cipheredText[BLOCK_SIZE:BLOCK_SIZE+CIPHERED_SIMETRIC_KEY_LEN]
    try:
        simetricKey = decryptor.decrypt(simetricKeyEncripted)
    except ValueError:
        raise Exception("Deciphering error: Message for other destination")

    cipher = AES.new(simetricKey, AES.MODE_CBC, iv)
    text = unpad(cipher.decrypt(cipheredText[BLOCK_SIZE+CIPHERED_SIMETRIC_KEY_LEN:]), BLOCK_SIZE)

    return text[:SIGN_LEN], text[SIGN_LEN:], simetricKey
    
def check_sign(signedData:bytes, data:bytes, sourcePublicKey:bytes):
    publicKey = RSA.importKey(sourcePublicKey)
    hasher = SHA256.new(data)
    verifier = PKCS1_v1_5.new(publicKey)
    return verifier.verify(hasher, signedData)
