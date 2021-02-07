
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elements.h"
#include "file_utils.h"
#include "tree.h"
#include "types.h"

// for debugging
int tree_print(FILE *f, BSTree *pa);
void rama_copy(BTNode *tree, BSTree *copy);

void display_tree(FILE *fp, BSTree *tree) {
  tree_print(fp, tree);
  printf("\nEl árbol tiene %d nodos y profundidad %d\n", tree_numNodes(tree),
         tree_depth(tree));
  printf("\nPreorder: ");
  tree_preOrder(fp, tree);
  printf("\nPostorder: ");
  tree_postOrder(fp, tree);
  printf("\nInorder: ");
  tree_inOrder(fp, tree);
  printf("\n\n");
}

int basic_tests() {
  BSTree *tree = NULL;
  int i;
  char *str = malloc(25 * sizeof(char));
  char file_int[] = "num2.txt";
  char file_str[] = "str2.txt";
  /*test_file_conversion();*/

  printf("Creando árbol a partir de fichero de enteros \"%s\":\n", file_int);
  tree = tree_init(int_free, int_copy, int_print, int_cmp);
  read_tree_from_file(tree, "num2.txt", str2int); // or read_tree_from_file_alt
  display_tree(stdout, tree);

  // búsqueda
  i = 68;
  printf("El valor 68 está en el arbol: %s\n",
         tree_search(tree, &i) ? "sí" : "no");
  i = 5;
  printf("El valor 5 está en el arbol: %s\n\n",
         tree_search(tree, &i) ? "sí" : "no");

  // borrado
  i = 25;
  printf("Borrando el valor %d:\n", i);
  tree_delete(tree, &i);
  tree_inOrder(stdout, tree);
  printf("\nEl árbol tiene ahora %d nodos y profundidad %d\n",
         tree_numNodes(tree), tree_depth(tree));
  tree_print(stdout, tree);

  tree_destroy(tree);
  tree = NULL;

  printf("\nCreando árbol a partir de fichero de cadenas \"%s\":\n", file_str);
  tree = tree_init(string_free, string_copy, string_print, string_cmp);
  read_tree_from_file(tree, "str2.txt", str2str); // or read_tree_from_file_alt
  display_tree(stdout, tree);

  // búsqueda
  strcpy(str, "Alicia");
  printf("Alicia está en el arbol: %s\n", tree_search(tree, str) ? "sí" : "no");
  strcpy(str, "Roberto");
  printf("Roberto está en el arbol: %s\n\n",
         tree_search(tree, str) ? "sí" : "no");

  // borrado
  strcpy(str, "Juan");
  printf("Borrando el valor %s:\n", str);
  tree_delete(tree, str);
  tree_inOrder(stdout, tree);
  printf("\nEl árbol tiene ahora %d nodos y profundidad %d\n",
         tree_numNodes(tree), tree_depth(tree));
  tree_print(stdout, tree);

  free(str);
  tree_destroy(tree);
  tree = NULL;
  return 0;
}

void print_usage(char *program) {
  printf("Usage: %s [i|s|c] [file]\n", program);
  printf("       options: i: file of integers, s: file of strings, c: file of "
         "chars\n");
  printf("Without arguments, run some basic tests\n");
}

int check_args(int argc, char **argv) {
  // check arguments, for case argc != 0
  char option;
  if (argc == 2) {
    if (strcmp("-h", argv[1]) == 0)
      print_usage(argv[0]);
    else if (strcmp("-t", argv[1]) == 0)
      test_file_conversion();
    return 0;
  }

  if (argc != 3) {
    printf("Incorrect number of arguments\n");
    print_usage(argv[0]);
    return 0;
  }

  if (argc == 3) {
    option = argv[1][0];
    if ('i' != option && 's' != option && 'c' != option && 't' != option) {
      printf("Wrong option\n");
      print_usage(argv[0]);
      return 0;
    }
  }

  return 1;
}

/**** PSEUDOCÓDIGO tree_copy *****/
/*
BSTree *tree_copy(BSTree *tree)
  BSTree copy
  if(!tree):
    return  NULL
  if(!(copy=tree_init(tree->destroy_element, tree->copy_element, tree->print_element, tree->cmp_element))):
    return  NULL
  if(tree_isEmpty(tree)==TRUE):
    return  copy
  rama_copy(root(tree), copy)
  return copy
*/

/*********************************/

BSTree *tree_copy(BSTree *tree) {
  BSTree *copy;
  if(!tree){
    return NULL;
  }
  if(!(copy=tree_init(tree->destroy_element, tree->copy_element, tree->print_element, tree->cmp_element))){
    return NULL;
  }
  if(tree_isEmpty(tree)==TRUE){
    return copy;
  }
  rama_copy(tree->root, copy);
  return copy;
}
/**** PSEUDOCÓDIGO rama_copy *****/
/*
void rama_copy(BTNode tree, BSTree copy)
  if(!tree):
    return
  tree_insert(copy, info(tree));
  rama_copy(left(tree), copy);
  rama_copy(right(tree), copy);
*/

/*********************************/
void rama_copy(BTNode *tree, BSTree *copy){
  if(!tree){
    return;
  }
  tree_insert(copy, tree->info);
  rama_copy(tree->left, copy);
  rama_copy(tree->right, copy);
}

void rama_copy_mirror(BTNode **origin, BTNode *destination, BSTree *tree){
  if(!(destination)){
    return; 
  }
  if(*origin==NULL)
    (*origin)=calloc(1, sizeof(BTNode));
  (*origin)->info=tree->copy_element(destination->info);
  rama_copy_mirror(&((*origin)->left), (destination)->right, tree);
  rama_copy_mirror(&((*origin)->right), (destination)->left, tree);
} 
/*Este también es funcional pero usa doble punteros*/
void tree_mirror_double_p(BSTree **tree) {
  BSTree *aux;
  if(!tree){
    return;
  }
  aux=tree_copy(*tree);
  tree_destroy(*tree);
  *tree=tree_init(aux->destroy_element, aux->copy_element, aux->print_element, aux->cmp_element);
  rama_copy_mirror(&(*tree)->root, aux->root, *tree);
  tree_destroy(aux);
}
/**** PSEUDOCÓDIGO tree_n_mirror *****/
/*
void tree_n_mirror(BTNode **node)
  BTNode aux
  if(!(*node)):
    return
  aux=left(*node)
  left(*node)=right(*node)
  right(node)=aux
  tree_n_mirror(&(left(*node)));
  tree_n_mirror(&(right(*node)));
*/

/*********************************/
void tree_n_mirror(BTNode **node){
  BTNode *aux;
  if(!(*node)){
    return;
  }
  aux=(*node)->left;
  (*node)->left=(*node)->right;
  (*node)->right=aux;
  tree_n_mirror(&(*node)->left);
  tree_n_mirror(&(*node)->right);
}
/**** PSEUDOCÓDIGO tree_mirror *****/
/*
void tree_mirror(BSTree *tree)
  if(!tree):
    return
  tree_n_mirror(&(root(tree)))
  return
*/

/*********************************/
void tree_mirror(BSTree *tree){
  if(!tree){
    return;
  }
  tree_n_mirror(&tree->root);
  return;
}


int main(int argc, char **argv) {
  BSTree *tree = NULL;
  char option;

  if (argc == 1) { // no args
    basic_tests();
    printf("\nYou can also use this program with arguments:\n");
    print_usage(argv[0]);
    exit(EXIT_SUCCESS);
  }

  if (!check_args(argc, argv))
    exit(EXIT_FAILURE);

  // sample usage: create a tree from a file:
  option = argv[1][0];

  tree = create_tree_from_file(argv[2], option);
  if (!tree) {
    exit(EXIT_FAILURE);
  }

  // do something with the tree
  // your code here

  printf("Original tree\n");
  tree_print(stdout, tree);
  tree_inOrder(stdout, tree);
  printf("\n");

  // copy tree
  BSTree *tree2 = tree_copy(tree);
  printf("Tree copy\n");
  tree_print(stdout, tree2);

  tree_mirror(tree);
  printf("Mirror tree\n");
  tree_print(stdout, tree);

  // CLEAN UP
  tree_destroy(tree);
  tree_destroy(tree2);

  exit(EXIT_SUCCESS);
}
