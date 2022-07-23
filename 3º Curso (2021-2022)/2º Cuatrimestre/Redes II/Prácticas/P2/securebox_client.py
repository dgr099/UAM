import sys, argparse, os
from argparse import RawTextHelpFormatter

from utils.utils import required_length
from utils import crypto, files, users

if __name__ == '__main__':

    if len(sys.argv) < 2:
        sys.exit("ERROR: faltan argumentos\n" +
            "Para ver la funcionalidad ejecute el siguiente comando:\n" +
            "python securebox_cliente.py --help")

    parser = argparse.ArgumentParser(formatter_class=RawTextHelpFormatter)

    parser.add_argument('--create_id', help='Crea nueva identidad: --create_id [nombre] [email] [alias:Opcional]', nargs='+', action=required_length(2,3))
    parser.add_argument('--search_id', help='Busca un usuario que contenga la cadena en el correo o en el nombre: --search_id [cadena]', type=str)
    parser.add_argument('--delete_id', help='Borra la identidad (creada por ti) con el id pasado: --delete_id [id]')
    parser.add_argument('--upload', help='Envia un fichero a otro usuario a traves de su id: --upload [fichero] --dest [id]')
    parser.add_argument('--source_id', help='Id del emisor del fichero: --source_id [id]')
    parser.add_argument('--dest_id', help='Id del receptor del fichero: --dest_id [id]')
    parser.add_argument('--list_files', help='Lista los ficheros pertenecientes al usuario', action='store_true')
    parser.add_argument('--download', help='Recupera un fichero con un id, verifica firma y descifra contenido: --download [id_fichero] --source_id [id]')
    parser.add_argument('--delete_file', help='Borra un fichero: --delete_file [id_fichero]')
    parser.add_argument('--encrypt', help='Cifra un fichero que puede descifrar otro usuario con el id pasado: --encrypt [fichero] --dest_id [id]')
    parser.add_argument('--sign', help='Firma un fichero --sign [fichero]')
    parser.add_argument('--enc_sign', help='Cifra y firma un fichero: --enc_sign [fichero] --dest_id [id]')

    args = parser.parse_args()
    
    if args.create_id:
        users.create_id(args.create_id)
    
    if args.search_id:
        users.search_id(args.search_id)

    if args.delete_id:
        users.delete_id(args.delete_id)

    if args.encrypt:
        if args.dest_id:
            crypto.encrypt(args.encrypt, args.dest_id)
        else:
            print('Error: Se necesita un destinatario')
            print('Sintaxis: python securebox_cliente.py --encrypt [filename] --dest_id [id]')

    if args.sign:
        crypto.sign(args.sign)

    if args.enc_sign:
        if args.dest_id:
            crypto.encsign(args.enc_sign, args.dest_id)
        else:
            print('Error: Se necesita un destinatario')
            print('Sintaxis: python securebox_cliente.py --enc_sign [filename] --dest_id [id]')

    if args.list_files == True:
        files.list_files()

    if args.delete_file:
        files.delete_file(args.delete_file)

    if args.upload:
        if args.dest_id:
            files.upload_file(args.upload, args.dest_id)
        else:
            print('Error: Se necesita un destinatario')
            print('Sintaxis: python securebox_cliente.py --upload_file [filename] --dest_id [id]')

    if args.download:
        if args.source_id:
            files.download_file(args.download, args.source_id)
        else:
            print('Error: Se necesita un emisor')
            print('Sintaxis: python securebox_cliente.py --download_file [filename] --source_id [id]')
