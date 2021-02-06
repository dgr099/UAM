/** 
 * @brief It declares the tests for the dice module
 * 
 * @file dice_test.h
 * @author Daniel Cerrato Sánchez
 * @version 1.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */

#ifndef DICE_TEST_H
#define DICE_TEST_H
/**
 * @test Test the dice creation function
 * @pre An id, a maximum value and a minimum value in integer value as parameters, the maximum is greater than the minimum
 * @post A non-null pointer to the created die
 */
void test1_dice_create ();

/**
 * @test Test the dice creation function
 * @pre An id, a maximum value and a minimum value in integer value as parameters, the minimum is greater than the maximum
 * @post A null pointer to the created die
 */
void test2_dice_create ();

/**
 * @test Test the function to get a value from the dice
 * @pre The die is a non-NULL pointer with the correct fields
 * @post The output must be greater than or equal to the minimum value entered
 */
void test1_dice_roll ();

/**
 * @test Test the function to get a value from the dice
 * @pre The die is a non-NULL pointer with the correct fields
 * @post The output must be less than or equal to the maximum value entered
 */
void test2_dice_roll ();

/**
 * @test Test the function to get a value from the dice
 * @pre The die is a pointer to NULL
 * @post The output must be -1
 */
void test3_dice_roll ();

/**
 * @test Test the function to get the last value taken with the given
 * @pre The die is a non-NULL pointer with the correct fields, after having thrown
 * @post The output must be greater than or equal to the minimum value entered
 */
void test1_dice_get_last ();

/**
 * @test Test the function to get the last value taken with the given
 * @pre The die is a non-NULL pointer with the correct fields, after having thrown
 * @post The output must be less than or equal to the maximum value entered
 */
void test2_dice_get_last ();

/**
 * @test Test the function to get the last value taken with the given
 * @pre The die is a non-NULL pointer with the correct fields, without having thrown
 * @post The output must be 0
 */
void test3_dice_get_last ();

/**
 * @test Test the function to get the last value taken with the given
 * @pre The die is a pointer to NULL
 * @post The output must be -1
 */
void test4_dice_get_last ();
#endif
