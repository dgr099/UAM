#!/usr/bin/python3 -tt
# Copyright 2010 Google Inc.
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0

# Google's Python Class
# http://code.google.com/edu/languages/google-python-class/

"""Wordcount exercise
Google's Python class

The main() below is already defined and complete. It calls print_words()
and print_top() functions which you write.

1. For the --count flag, implement a print_words(filename) function that counts
how often each word appears in the text and prints:
word1 count1
word2 count2
...

Print the above list in order sorted by word (python will sort punctuation to
come before letters -- that's fine). Store all the words as lowercase,
so 'The' and 'the' count as the same word.

2. For the --topcount flag, implement a print_top(filename) which is similar
to print_words() but which prints just the top 20 most common words sorted
so the most common word is first, then the next most common, and so on.

Use str.split() (no arguments) to split on all whitespace.

Workflow: don't build the whole program at once. Get it to an intermediate
milestone and print your data structure and sys.exit(0).
When that's working, try for the next milestone.

Optional: define a helper function to avoid code duplication inside
print_words() and print_top().

"""

import sys


# +++your code here+++
# Define print_words(filename) and print_top(filename) functions.
# You could write a helper utility function that reads a file
# and builds and returns a word/count dict for it.
# Then print_words() and print_top() can just call the utility function.

###

# This basic command line argument parsing code is provided and
# calls the print_words() and print_top() functions which you must define.

# función para obtener el diccionario
def get_dic(filename):
    diccionario = {}
    f = open(filename)  # abrimos el fichero de lectura
    for linea in f:
        palabras = linea.split()  # obtenemos las palabras de la linea
        for palabra in palabras:
            palabra = palabra.lower()  # las ponemos todas en minúsculas
            # si la palabra está en el diccionario,
            # aumentamos en 1 su valor anterior
            if palabra in diccionario:
                diccionario.update({palabra: diccionario[palabra] + 1})
            else:
                # en caso de no estar ponemos en 1 su valor
                diccionario[palabra] = 1
    return diccionario


def print_words(filename):
    # obtenemos el diccionario con las parejas de palabra y ocurrencia
    diccionario = get_dic(filename)
    # imprimimos los resultados con el formato especificado
    for element in diccionario:
        print(element, diccionario[str(element)])
    return


def print_top(filename):
    diccionario = get_dic(filename)  # obtenemos el diccionario
    # reverse activado porque quiero de mayor a menor
    diccionarioItems = sorted(
        diccionario.items(), key=lambda item: item[1], reverse=True)
    # los primeros 20 valores del diccionario
    for values in diccionarioItems[:20]:
        print(values[0], values[1])

    return


def main():
    if len(sys.argv) != 3:
        print('usage: ./wordcount.py {--count | --topcount} file')
        sys.exit(1)

    option = sys.argv[1]
    filename = sys.argv[2]
    if option == '--count':
        print_words(filename)
    elif option == '--topcount':
        print_top(filename)
    else:
        print('unknown option: ' + option)
        sys.exit(1)


if __name__ == '__main__':
    main()
