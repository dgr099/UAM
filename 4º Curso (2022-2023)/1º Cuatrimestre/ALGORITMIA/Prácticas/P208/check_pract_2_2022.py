#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import os
import argparse
import textwrap

import numpy as np

import p208 as p2
  
####################################### main
def main():
    """Comprobador de practica 2.
    
    Comprueba gestión de CDs, identificación de componentes conexas.
    
    Args: 
        t_size: tamaño de tablas para bb y selección
        
    Returns:
        None
    """
    # check cd
    print(30*'_' + "Checking CD")
    
    #ejemplo del problema 2.15; usar cualquier otro
    p =np.array([-2, 0, 1, -2, 3, 4, -1, -2, 7, 8])
    d = p2.cd_2_dict(p)
    print("antes  \t", d)
    
    p2.union(p2.find(1, p), p2.find(5, p), p)
    p2.union(p2.find(2, p), p2.find(6, p), p)
    p2.union(p2.find(5, p), p2.find(9, p), p)
    d = p2.cd_2_dict(p)
    print("después\t", d)
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    # check cc
    print(30*'_' + "Checking CCs")
    # lo que siguen son distintos grafos; usar cualquiera
    g = [(1, 2), (1, 3), (0, 4), (4, 5)]
    g = [(1, 2), (1, 3), (2, 1), (3, 1), (4, 5), (5, 4)]
    g = [(0, 1), (0, 3), (1, 2), (1, 4), (3, 4), (4, 5), (4, 6), (5, 6)]
    g = []
    g = [(0, 2), (1, 3), (2, 3), (2, 4), (3, 4), (5, 6), (5, 7), (6, 8)]
    g = [(0, 12), (10, 0), (7, 12), (1, 9), (3, 8), (3, 9), (11, 6), (2, 5), (4, 5), (0, 2)]
    d_cc = p2.ccs(13, g)
    print(d_cc)
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    # check tsp
    print(30*'_' + "Checking greedy TSP")
    # distances for ["barcelona", "madrid", "sevilla", "valencia"]
    dist_bmsv = np.array([
    [0, 624, 995, 350], 
    [624, 0, 506, 357],
    [995, 506, 0, 653],
    [350, 357, 653, 0]])
    
    #simple graph
    dist_simple = np.array([
    [0, 1, 2, 1],
    [1, 0, 1, 2],
    [2, 1, 0, 1],
    [1, 2, 1, 0]])
    
    #coger uno
    dist_m = dist_simple
    print("graph_matrix\n", dist_m)
    
    circuit = p2.greedy_tsp(dist_m)
    print(circuit)
    
    circuit_length = p2.len_circuit(circuit, dist_m)
    print("\ngreedy length: %d" % circuit_length)
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    # check repeated greedy tsp
    print(30*'_' + "Checking iterated greedy TSP")
    
    circuit = p2.repeated_greedy_tsp(dist_m)
    print(circuit)
    
    circuit_length = p2.len_circuit(circuit, dist_m)
    print("\nrepeated greedy length: %d" % circuit_length)
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    # check exhaustive tsp
    print(30*'_' + "Checking exhaustive TSP")
    
    circuit = p2.exhaustive_tsp(dist_m)
    print(circuit)
    
    circuit_length = p2.len_circuit(circuit, dist_m)
    print("\nexhaustive length: %d" % circuit_length)
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    # check exhaustive tsp
    print(30*'_' + "Checking on random graphs")
    
    dm = p2.dist_matrix(4, w_max=50)
    print("graph_matrix\n", dm)
    
    c_g = p2.greedy_tsp(dm)
    print("\ngreedy circuit\n", c_g)
    l_g = p2.len_circuit(c_g, dm)
    print("\ngreedy length: %d" % l_g)
    
    c_e = p2.exhaustive_tsp(dm)
    print("\nexhaustive circuit\n", c_e)
    l_e = p2.len_circuit(c_e, dm)
    print("\nexhaustive length: %d" % l_e)
    
    
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
    #parser.add_argument("-s", "--size", help="size of arrays", type=int, default=10)
    
    args = parser.parse_args()
    
    if len(sys.argv) > 0:
        if args.pareja is not None:
            f_path = "./p2" + args.pareja + "/p2" + args.pareja + ".py"
            if os.path.isfile(f_path):
                #str_comm = "cp ./p2" + args.pareja + "/p2" + args.pareja + ".py  ./pract1.py"
                str_comm = "cp ./p2" + args.pareja + "/p2" + args.pareja + ".py  ."
                print(str_comm)
                os.system(str_comm)
                str_comm = "mv p2" + args.pareja + ".py  ./pract2.py"
                print(str_comm)
                os.system(str_comm)
                import pract1 as p1
            else:
                sys.exit("file {0:s} not found".format(f_path))
        
        else:
            import p208 as p2
            print('here')
            
        main()
    
    else:
        parser.print_help()
            
        