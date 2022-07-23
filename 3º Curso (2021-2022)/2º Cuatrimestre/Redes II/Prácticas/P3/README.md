# practica3
## Cliente llamada
###### David Teófilo Garitagoitia Romero & Daniel Cerrato Sánchez

Aplicación con conexión a servidor de descubrimiento para establecer videoconferencias
## Contenido

- Utils folder, dentro de este tenemos los módulo de comunicación con el servidor de descubirmiento y el control de las llamadas
- cliente de llamadas dentro del cual está implementada la interfaz visual en conjunto con el main

## Método de uso
Al iniciar la aplicación esta procurará conectarse con el servidor de descubrimiento para poder registrar al usuario, una vez nos registremos, encontraremos una pantalla principal desde la cual podremos conectarnos con otro usuario buscando a este por su nick para posteriormente llamarlo, podremos salir de la aplicación, o, desplazarnos a una segunda pantalla donde encontraremos una lista de todos los usuarios de la aplicación, lista que podremos recargar o seleccionar para comunicarnos con el usuario seleccionado.
Lo único que debemos hacer es installar los requisitos
```sh
pip3 --upgrade
pip3 install appjar
pip3 install opencv-python
python3 practica3_client.py 
```

Tras la ejecución del servidor podemos realizar todas las acciones previamente indicadas
Al establecer una conexión de llamada, nuestra ventana cambiará mostrando una nueva ventana donde se muestra nuestra imagen y la de nuestro par, podremos:
- Colgar/aceptar la llamada
- Pausar (dejar de enviar video a nuestro par en llamada)
- Reanudar (reanudar envio de video a nuestro par en llamada)
- Cambiar la calidad de retrasmisión
- Cambiar la fuente de video a trasmitir



## Conclusiones
Hemos logrado realizar un pequeño cliente de telefonía ip el cual requiere una conexión con un servidor de descubrimiento donde registrar nuestros valores de usuario.
Una vez hecho esto se sigue un procedimiento similar al protocolo RTSP empleando dos puertos y enviando la información de control fuera de banda.
De esta forma los comandos se enviaran mediante TCP para tener cuidado con las pérdidas, mientras que el video será UDP aumentando la velocidad de envio y priorizando retrasmisión en tiempo real siendo tolerantes con las pérdidas en pos de reducir el tamaño del retraso

No todo es tan sencillo como lo creemos inicialmente y,
a decir verdad, esta práctica no es compleja como tal.
La dificultad reside en la cantidad de cosas que hay que
hacer y, sobre todo, manejarlas bien para conseguir un resultado satisfactorio.

En general, la práctica nos ha encantado a ambos y creemos
que es una práctica que desarrollaremos más en el futuro.

