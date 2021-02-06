/** 
 * @brief It declares the tests for the player module
 * 
 * @file player_test.h
 * @author Daniel Cerrato Sánchez
 * @version 1.0 
 * @date 08-06-2020
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @test Test the player creation function
 * @pre An id and an integer for the number of objects they can carry as parameters
 * @post A non-null pointer to the created player
 */
void test1_player_create ();

/**
 * @test Test the player creation function
 * @pre Player is a non-NULL pointer
 * @post The player id must be processed when creating it
 */
void test2_player_create ();

/**
 * @test Test the function of adding an object to the player
 * @pre The player is a non-NULL pointer, but the object is a NULL pointer
 * @post The output must be ERROR
 */
void test1_player_add_object ();

/**
 * @test Test the function of adding an object to the player
 * @pre The player is a non-NULL pointer, the object is a NULL pointer
 * @post The output must be ERROR
 */
void test2_player_add_object ();

/**
 * @test Test the function of adding an object to the player
 * @pre Player is a NULL pointer, object is a non-NULL pointer
 * @post The output must be ERROR
 */
void test3_player_add_object ();

/**
 * @test Test the deletion function of a player object
 * @pre Player and object are non-NULL pointers, correct object is searched
 * @post The output must be OK
 */
void test1_player_dell_object ();

/**
 * @test Test the deletion function of a player object
 * @pre Player and object are non-NULL pointers, player has no object
 * @post The output must be ERROR
 */
void test2_player_dell_object ();

/**
 * @test Test the deletion function of a player object
 * @pre Player and objects are non-NULL pointers, wrong object is searched
 * @post The output must be ERROR
 */
void test3_player_dell_object ();

/**
 * @test Test the deletion function of a player object
 * @pre Player is a pointer to NULL
 * @post The output must be ERROR
 */
void test4_player_dell_object ();

/**
 * @test Test a player's name change function
 * @pre The player is a non-NULL pointer, the name is correct
 * @post The output must be OK
 */
void test1_player_set_name ();

/**
 * @test Test a player's name change function
 * @pre The player is a non-NULL pointer, the name is NULL
 * @post The output must be ERROR
 */
void test2_player_set_name ();

/**
 * @test Test function to get player name
 * @pre Player is a non-NULL pointer with a correct name
 * @post The comparison between the name and the word to compare must be 0
 */
void test1_player_get_name ();

/**
 * @test Test function to get player name
 * @pre Player is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_player_get_name ();

/**
 * @test Test a player's location change function
 * @pre The player is a non-NULL pointer, the space is correct
 * @post The output must be OK
 */
void test1_player_set_location ();

/**
 * @test Test a player's location change function
 * @pre Player is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_player_set_location ();

/**
 * @test Test the function to get the location of a player
 * @pre The player is a non-NULL pointer in a correct space
 * @post The output must be OK
 */
void test1_player_get_location ();

/**
 * @test Test the function to get the location of a player
 * @pre Player is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_player_get_location ();
/**
 * @test Test a player's id change function
 * @pre The player is a non-NULL pointer, the id is correct
 * @post The output must be OK
 */
void test1_player_set_id ();

/**
 * @test Test a player's id change function
 * @pre Player is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_player_set_id ();

/**
 * @test Test the function to get the id of a player
 * @pre The player is a non-NULL pointer with a correct id
 * @post The output must be OK
 */
void test1_player_get_id ();

/**
 * @test Test the function to get the id of a player
 * @pre Player is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_player_get_id ();

/**
 * @test Test function to get player item set
 * @pre Player is a non-NULL pointer with a correct set
 * @post The output must be OK
 */
void test1_player_get_inventory ();

/**
 * @test Test function to get player item set
 * @pre Player is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_player_get_inventory ();
#endif
