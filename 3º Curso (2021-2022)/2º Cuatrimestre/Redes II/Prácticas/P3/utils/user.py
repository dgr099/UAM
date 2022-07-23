from asyncio import protocols
from utils import util
import socket

LIST_OK_LEN = 13
REGISTER_OK_LEN = 10
def register(sock, dict):
    """if query(sock, dict['nick']) != None:
        return 'nick'"""
    if util.checker(dict['ip'], 'IP') == False:
        return 'ip'
    if util.checker(dict['port'], 'PORT') == False:
        return 'port'
    if util.checker(dict['protocol'], 'PROTOCOL') == False:
        return 'protocol'

    protocolos = ''
    for i in range(0, int(dict['protocol']) + 1):
        protocolos += 'V' + str(i)
        if i != int(dict['protocol']):
            protocolos += '#'

    cmd = f"REGISTER {dict['nick']} {dict['ip']} {dict['port']} {dict['password']} {protocolos}"
    print('c->s: ' + cmd)
    sock.send(cmd.encode())
    response = sock.recv(4096).decode('utf-8')

    print('s->c: ' + response)

    if response is None or response[:REGISTER_OK_LEN] != 'OK WELCOME':
        return 'password'
    
    return None

def query(sock, nick):
    cmd = "QUERY " + nick
    print('c->s: ' + cmd)
    
    sock.send(cmd.encode())
    response = sock.recv(4096).decode('utf-8')
    
    print('s->c: ' + response)

    if response is None or response == "NOK USER_UNKNOWN":
        return None

    data = response.split(' ')
    nick = data[2]
    ip = data[3]
    port = data[4]
    protocols = data[5]

    return nick, ip, port, protocols

def user_list(sock):
    cmd = "LIST_USERS"
    print('c->s: ' + cmd)
    list_users = []
    sock.send(cmd.encode())
    data = b''
    chunk = b''
    try:
        while True:
            chunk = sock.recv(4096)
            if chunk == b'':
                break
            data += chunk
    except Exception as e:
        pass

    response = data.decode('utf-8')

    cod = response[:LIST_OK_LEN]
    if response is None or cod != 'OK USERS_LIST':
        print('Error en call_users_list')
        return list_users
    
    response_data = response[LIST_OK_LEN + 1:]
    num_users_len = response_data.index(' ')
    
    num_users = response_data[:num_users_len] # Obtenemos el número de usuarios
    
    print(f's->c: Se han encontrado {num_users} usuarios')
    # Los usuarios se separan por '#'
    users = response_data[num_users_len + 1:].split('#')[:-1]
    i=1
    for user in users:
        try:
            user_fields = user.split(' ')
            list_users.append(f"{i}-> Nick: {user_fields[0]};   IP: {user_fields[1]};   Puerto: {user_fields[2]}")
            i=i+1
        except Exception as e:
            pass
    
    return list_users

def quit(sock):
    cmd = "QUIT"
    print('c->s: ' + cmd)
    
    sock.send(cmd.encode())
    response = sock.recv(4096).decode('utf-8')
    
    if response is None or response != "BYE":
        print("Error en el quit")

    print('s->c: ' + response)
    sock.close()

def call(local, user, sock):
    cmd = "CALLING " + local['nick'] + " " + local['UDPport']
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(5)
    try:
        #intentamos conectar con la persona a llamar
        sock.connect((user['ip'], int(user['port'])))
        sock.send(cmd.encode()) #le enviamos que le estamos llamando
        print("Se envio " + cmd)
    except Exception as e: 
            print("ERR en call" + str(e))
            sock.close()
            return False
    