# Práctica 1 Redes
## Servidor web
###### David Teófilo Garitagoitia Romero & Daniel Cerrato Sánchez

Servidor web simple con soporte para verbos GET, POST y OPTIONS con fines educativos para profundizar y conocer conceptos básicos del manejo de HTTP
## Contenido

- Configurar el servidor mediante el fichero .conf
- Makefile para compilación de servidor y librerias
- Script para probar resistencia del server
- Codigo del servidor y librerías de utilidad

## Método de uso
Lo primero que deberemos hacer será limpiar los objetos de una compilación anterior, tras ello compilaremos el programa y ejecutaremos el servidor
```sh
make clean
make
./server
```
Tras la ejecución del servidor podemos acceder a localhost:puerto/index,html para acceder a la página de pruebas del servidor dentro de la cual podremos comprobar como se cargan las imágenes, navegamos entre recursos con los links, se muestran satisfactoriamente los errores etc.
Para comprobar el comando options, lo podemos realizar desde la cmd
```sh
curl -i --request-target "*" -X OPTIONS localhost:8081
```
Se nos mostrará como es de esperar la siguiente información:
```sh
HTTP/1.0 200 OK
Date: Sat, 19 Mar 2022 19:45:42 GMT
Server: MyCoolServer 1.1
Last-Modified: Thu, 01 Jan 1970 00:00:00 GMT
Content-Length: 0
Content-Type: No file requested
Allow: GET POST OPTIONS
```
Si queremos centrarnos en un recurso en concreto también podemos como se ve en el siguiente ejemplo:
```sh
curl -i --request-target "/media/img1.jpg" -X OPTIONS localhost:8081
HTTP/1.0 200 OK
Date: Sat, 19 Mar 2022 22:23:44 GMT
Server: MyCoolServer 1.1
Last-Modified: Thu, 17 Mar 2022 13:24:42 GMT
Content-Length: 0
Content-Type: image/jpeg
Allow: GET OPTIONS
```
Y en cn caso de no encontrarlo nos mostrará la siguiente información con su correspondiente error 404
```sh
curl -i --request-target "/media/noexiste.jpg" -X OPTIONS localhost:8081
HTTP/1.0 404 Not Found
Date: Sat, 19 Mar 2022 22:24:50 GMT
Server: MyCoolServer 1.1
Last-Modified: Wed, 22 Feb 4461375 04:18:40 GMT
Content-Length: 0
Content-Type: image/jpeg
Allow: GET OPTIONS
```

## Conclusiones
Hacer un pequeño servidor en esta práctica nos ha acercado
aún más a conocer los entresijos que tiene la web por
debajo, el tratamiento de las diferentes funcionalidades
de HTTP y la conexión mediante sockets entre los diversos
clientes y el servidor.

No todo es tan sencillo como lo creemos inicialmente y,
a decir verdad, esta práctica no es compleja como tal.
La dificultad reside en la cantidad de cosas que hay que
hacer y, sobre todo, manejarlas bien para conseguir un resultado satisfactorio.

En general, la práctica nos ha encantado a ambos y creemos
que es una práctica que desarrollaremos más en el futuro.
