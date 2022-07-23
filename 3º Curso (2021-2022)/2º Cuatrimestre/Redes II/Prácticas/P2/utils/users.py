import requests, json
from Crypto.PublicKey import RSA
from utils.utils import check, none_string_check

TAM_CLAVE = 2048    # Tamano de las claves asimetricas

token = "6BDe8cF4b931EaCd"
headers = {"Authorization": "Bearer " + token,
            "Content-Type":"application/json"}

# Archivos para almacenar las claves asimetricas
privateKeyFile = "key.priv"
publicKeyFile = "key.pub"

# Ruta base de la api
api_base_url = "http://vega.ii.uam.es:8080/api"

# Rutas relativas para la gestion de usuarios
register_url = "/users/register"    # Registra un usuario en el sistema
search_url = "/users/search"        # Obtiene datos de un usuario por nombre o correo electronico
delete_usr_url = "/users/delete"    # Borrar un usuario


def create_id(args):
    privateKey = RSA.generate(TAM_CLAVE)
    publicKey = privateKey.publickey()
    print("Generando par de claves RSA de " + str(TAM_CLAVE) + " bits ... OK")

    data = {'nombre': args[0], 
            'email': args[1],
            'publicKey': publicKey.exportKey('PEM').decode("utf-8")
            }
    
    r = requests.post(api_base_url+register_url, data=json.dumps(data), headers=headers)
    check(r, 'create_id')

    with open(privateKeyFile, "wb") as f:
        f.write(privateKey.exportKey('PEM'))

    with open(publicKeyFile, "wb") as f:
        f.write(publicKey.exportKey('PEM'))

    print("Identidad con ID#" + r.json()['userID'] + " creada correctamente")

def search_id(string):
    print("Buscando usuario '" + string + "' en el servidor ... OK")
    
    data = {'data_search': string}
    
    r = requests.post(api_base_url+search_url, data=json.dumps(data), headers=headers)
    check(r, 'search_id')
    
    n_users = len(r.json())
    print(str(n_users) + " usuarios encontrados:")
    for i in range(n_users):
        print("[" + str(i) +  "] " + none_string_check(r.json()[i]['nombre']) + ", "
                + none_string_check(r.json()[i]['email']) + ", ID: " + none_string_check(r.json()[i]['userID']))
        
def delete_id(id):
    print("Solicitando borrado de la identidad #" + id + "...OK")
    
    data = {'userID': id}
    
    r = requests.post(api_base_url+delete_usr_url, data=json.dumps(data), headers=headers)
    check(r, 'delete_id')

    print("Identidad con ID#" + id + " borrada correctamente")