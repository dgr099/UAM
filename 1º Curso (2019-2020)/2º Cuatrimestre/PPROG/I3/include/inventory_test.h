/** 
 * @brief It declares the tests for the inventory module
 * 
 * @file inventory_test.h
 * @author Daniel Cerrato Sánchez
 * @version 1.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H


/**
 * @test Test the inventory creation function
 * @pre An id and a maximum of integer objects as parameters
 * @post A non-null pointer to the created inventory
 */
void test1_inventory_create();

/**
 * @test Test the inventory creation function
 * @pre Inventory is a non-NULL pointer with correct id
 * @post The inventory id must be the one entered when creating it
 */
void test2_inventory_create();

/**
 * @test Test the function to get the inventory item set
 * @pre Inventory is a non-NULL pointer with correct set
 * @post The output must be a set as a non-NULL pointer
 */
void test1_inventory_get_inside();

/**
 * @test Test the function to get the inventory item set
 * @pre Inventory is a pointer to NULL
 * @post The output must be a set as a pointer to NULL
 */
void test2_inventory_get_inside();

/**
 * @test Test the function to add objects to an inventory
 * @pre Inventory is a non-NULL pointer, object id is correct
 * @post The output must be OK
 */
void test1_inventory_add();

/**
 * @test Test the function to add objects to an inventory
 * @pre Inventory is a non-NULL pointer, object id is wrong
 * @post The output must be ERROR
 */
void test2_inventory_add();

/**
 * @test Test the function to add objects to an inventory
 * @pre Inventory is a pointer to NULL
 * @post The output must be ERROR
 */
void test3_inventory_add();

/**
 * @test Test the function to remove objects from an inventory
 * @pre Inventory is a non-NULL pointer with correct object ids, correct object is searched
 * @post The output must be OK
 */
void test1_inventory_dell();

/**
 * @test Test the function to remove objects from an inventory
 * @pre Inventory is a non-NULL pointer with no object ids
 * @post The output must be ERROR
 */
void test2_inventory_dell ();

/**
 * @test Test the function to remove objects from an inventory
 * @pre Inventory is a pointer to NULL
 * @post The output must be ERROR
 */
void test3_inventory_dell ();

/**
 * @test Test the function to know if an object is in an inventory
 * @pre Inventory is a non-NULL pointer to an object, a correct object is searched
 * @post The output must be TRUE
 */
void test1_inventory_is_object ();

/**
 * @test Test the function to know if an object is in an inventory
 * @pre Inventory is a non-NULL pointer with no objects
 * @post The output must be FALSE
 */
void test2_inventory_is_object ();

/**
 * @test Test the function to know if an object is in an inventory
 * @pre Inventory is a non-NULL pointer to an object, an incorrect object is searched
 * @post The output must be FALSE
 */
void test3_inventory_is_object ();

/**
 * @test Test the function to know if an object is in an inventory
 * @pre Inventory is a pointer to NULL
 * @post The output must be FALSE
 */
void test4_inventory_is_object ();

/**
 * @test Test the function to get the maximum number of objects in an inventory
 * @pre Inventory is a non-NULL pointer with correct maximum
 * @post The maximum inventory must be the one entered when creating it
 */
void test1_inventory_get_max ();

/**
 * @test Test the function to get the maximum number of objects in an inventory
 * @pre Inventory is a pointer to NULL
 * @post The output must be -1
 */
void test2_inventory_get_max ();

/**
 * @test Test the function to know if an inventory is full
 * @pre Inventory is a non-NULL pointer, inventory is full
 * @post The output must be TRUE
 */
void test1_inventory_is_full ();

/**
 * @test Test the function to know if an inventory is full
 * @pre Inventory is a non-NULL pointer, inventory is not full
 * @post The output must be FALSE
 */
void test2_inventory_is_full ();

/**
 * @test Test the function to know if an inventory is full
 * @pre Inventory is a pointer to NULL
 * @post The output must be TRUE
 */
void test3_inventory_is_full ();

/**
 * @test Test the function to know if an inventory is empty
 * @pre Inventory is a non-NULL pointer, inventory is empty
 * @post The output must be TRUE
 */
void test1_inventory_is_emty ();

/**
 * @test Test the function to know if an inventory is empty
 * @pre Inventory is a non-NULL pointer, inventory is not empty
 * @post The output must be FALSE
 */
void test2_inventory_is_emty ();

/**
 * @test Test the function to know if an inventory is empty
 * @pre Inventory is a pointer to NULL
 * @post The output must be TRUE
 */
void test3_inventory_is_emty ();

/**
 * @test Test the function to get the id of an inventory
 * @pre Inventory is a non-NULL pointer with correct id
 * @post The inventory id must be the one entered when creating it
 */
void test1_inventory_get_id ();

/**
 * @test Test the function to get the id of an inventory
 * @pre Inventory is a pointer to NULL
 * @post The output must be NO_ID
 */
void test2_inventory_get_id ();
#endif  
