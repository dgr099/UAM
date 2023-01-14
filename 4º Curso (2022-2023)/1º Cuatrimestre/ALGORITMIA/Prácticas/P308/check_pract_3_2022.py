#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import os
import argparse
import textwrap

import numpy as np

#import p100 as p1
  
####################################### main
def main(size, shift):
    """Comprobador de practica 3.
    
    Comprueba qselect, funciones auxiliares y variantes y funciones PD
    gestión de CDs, identificación de componentes conexas.
    
    Args: 
        None
    Returns:
        None
    """
    # check qselect
    print(30*'_' + "Checking QSel and QSel nr")
    #size = 13
    #shift = 4
    t = np.random.permutation(size).astype(int)
    for k in range(size + 2 * shift):
        print(" qsel {0:d}: {1:s}\t{2:s}".format(k-shift, str(p3.qsel(t, k-shift)), str(p3.qsel_nr(t, k-shift))))
        
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    print(30*'_' + "Checking QSel5")
    for k in range(size + 2 * shift):
        print("qsel5 {0:d}: {1:s}".format(k-shift, str(p3.qsel5_nr(t, k-shift))))
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    
    print(30*'_' + "Checking QSort5")
    print(p3.qsort_5(t).astype(int))
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    
    # check PD
    print(30*'_' + "Checking edit distance")
    #strng_1, strng_2 = 'bananas', 'bahamas'
    #strng_1, strng_2 = 'algoritmos', 'logaritmos'
    strng_1, strng_2 = 5*'a', 'b' + 4*'a'
    print("edit_distance:\t", p3.edit_distance(strng_1, strng_2))
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    print(30*'_' + "Checking max common subsequence")
    print("max_length:\t", p3.max_subsequence_length(strng_1, strng_2))
    print("max_commmon_subsequence:\n", p3.max_common_subsequence(strng_1, strng_2))
    
    _ = input("\npulsar Intro para continuar " + 20*'.' + "\n")
    
    print(30*'_' + "Checking matrix mult")
    l_dims = [50, 10, 40, 30, 5]
    print(p3.min_mult_matrix(l_dims))

    
    
###############################################################################################
if __name__ == '__main__':
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter,
        description=textwrap.dedent(
        """
        Comprobador de la práctica 3. 
        
        Comprueba qselect, funciones auxiliares y variantes y funciones PD
        gestión de CDs, identificación de componentes conexas.
    
        
        Ejecutar por ejemplo en Linux como 
        
            ./check_pract_3_2022.py  
            
        y en Windows como 
        
            python check_pract_3_2022.py
        """))
    
    parser.add_argument("-p", "--pareja", type=str, default=None)
    parser.add_argument("-sz", "--size", help="size of perms for qsel", type=int, default=10)
    parser.add_argument("-sh", "--shift", help="size of shift for qsel", type=int, default=3)
    
    args = parser.parse_args()
    
    if len(sys.argv) > 0:
        if args.pareja is not None:
            f_path = "./p3" + args.pareja + "/p3" + args.pareja + ".py"
            if os.path.isfile(f_path):
                #str_comm = "cp ./p3" + args.pareja + "/p3" + args.pareja + ".py  ./pract1.py"
                str_comm = "cp ./p3" + args.pareja + "/p3" + args.pareja + ".py  ./pract3.py"
                print(str_comm)
                os.system(str_comm)
                str_comm = "mv p3" + args.pareja + ".py  ./pract3.py"
                print(str_comm)
                os.system(str_comm)
                #import pract3 as p3
            else:
                sys.exit("file {0:s} not found".format(f_path))
        
        else:
            import p308 as p3
            
        main(args.size, args.shift)
    
    else:
        parser.print_help()
            
        