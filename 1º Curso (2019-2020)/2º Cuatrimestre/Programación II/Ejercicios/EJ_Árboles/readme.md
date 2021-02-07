# Tree library

Contents:

```
Makefile: creates the test_tree program and the libtree.a library

trees.c: source of the tree library

file.utils.c: utilities to read a tree from a file

elements. c: functions for different types of elements: int, string, char, float, add your own

test_tree.c: a sample program to test the library

Header files: types.h, elements.h, file_utils.h.
```

The functions available for use with the tree library are in `tree.h`. This file also contains the function types necessary to handle arbitrary tree elements, specifically to create, destroy, print, copy, and compare elements. In order to use a tree with some element type, you need to provide functions of this type for the element type. See `elements.c` and `elements.h` for examples.

You can also use the functions in file_utils.h to create a binary search tree from a file containing (a string representation of) one element per line. In order to do this, you need an additional function to convert a string to an element.

To use the tree library, use `-L. -ltree` as compilation flags, with the file libtree.a in your current directory.

The test_tree program exemplifies various uses of the tree library. Use `test_tree -h` for usage; in particular you can create a tree from a file containing elements of some particular type one per line.

```
$ ./test_tree -h
Usage: ./test_tree [i|s|c][file]
options: i: file of integers, s: file of strings, c: file of chars
Without arguments, run some basic tests

```

So for example `test_tree i nums.txt` will create a tree of integers read from the file _nums.txt_

## Visualización de árboles
La función `tree_print` permite visualizar un árbol. Esta función imprime un nodo en cada línea, con una sangría proporcional a su profundidad, con '--' para representar un nodo nulo. Dado un nodo N, su subárbol izquierdo se empieza a imprimir en la siguiente línea, y tras terminar este, se imprime su subárbol derecho. Nótese que los hijos izquierdo y derecho de N tendrán la misma sangría, algo superior a la del propio N. 

Ejemplo: el árbol
```      
        A
      /   \
      B    C
    /  \    \   
    D  E    F
  /
 G
```
se imprime así:
```
A
  B
    D
      G
        --
        --
      --
    E
      --
      --
  C
      --
      F
        --
        --
```

## File utils

The file_utils.c and file_utils.h files provide functionality to easily create trees for any kind of element. What you need:

- a file where your elements are stored one by line
- a funcion to convert from a string representation of your elements to the appropiate data structure.

This is illustrated in file_utils.h:

```c
/**_ conversion functions _**/
/* function types to convert strings to elements of the appropriate type */
/* the functions should allocate memory for the element */
typedef void *(*elem_from_string)(const char _str);
/* convert string to integer pointer */
void *str2int(const char _str);
/* convert string to string, i.e duplicate string */
void *str2str(const char _str);
/* convert string to char pointer */
void *str2chr(const char *str);

```

If you define a new type of element, you can test that you can read your new elements from a file by using `read_elements_from_file` in `file_utils.c`

