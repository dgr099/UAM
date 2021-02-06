
/**
 * @file  stack_types.h
 * @author Profesores Prog2
 * @date 10 Dec 2018
 * @version 1.0
 * @brief Stack elements
 *
 * @details Functions to manage the stack elements
 * 
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

#include <stdio.h>
#include <stdlib.h>

/********* INT  *********/


/**
 * @brief  This function copies the integer pointed by a.
 * This function allocates memory for the copy. 
 *
 * @param a Pointer to the integer
 * @return   This function returns a pointer to the new integer or null
 * if insufficient memory is available to create the element.
 *  */
void *int_copy (const void *a);

/**
 * @brief  This function compares two integers c1 and c2. 
 *
 * @param c1 Pointer to the first integer
 * @param c2 Pointer to the second integer 
 * @return  It returns an integer less than, equal to, or greater than zero 
 * if c1 is found, respectively, to be less than, to match, or be greater than c2.
**/
int int_cmp (const void *c1, const void *c2); 

/**
 * @brief  This function frees all the memory used by the integer.
 *
 * @param a A pointer to the integer 
 *  */
void int_free (void *a);

/**
 * @brief  This function writes the content of the pointer to integer to the stream. 
 *
 * @param pf A pointer to the stream
 * @param a A pointer to the element 
 * @return Upon successful return, these function return the number of characters.
 * If an output error is encountered, a negative value is returned.
 *  */
int int_print(FILE *pf, const void *a); 

/*******************CHAR **********/

/**
 * @brief  This function copies the char pointed by a.
 * This function allocates memory for the copy. 
 *
 * @param a Pointer to the char
 * @return   This function returns a pointer to the new char or null
 * if insufficient memory is available to create the element.
 *  */
void *char_copy (const void *a); 


/**
 * @brief  This function compares two chars c1 and c2. 
 *
 * @param c1 Pointer to the first char
 * @param c2 Pointer to the second char 
 * @return  It returns an integer less than, equal to, or greater than zero
 * if c1 is found, respectively, to be less than, to match, or be greater than c2.
**/
int char_cmp (const void *c1, const void *c2); 


/**
 * @brief  This function frees all the memory used by the char.
 *
 * @param a A pointer to the char 
 *  */
void char_free (void *a); 

/**
 * @brief  This function writes the content of the pointer to char to the stream. 
 *
 * @param pf A pointer to the stream
 * @param a A pointer to the element 
 * @return Upon successful return, these function return the number of characters.
 * If an output error is encountered, a negative value is returned.
 *  */
int char_print (FILE *pf, const void *a); 


/***************  Float **********/

/**
 * @brief  This function copies the float pointed by a.
 *
 * This function allocates memory for the copy. 
 * @param a Pointer to the float
 * @return   This function returns a pointer to the new float or null
 * if insufficient memory is available to create the element.
 *  */
void *float_copy (const void *a); 

/**
 * @brief  This function compares two floats c1 and c2. 
 *
 * @param c1 Pointer to the first float
 * @param c2 Pointer to the second float 
 * @return  It returns an integer less than, equal to, or greater than zero
 * if c1 is found, respectively, to be less than, to match, or be greater than c2.
**/
int float_cmp (const void *c1, const void *c2); 

/**
 * @brief  This function frees all the memory used by the float.
 *
 * @param a A pointer to the float 
 *  */
void float_free (void *a); 

/**
 * @brief  This function writes the content of the pointer to char to the stream. 
 *
 * @param pf A pointer to the stream
 * @param a A pointer to the element 
 * @return Upon successful return, these function return the number of characters.
 * If an output error is encountered, a negative value is returned.
 *  */
int float_print (FILE *pf, const void *a); 


/****************** String  **********************************/


/**
 * @brief  This function copies the string pointed by src.
 *
 * This function allocates memory for the copy. 
 * @param src Pointer to the source string
 * @return   This function returns a pointer to the new string or null
 * if insufficient memory is available to create the string.
 *  */
void *string_copy (const void *src); 

/**
 * @brief  This function compares two strings c1 and c2. 
 * This is a wrapper funtion of the function strcmp included in the library string.h
 *
 * @param c1 Pointer to the first string
 * @param c2 Pointer to the second string 
 * @return  It returns an integer less than, equal to, or greater than zero 
 * if c1 is found, respectively, to be less than, to match, or be greater than c2.
**/
int string_cmp (const void *c1, const void *c2); 


/**
 * @brief  This function frees all the memory used by the string.
 *
 * @param str A pointer to the string 
 *  */
void string_free (void *str); 

/**
 * @brief  This function writes a string to the stream. 
 *
 * @param pf A pointer to the stream
 * @param str A pointer to the string 
 * @return Upon successful return, these function return the number of characters.
 * If an output error is encountered, a negative value is returned.
 *  */
int string_print (FILE *pf, const void *str); 

