/** 
 * @brief It declares the tests for the cmdAnswer module
 * 
 * @file cmdAnswer_test.h
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */

#ifndef CMDANSWER_TEST_H
#define CMDANSWER_TEST_H
/**
 * @test Test the CmdAnswer creation function
 * @pre Nothing
 * @post A non-null pointer to the created cmda
 */
void test1_CmdAnswer_init();
/**
 * @test Test the CmdAnswer add new error function
 * @pre the cmda created before
 * @post No errors after add new error to the cmda 
 */
void test1_CmdAnswer_add_new_error();
/**
 * @test Test the CmdAnswer add new error function
 * @pre the cmda is a NULL pointer
 * @post the output must be ERROR 
 */
void test2_CmdAnswer_add_new_error();
/**
 * @test Test the CmdAnswer add error at function
 * @pre the cmda is a NULL pointer
 * @post the output must be ERROR
 */
void test1_CmdAnswer_add_error_at();
/**
 * @test Test the CmdAnswer add error at function
 * @pre The cmda is created but the level of error if higher than the errors of the cmda
 * @post the output must be ERROR 
 */
void test2_CmdAnswer_add_error_at();
/**
 * @test Test the CmdAnswer add error at function
 * @pre The cmda is created and the level it is in the cmda error range
 * @post The output must be OK
 */
void test3_CmdAnswer_add_error_at();
/**
 * @test Test the CmdAnswer add error at function
 * @pre The cmda is created and the level it is in the cmda error range but the error is NULL
 * @post the output must be ERROR
 */
void test4_CmdAnswer_add_error_at();
/**
 * @test Test the CmdAnswer add OK
 * @pre The cmda is a NULL pointer
 * @post the output must be ERROR
 */
void test1_CmdAnser_add_ok();
/**
 * @test Test the CmdAnswer add OK
 * @pre A cmda pointer created before
 * @post the output must be OK
 */
void test2_CmdAnser_add_ok();
/**
 * @test Test the CmdAnswer add OK
 * @pre A cmda pointer created before but he ok answer is NULL
 * @post the output must be ERROR
 */
void test3_CmdAnser_add_ok();
/**
 * @test Test the CmdAnswer get random error
 * @pre A cmda pointer created before with two different errors
 * @post the output must be a random error between the two errors
 */
void test1_CmdAnswer_get_random_error();
/**
 * @test Test the CmdAnswer get random error
 * @pre A cmda pointer created before with two different errors but the level of error is higher than the maximum of the cmda
 * @post the output must be NULL
 */
void test2_CmdAnswer_get_random_error();
/**
 * @test Test the CmdAnswer get random error
 * @pre A cmda NULL pointer
 * @post the output must be NULL
 */
void test3_CmdAnswer_get_random_error();
/**
 * @test Test the CmdAnswer get random ok
 * @pre A cmda pointer created before with two different ok answer
 * @post the output must be different to NULL
 */
void test1_CmdAnswer_get_random_ok();
/**
 * @test Test the CmdAnswer get random ok
 * @pre A cmda NULL pointer
 * @post the output must be NULL
 */
void test2_CmdAnswer_get_random_ok();

#endif