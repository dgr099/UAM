/** 
 * @brief It declares the tests for the link module
 * 
 * @file link_test.h
 * @author Daniel Cerrato Sánchez
 * @version 1.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test the link creation function
 * @pre An id as parameter
 * @post A non-null pointer to the created link
 */
void test1_link_create ();

/**
 * @test Test the link creation function
 * @pre The link is a non-NULL pointer with correct id
 * @post The link id must be the one entered when creating it
 */
void test2_link_create ();

/**
 * @test Test the function to rename a link
 * @pre The link is a non-NULL pointer, the name is correct
 * @post The output must be OK
 */
void test1_link_set_name ();

/**
 * @test Test the function to rename a link
 * @pre The link is a non-NULL pointer, the name is NULL
 * @post The output must be ERROR
 */
void test2_link_set_name ();

/**
 * @test Test the function to change the exit id of a link
 * @pre The link is a non-NULL pointer, the exit id is correct
 * @post The output must be OK
 */
void test1_link_set_id1 ();

/**
 * @test Test the function to change the exit id of a link
 * @pre The link is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_link_set_id1 ();

/**
 * @test Test the function to change the input id of a link
 * @pre The link is a non-NULL pointer, the input id is correct
 * @post The output must be OK
 */
void test1_link_set_id2 ();

/**
 * @test Test the function to change the input id of a link
 * @pre The link is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_link_set_id2 ();

/**
 * @test Test the function to change the opening state of a link
 * @pre The link is a non-NULL pointer, the state is 0 (open)
 * @post The output must be OK
 */
void test1_link_set_open ();

/**
 * @test Test the function to change the opening state of a link
 * @pre The link is a non-NULL pointer, the state is 1 (closed)
 * @post The output must be OK
 */
void test2_link_set_open ();

/**
 * @test Test the function to change the opening state of a link
 * @pre The link is a pointer to NULL
 * @post The output must be ERROR
 */
void test3_link_set_open ();

/**
 * @test Test the function to get the id of a link
 * @pre The link is a non-NULL pointer with correct id
 * @post The output must be the id entered when creating it
 */
void test1_link_get_id ();

/**
 * @test Test the function to get the id of a link
 * @pre The link is a pointer to NULL
 * @post The output must be NO_ID
 */
void test2_link_get_id ();

/**
 * @test Test the function to get the opening status of a link
 * @pre The link is a non-NULL pointer with status 0 (open)
 * @post The output must be TRUE
 */
void test1_link_is_open ();

/**
 * @test Test the function to get the opening status of a link
 * @pre The link is a non-NULL pointer with status 1 (closed)
 * @post The output must be FALSE
 */
void test2_link_is_open ();

/**
 * @test Test the function to get the opening status of a link
 * @pre The link is a pointer to NULL
 * @post The output must be FALSE
 */
void test3_link_is_open ();

/**
 * @test Test the function to get the exit id of a link
 * @pre The link is a non-NULL pointer with correct exit id
 * @post The output must be the output id
 */
void test1_link_get_id1 ();

/**
 * @test Test the function to get the exit id of a link
 * @pre The link is a pointer to NULL
 * @post The output must be NO_ID
 */
void test2_link_get_id1 ();

/**
 * @test Test the function to get the input id of a link
 * @pre The link is a non-NULL pointer with correct input id
 * @post The output must be the input id
 */
void test1_link_get_id2 ();

/**
 * @test Test the function to get the input id of a link
 * @pre The link is a pointer to NULL
 * @post The output must be NO_ID
 */
void test2_link_get_id2 ();

/**
 * @test Test the function to get the name of a link
 * @pre The link is a non-NULL pointer with correct name
 * @post The comparison between the name and the word to compare must be 0
 */
void test1_link_get_name ();

/**
 * @test Test the function to get the name of a link
 * @pre The link is a pointer to NULL
 * @post The output must be NULL
 */
void test2_link_get_name ();

#endif
