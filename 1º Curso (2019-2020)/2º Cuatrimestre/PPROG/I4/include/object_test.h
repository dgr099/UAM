/** 
 * @brief It declares the tests for the object module
 * 
 * @file object_test.h
 * @author Daniel Cerrato Sánchez
 * @version 1.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H
/**
 * @test Test the function of creating an object
 * @pre An id as parameter
 * @post A non-null pointer to the created object
 */
void test1_object_create ();

/**
 * @test Test the function of creating an object
 * @pre The object is a non-NULL pointer with correct id
 * @post The object id must be the one entered when creating it
 */
void test2_object_create ();

/**
 * @test Test the function of creating an object
 * @pre The object is a non-NULL pointer with correct id
 * @post The object movable atribute must be the start one
 */
void test3_object_create();

/**
 * @test Test the function of creating an object
 * @pre The object is a non-NULL pointer with correct id
 * @post The object hidden atribute must be the start one
 */
void test4_object_create();

/**
 * @test Test the function of creating an object
 * @pre The object is a non-NULL pointer with correct id
 * @post The object iluminate atribute must be the start one
 */
void test5_object_create();

/**
 * @test Test the function of creating an object
 * @pre The object is a non-NULL pointer with correct id
 * @post The object open atribute must be the start one
 */
void test6_object_create();

/**
 * @test Test the function of creating an object
 * @pre The object is a non-NULL pointer with correct id
 * @post The object turned atribute must be the start one
 */
void test7_object_create();

/**
 * @test Test the function of creating an object
 * @pre The object is a non-NULL pointer with correct id
 * @post The object dependency atribute must be the start one
 */
void test8_object_create();

/**
 * @test Test the function of creating an object
 * @pre The object is a non-NULL pointer with correct id
 * @post The object incompatible atribute must be the start one
 */
void test9_object_create();

/**
 * @test Test the function to rename an object
 * @pre The object is a non-NULL pointer, the name is correct
 * @post The output must be OK
 */
void test1_object_set_name ();

/**
 * @test Test the function to rename an object
 * @pre The object is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_object_set_name ();

/**
 * @test Test the function to change the description of an object
 * @pre The object is a non-NULL pointer, the description is correct
 * @post The output must be OK
 */
void test1_object_set_description ();

/**
 * @test Test the function to change the description of an object
 * @pre The object is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_object_set_description ();

/**
 * @test Test the function to get the description of an object
 * @pre The object is a non-NULL pointer with correct description
 * @post The comparison between the description and the phrase to compare must be 0
 */
void test1_object_get_description ();

/**
 * @test Test the function to get the description of an object
 * @pre The object is a pointer to NULL
 * @post The output must be NULL
 */
void test2_object_get_description ();

/**
 * @test Test the function to get the id of an object
 * @pre The object is a non-NULL pointer with correct id
 * @post The output must be the correct id
 */
void test1_object_get_id ();

/**
 * @test Test the function to get the id of an object
 * @pre The object is a pointer to NULL
 * @post The output must be NULL
 */
void test2_object_get_id ();

/**
 * @test Test the function to get the name of an object
 * @pre Object is a non-NULL pointer with correct name
 * @post The comparison between the name and the word to compare must be 0
 */
void test1_object_get_name ();

/**
 * @test Test the function to get the name of an object
 * @pre The object is a pointer to NULL
 * @post The output must be NULL
 */
void test2_object_get_name ();

/**
 * @test Test the function to set movable of an object
 * @pre The movable atribute
 * @post The output must be OK
 */
void test1_object_set_movable();

/**
 * @test Test the function to set movable of an object
 * @pre The object is a NULL pointer
 * @post The output must be ERROR
 */
void test2_object_set_movable();

/**
 * @test Test the function to get movable of an object
 * @pre The movable you want to set and the object
 * @post The output must be the movable you set before
 */
void test1_object_get_movable();

/**
 * @test Test the function to get movable of an object
 * @pre The object is a NULL pointer
 * @post The output must be ERROR
 */
void test2_object_get_movable();

/**
 * @test Test the function to set dependency of an object
 * @pre The dependency atribute
 * @post The output must be OK
 */
void test1_object_set_dependency();

/**
 * @test Test the function to set dependency of an object
 * @pre The object is a NULL pointer
 * @post The output must be ERROR
 */
void test2_object_set_dependency();

/**
 * @test Test the function to get dependency of an object
 * @pre The dependency you want to set and the object
 * @post The output must be the dependency you set before
 */
void test1_object_get_dependency();

/**
 * @test Test the function to get dependency of an object
 * @pre The object is a NULL pointer
 * @post The output must be NO_ID
 */
void test2_object_get_dependency();

/**
 * @test Test the function to set incompatible of an object
 * @pre The incompatible atribute
 * @post The output must be OK
 */
void test1_object_set_incompatible();

/**
 * @test Test the function to set incompatible of an object
 * @pre The object is a NULL pointer
 * @post The output must be ERROR
 */
void test2_object_set_incompatible();

/**
 * @test Test the function to get incompatible of an object
 * @pre The incompatible you want to set and the object
 * @post The output must be the incompatible you set before
 */
void test1_object_get_incompatible();

/**
 * @test Test the function to get incompatible of an object
 * @pre The object is a NULL pointer
 * @post The output must be NO_ID
 */
void test2_object_get_incompatible();

/**
 * @test Test the function to turSned an object
 * @pre The turned atribute
 * @post The output must be OK
 */
void test1_object_turned();

/**
 * @test Test the function to turned an object
 * @pre The object is a NULL pointer
 * @post The output must be ERROR
 */
void test2_object_turned();

/**
 * @test Test the function to get turned of an object
 * @pre The object and the turner
 * @post The output must be the one you have written
 */
void test1_object_get_turned();
#endif
