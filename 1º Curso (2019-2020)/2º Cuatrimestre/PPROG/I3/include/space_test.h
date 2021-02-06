/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Daniel Cerrato Sánchez
 * @version 3.0 
 * @date 09-06-2020
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test the space creation function
 * @pre An identifier as a parameter
 * @post A non-null pointer to the created space
 */
void test1_space_create ();

/**
 * @test Test the space creation function
 * @pre An identifier as a parameter
 * @post The space identifier is the one entered
 */
void test2_space_create ();

/**
 * @test Test the function to set the name of a space
 * @pre Name to set the space
 * @post The output must be OK
 */
void test1_space_set_name ();

/**
 * @test Test the function to set the name of a space
 * @pre The space to set the name to is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_space_set_name ();

/**
 * @test Test the function to set the name of a space
 * @pre The space is a non-NULL pointer, but the name to set is NULL
 * @post The output must be ERROR
 */
void test3_space_set_name ();
/**
 * @test Test the function to set the north of a space
 * @pre The space is a non-NULL pointer and the id is correct
 * @post The output must be OK
 */
void test1_space_set_north ();

/**
 * @test Test the function to set the north of a space
 * @pre Space is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_space_set_north ();

/**
 * @test Test the function to set the south of a space
 * @pre The space is a non-NULL pointer and the id is correct
 * @post The output must be OK
 */
void test1_space_set_south ();

/**
 * @test Test the function to set the south of a space
 * @pre Space is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_space_set_south ();

/**
 * @test Test the function to set the east of a space
 * @pre The space is a non-NULL pointer and the id is correct
 * @post The output must be OK
 */
void test1_space_set_east ();

/**
 * @test Test the function to set the east of a space
 * @pre Space is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_space_set_east ();

/**
 * @test Test the function to set the west of a space
 * @pre The space is a non-NULL pointer and the id is correct
 * @post The output must be OK
 */
void test1_space_set_west ();

/**
 * @test Test the function to set the west of a space
 * @pre Space is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_space_set_west ();

/**
 * @test Test the function to set objects in a space
 * @pre The space is a non-NULL pointer and is passed a correct id
 * @post The output must be OK
 */
void test1_space_set_object ();

/**
 * @test Test the function to set objects in a space
 * @pre Space is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_space_set_object ();

/**
 * @test Test the function to get the name of a space
 * @pre Space is a non-NULL named pointer
 * @post The comparison between the last word and the name must be correct
 */
void test1_space_get_name ();

/**
 * @test Test the function to get the name of a space
 * @pre Space is a pointer to NULL
 * @post The output must be NULL
 */
void test2_space_get_name ();

/**
 * @test Test the function to get the object set of a space
 * @pre The space is a non-NULL pointer, but without adding objects
 * @post The output must be different from NULL
 */
void test1_space_get_object ();

/**
 * @test Test the function to get the object of a space
 * @pre Space is a pointer to NULL
 * @post The output must be NULL
 */
void test2_space_get_object ();

/**
 * @test Test the function to get the north of a space
 * @pre Space is a non-NULL pointer with space to the north
 * @post The output must be the id of the space to the north
 */
void test1_space_get_north ();

/**
 * @test Test the function to get the north of a space
 * @pre Space is a pointer to NULL
 * @post The output must be NO_ID
 */
void test2_space_get_north ();

/**
 * @test Test the function to get the south of a space
 * @pre Space is a non-NULL pointer with space to the south
 * @post The output must be the id of the space to the south
 */
void test1_space_get_south ();

/**
 * @test Test the function to get the south of a space
 * @pre Space is a pointer to NULL
 * @post The output must be NO_ID
 */
void test2_space_get_south ();

/**
 * @test Test the function to get the east of a space
 * @pre Space is a non-NULL pointer with space to the east
 * @post The output must be the ide of the space to the east
 */
void test1_space_get_east ();

/**
 * @test Test the function to get the south of a space
 * @pre Space is a pointer to NULL
 * @post The output must be NO_ID
 */
void test2_space_get_east ();

/**
 * @test Test the function to get the west of a space
 * @pre Space is a non-NULL pointer with space to the west
 * @post The output must be the space id to the west
 */
void test1_space_get_west ();

/**
 * @test Test the function to get the south of a space
 * @pre Space is a pointer to NULL
 * @post The output must be NO_ID
 */
void test2_space_get_west ();

/**
 * @test Test the function to get the id of a space
 * @pre Space is a non-NULL pointer with correct id
 * @post The output must be the id provided
 */
void test1_space_get_id ();

/**
 * @test Test the function to get the id of a space
 * @pre Space is a pointer to NULL
 * @post The output must be NO_ID
 */
void test2_space_get_id ();
#endif
