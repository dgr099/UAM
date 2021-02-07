#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elements.h" /*for testing only*/
#include "file_utils.h"
#include "tree.h"
#include "types.h"

#define BUFFER_SIZE 256

/* convert string to integer pointer */
void *str2int(const char *str) {
  // no error handling, to fix it use strtol as in:
  // https://wiki.sei.cmu.edu/confluence/display/c/ERR34-C.+Detect+errors+when+converting+a+string+to+a+number

  int *i = malloc(sizeof(int));
  if (!i)
    return NULL;
  *i = atoi(str);
  return i;
}

/* convert string to string, i.e duplicate string*/
void *str2str(const char *str) { return strdup(str); }

/* convert string to char pointer */
void *str2chr(const char *str) {
  char *c = malloc(sizeof(char));
  if (!c)
    return NULL;
  *c = str[0];
  return c;
}

void *str2float(const char *str) {
  float *f = malloc(sizeof(float));
  if (!f)
    return NULL;
  *f = strtof(str, NULL);
  return f;
}

/* read line from file and strip newline */
/* note it doesn't strip any additional whitespace */

int read_line(FILE *fp, char *buffer) {
  int len;
  if (fgets(buffer, BUFFER_SIZE, fp)) {
    len = strlen(buffer);
    if (buffer[len - 1] == '\n')
      buffer[--len] = '\0'; // remove '\n' from end of buffer
    if (buffer[len - 1] == '\r')
      buffer[--len] =
          '\0'; // hopefully this handles '\r\n' for files created in Windows.
    // printf("Buffer %d: --%s--\n", len - 1, buffer);
    return len; // will return 0 for empty line
  }
  return 0;
}

/* convenience function to test read_elements_from_file */
void noop(void *elem) {}

/* reads a file line by line, converting each line to an element
 of the appropriate type and processing (e.g. printing) that element */
Status read_elements_from_file(char *filename, elem_from_string convert,
                               process_element process) {
  FILE *fp;
  char buffer[BUFFER_SIZE];
  void *elem;

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Error opening %s\n", filename);
    return ERROR;
  }

  while (read_line(fp, buffer)) {
    elem = convert(buffer);
    process(elem);
    free(elem);
  }
  fclose(fp);
  return OK;
}

/* wrappers for print functions, for debugging */
void std_int_print(const void *i) {
  int_print(stdout, i);
  printf(", ");
}

void std_str_print(const void *i) {
  string_print(stdout, i);
  printf(", ");
}

void std_chr_print(const void *i) {
  char_print(stdout, i);
  printf(", ");
}

void std_flt_print(const void *i) {
  float_print(stdout, i);
  printf(", ");
}

void test_file_conversion() {
  char *files[] = {"ej15_3_ints.txt", /*"num.txt",*/ "str.txt", "chars.txt",
                   "floats.txt"};
  // int num_files = sizeof(files) / sizeof(files[0]);

  printf("Reading %s: ", files[0]);
  read_elements_from_file(files[0], str2int, std_int_print);
  printf("\nReading %s: ", files[1]);
  read_elements_from_file(files[1], str2str, std_str_print);
  printf("\nReading %s: ", files[2]);
  read_elements_from_file(files[2], str2chr, std_chr_print);
  printf("\nReading %s: ", files[3]);
  read_elements_from_file(files[3], str2float, std_flt_print);
  printf("\n");
}

/* MAIN FUNCTIONS */

/* builds a tree from a previously allocated empty tree and a file containing
one element per line, using the convert function to create the elements*/
Status read_tree_from_file(BSTree *tree, char *filename, elem_from_string convert) {

  FILE *fp;
  char buffer[BUFFER_SIZE];
  void *elem = NULL;
  Status ret = OK;

  if (!tree || !tree_isEmpty(tree)) {
    printf("Something's wrong with the tree\n");
    return ERROR;
  }

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Error opening %s\n", filename);
    return ERROR;
  }

  while (read_line(fp, buffer) && ret == OK) {
    elem = convert(buffer);
    ret = tree_insert(tree, elem); // change to tree_insert_alt to test the
                                   // alternative insert function
    free(elem);
  }

  // if (ret == ERROR) {
  //   printf("Something went wrong\n");
  //   tree_destroy(tree);
  // }
  // better let the creator of tree handle its destruction

  fclose(fp);
  return ret;
}

/* creates and returns a newly allocated tree from a file containing one element
 * per line, using the convert function to create the elements */
BSTree *create_tree_from_file(char *filename, char type) {
  BSTree *tree = NULL;
  elem_from_string convert;
  Status st = OK;

  switch (type) {
  case 'i':
    tree = tree_init(int_free, int_copy, int_print, int_cmp);
    convert = str2int;
    break;
  case 's':
    tree = tree_init(string_free, string_copy, string_print, string_cmp);
    convert = str2str;
    break;
  case 'c':
    tree = tree_init(char_free, char_copy, char_print, char_cmp);
    convert = str2chr;
    break;
  default:
    printf("Unrecognized type when creating a tree\n");
    return NULL;
  }

  if (!tree) {
    printf("Error creating tree from %s\n", filename);
    return NULL;
  }

  st = read_tree_from_file(tree, filename, convert);

  if (st == ERROR) {
    tree_destroy(tree);
    tree = NULL;
  }

  return tree;
}