/** 
 * @brief It declares the tests for the set module
 * 
 * @file set_test.h
 * @author Daniel Cerrato Sánchez
 * @version 1.0 
 * @date 08-06-2020
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test the set creation function
 * @pre No arguments needed
 * @post A non-null pointer to the created set
 */
void test1_set_create ();


/**
 * @test Test the set creation function
 * @pre The set is a non-NULL pointer
 * @post The value of the field that stores the id number of the set without having inserted any
 */
void test2_set_create ();


/**
 * @test Test the function of adding an id to the set
 * @pre The set is a non-NULL pointer passing a correct id
 * @post The output must be OK
 */
void test1_set_add ();

/**
 * @test Test the function of adding an id to the set
 * @pre The set is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_set_add ();

/**
 * @test Test the function of deleting an id to the set
 * @pre The set is a non-NULL pointer with a correct id, a correct id is searched
 * @post The output must be OK
 */
void test1_set_dell ();

/**
 * @test Test the function of deleting an id to the set
 * @pre The set is a non-NULL pointer with a correct id, but an incorrect id is searched
 * @post The output must be ERROR
 */
void test2_set_dell ();

/**
 * @test Test the function of deleting an id to the set
 * @pre The set is a pointer to NULL
 * @post The output must be ERROR
 */
void test3_set_dell ();

/**
 * @test Test the function to get the number of ids of the set
 * @pre The set is a non-NULL pointer with at least one id
 * @post The output must be the number of ids in the set
 */
void test1_set_get_num ();

/**
 * @test Test the function to get the number of ids of the set
 * @pre The set is a pointer to NULL
 * @post The output must be -1
 */
void test2_set_get_num ();

/**
 * @test Test the function to get the position of an id in the set
 * @pre The set is a non-NULL pointer with at least one id, a correct id is searched
 * @post The output must be the position of that id in the set
 */
void test1_set_find_index ();

/**
 * @test Test the function to get the position of an id in the set
 * @pre The set is a non-NULL pointer with at least one id, an incorrect id is searched
 * @post The output must be -1
 */
void test2_set_find_index ();

/**
 * @test Test the function to get a set id through its position
 * @pre The set is a non-NULL pointer with at least one id, a correct position is searched
 * @post The output must be a set id
 */
void test1_set_get_id_at_position ();

/**
 * @test Test the function to get a set id through its position
 * @pre The set is a non-NULL pointer with at least one id, an incorrect position is searched
 * @post The output must be -1
 */
void test2_set_get_id_at_position ();
#endif
