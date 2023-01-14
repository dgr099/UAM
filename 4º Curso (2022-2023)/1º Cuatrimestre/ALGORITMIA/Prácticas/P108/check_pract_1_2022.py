#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import argparse
import textwrap

import numpy as np

import p100 as p1
  
####################################### main
def main(t_size: int):
    """Comprobador de practica 1.
    
    Comprueba BB, min heap inserción t eliminación, PQ creación y extracción y
    heap based selection.
    BB, PQ y selection se prueban en tablas aleatorias; heaps sobre tablas fijas
    
    Args: 
        t_size: tamaño de tablas para bb y selección
        
    Returns:
        None
    """
    # check bb recursiva e iterativa
    print(30*'_' + "Checking recursive and iterative BB")
    
    # se genera un array ordenado aleatoria y se buscan sus sucesivos elemenetos
    # el bucle de busqueda se interrumpe en caso de error
    
    t = np.random.permutation(2 * t_size)[ : t_size]
    t = np.sort(t[ : t_size])
    
    # el bucle se interrumpe en caso de error
    for k in range(len(t)):
        idx_rec = p1.rec_bb(t, 0, len(t)-1, t[k])
        if idx_rec != k:
            print("error en bb recursiva")
            break
            
        idx_iter = p1.bb(t, 0, len(t)-1, t[k])
        if idx_rec != k:
            print("error en bb no recursiva")
            break 
            
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    # check min heap;
    print(30*'_' + "Checking min heap insertion")
    
    # se insertan sucesivamente en un min heap los elementos de una lista ordenada cuyo min heap 
    # correspondiente se conoce y se imprime el min heap final para comprobar si 
    # la creación ha sido correcta
    
    #cambiar por cualquier lista cuyo min heap se conoozca
    l = list(range(5))
    
    h = None 
    for i in range(len(l)):
        h = p1.insert_min_heap(h, l[i])
    print(h)
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    print(30*'_' + "Checking min heap creation")
    
    # mismo objetivo que la prueba anterior pero ahora el min heap se genera directamente sobre un array
    # el min heap final puede ser distinto del anterior
    t = np.array(l)
    p1.create_min_heap(t)
    print(t)
    
    # check pq
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    print(30*'_' + "Checking PQ insertion and removal")
    
    # se genera un array aleatorio, se insertan sus elementos en una pq y se extraen a continuación
    # lo que debe producir una ordenacion del array
    
    t = np.random.permutation(2 * t_size)[ : t_size]
        
    pq_ = p1.pq_ini()
    for i in range(len(t)):
        pq_ = p1.pq_insert(pq_, t[i])
        
        
    for _ in range(len(t)):
        e, pq_ = p1.pq_remove(pq_)
        print(e)
    
    # check problema de selección
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    print(30*'_' + "Checking heap based selection")
    
    # se genera un array aleatorio, se insertan sus elementos en una pq y se buscan los elementos
    # en las 4 primeras posiciones de su ordenación
    
    for _ in range(3):
        l = list(np.random.permutation(t_size))
        l = list(np.random.permutation(2 * t_size)[ : t_size])
    
        print(sorted(l))
        
        for k in range(1, min(t_size, 5)):
            val = p1.select_min_heap(l, k)
            print('pos', k, '\tval', val)
        
###############################################################################################
if __name__ == '__main__':
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter,
        description=textwrap.dedent(
        """
        Comprobador de la práctica 1. 
        
        Comprueba BB, min heap inserción t eliminación, PQ creación y extracción y 
        heap based selection. 
        
        BB, PQ y selection se prueban en tablas aleatorias; heaps sobre tablas fijas.
        
        Ejecutar por ejemplo en Linux como 
        
            ./check_pract_1_2022.py -s 10 
            
        y en Windows como 
        
            python check_pract_1_2022.py -s 10
        """))
    
    parser.add_argument("-p", "--pareja", type=str, default=None)
    parser.add_argument("-s", "--size", help="size of arrays", type=int, default=10)
    
    args = parser.parse_args()
    
    if len(sys.argv) > 1:
        if args.pareja is not None:
            f_path = "./p1" + args.pareja + "/graphs" + args.pareja + ".py"
            if os.path.isfile(f_path):
                str_comm = "cp ./p1" + args.pareja + "/graphs" + args.pareja + ".py  ./grafos.py"
                print(str_comm)
                os.system(str_comm)
                import grafos as gr
            else:
                sys.exit("file {0:s} not found".format(f_path))
        
        else:
            import p100 as p1 
            
        main(args.size)
    
    else:
        parser.print_help()
            
        