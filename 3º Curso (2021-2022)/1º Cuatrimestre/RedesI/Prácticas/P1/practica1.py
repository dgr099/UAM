'''
    practica1.py
    Muestra el tiempo de llegada de los primeros 50 paquetes a la interfaz especificada
    como argumento y los vuelca a traza nueva con tiempo actual

    Autor: Javier Ramos <javier.ramos@uam.es>
    2020 EPS-UAM
'''

from rc1_pcap import *
import sys
import binascii
import signal
import argparse
from argparse import RawTextHelpFormatter
import time
import logging

ETH_FRAME_MAX = 1514
PROMISC = 1
NO_PROMISC = 0
TO_MS = 10
num_paquete = 0
TIME_OFFSET = 30*60

def signal_handler(nsignal,frame):
	logging.info('Control C pulsado')
	if handle:
		pcap_breakloop(handle)
		
def convertToHex(number):
	number2 = number #para no actuar sobre la variable pasado por argumento
	result = "" #string con el valor en hexadecimal
	while(number2 != 0):
		aux = number2 % 16
		number2 = number2//16
		if aux >= 10:
			aux = ord('A') + (aux-10)
			result = chr(aux) + result
		else:
			result = str(aux) + result
	#concatenamos 0 hasta tener mínimo 2 nibbles
	while(len(result) < 2):
		result = "0" + result

	return result

def procesa_paquete(us,header,data):
	global num_paquete, pdumper
	logging.info('Nuevo paquete de {} bytes capturado en el timestamp UNIX {}.{}'.format(header.len,header.ts.tv_sec,header.ts.tv_usec))
	num_paquete += 1
	header.ts.tv_sec += TIME_OFFSET #le sumamos los 30 minutos como nos dice el enunciado
	#TODO imprimir los N primeros bytes
	print(data) #imprime la información
	#pkt_header.caplen: longitud capturada del paquete. Esto es, pkt_data solo contendrá pkt_header.caplen bytes.
	#si solicitamos más bytes del tamaño del paquete que solo imprima el tamaño del paquete sin pasarse
	size = min(args.nbytes, header.caplen)

	for i in range(0, size): #muestra la información con los bytes separados y en hexadecimal
		print("0x" + convertToHex(data[i]) + "h", end=" ")
		if (i+1) % 8 == 0: #pone una línea de separación cada 32 bytes
			print()
	print("\n") # Acabar con nueva linea + 1 linea de separacion entre paquetes.
	#Escribir el tráfico al fichero de captura con el offset temporal
	if pdumper is not None: #si se ha especificado interfaz y hemos abierto un dumper
		pcap_dump(pdumper,header,data)
	
if __name__ == "__main__":
	global pdumper,args,handle
	parser = argparse.ArgumentParser(description='Captura tráfico de una interfaz ( o lee de fichero) y muestra la longitud y timestamp de los 50 primeros paquetes',
	formatter_class=RawTextHelpFormatter)
	parser.add_argument('--file', dest='tracefile', default=False,help='Fichero pcap a abrir')
	parser.add_argument('--itf', dest='interface', default=False,help='Interfaz a abrir')
	parser.add_argument('--nbytes', dest='nbytes', type=int, default=14,help='Número de bytes a mostrar por paquete')
	parser.add_argument('--debug', dest='debug', default=False, action='store_true',help='Activar Debug messages')
	args = parser.parse_args()

	if args.debug:
		logging.basicConfig(level = logging.DEBUG, format = '[%(asctime)s %(levelname)s]\t%(message)s')
	else:
		logging.basicConfig(level = logging.INFO, format = '[%(asctime)s %(levelname)s]\t%(message)s')

	if args.tracefile is False and args.interface is False:
		logging.error('No se ha especificado interfaz ni fichero')
		parser.print_help()
		sys.exit(-1)

	signal.signal(signal.SIGINT, signal_handler) #si recibe la señal asociada al ctrl+c llama al signal_handler

	errbuf = bytearray()
	handle = None
	pdumper = None
	descr2 = None
	#TODO abrir la interfaz especificada para captura o la traza
	
	if args.interface is not False:
		handle = pcap_open_live(args.interface,args.nbytes,NO_PROMISC,TO_MS, errbuf) #abrimos una interfaz de 
		if handle is None:
			logging.error('Error en la apertura de la interfaz')
			print(errbuf)
			sys.exit(-1)
		#TODO abrir un dumper para volcar el tráfico (si se ha especificado interfaz) 
		#crear el archivo donde vamos a ir volcando los paquetes.
		descr2 = pcap_open_dead(DLT_EN10MB,ETH_FRAME_MAX) #devuelve un descriptor de archivo pcap
		if descr2 is None:
			logging.error('Error en el descriptor de archivo pcap')
			pcap_close(handle)
			print(errbuf)
			sys.exit(-1)
		pdumper = pcap_dump_open(descr2, "captura." + args.interface + time.asctime(time.gmtime()) + ".pcap") #creamos el dumper para guardar paquetes 
		if pdumper is None:
			logging.error('Error en la apertura del dumper')
			pcap_close(handle)
			pcap_close(descr2)
			print(errbuf)
			sys.exit(-1)

	else: #si no se ha especificado interfaz, abrimos traza
		handle = pcap_open_offline(args.tracefile, errbuf)
		if handle is None:
			logging.error('Error en la apertura de la traza')
			print(errbuf)
			sys.exit(-1)
	
	#procesamos los paquetes
	#descriptor del PCAP que queremos leer, 
	#número de paquetes a analizar, 
	#función de atención al paquete,
	#variable auxiliar que sirve para pasar datos a la función de atención.
	ret = pcap_loop(handle,-1,procesa_paquete,None)
	if ret == -1:
		logging.error('Error al capturar un paquete')
	elif ret == -2:
		logging.debug('pcap_breakloop() llamado')
	elif ret == 0:
		logging.debug('No mas paquetes o limite superado')
	logging.info('{} paquetes procesados'.format(num_paquete))
	if handle is not None: #si se pudo abrir la interfaz o traza cerramos
		pcap_close(handle)
	if pdumper is not None: #si se ha creado un dumper cerrarlo
		if descr2 is not None: #si se solicitó captura de interfaz y usamos descriptor de archivo pcap, lo cerramos
			pcap_close(descr2)
		pcap_dump_close(pdumper)
	sys.exit(0)



