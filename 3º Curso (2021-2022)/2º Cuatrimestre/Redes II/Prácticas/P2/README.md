# Redes2-Practica2
### Servicio de almacenamiento de ficheros siguiendo API Rest
#### Características:
- Gestionar la identidad (crear, exportar, buscar y borrar) de un usuario. Un usuario solo podrá disponer de una identidad en un momento dado.
- Cifrar y firmar archivos de forma local especificando la identidad de destinatario.
- Enviar un archivo al servicio previamente firmado y cifrado
- Recibir un fichero del servicio comprobando tras la descarga la firma digital.

#### Ayuda de uso
```sh
python3 securebox_client.py --help
```

