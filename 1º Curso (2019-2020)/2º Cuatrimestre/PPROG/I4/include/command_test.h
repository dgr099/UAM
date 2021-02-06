/** 
 * @brief It declares the tests for the command module
 * 
 * @file dice_test.h
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */

#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H
/**
 * @test Test the command creation function
 * @pre
 * @post A non-null pointer to the created space
 */
void test1_command_init();
/**
 * @test Test the command creation function
 * @pre An identifier as a parameter
 * @post the argument must be '\0'
 */
void test2_command_init();
/**
 * @test Test the command creation function
 * @pre An identifier as a parameter
 * @post The status must be ERROR
 */
void test3_command_init();
/**
 * @test Test the command creation function
 * @pre An identifier as a parameter
 * @post The principal cmd must be NO_CMD
 */
void test4_command_init();
/**
 * @test Test the command set principal cmd function
 * @pre An identifier as a parameter
 * @post The principal cmd is the one entered
 */
void test1_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre The command to set the principal cmd to is a pointer to NULL
 * @post The output must be ERROR
 */
void test2_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be EXIT
 */
void test3_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be TAKE
 */
void test4_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be DROP
 */
void test5_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be ROLL
 */
void test6_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be MOVE
 */
void test7_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be INSPECT
 */
void test8_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be NEXT
 */
void test9_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be BACK
 */
void test10_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be RIGHT
 */
void test11_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be LEFT
 */
void test12_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be TURNON
 */
void test13_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be TURNOFF
 */
void test14_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be LOAD
 */
void test15_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be SAVE
 */
void test16_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be TALK
 */
void test17_command_set_principal_cmd();
/**
 * @test Test the command set principal cmd function
 * @pre An cmd as a parameter
 * @post The principal cmd must be ACCUSE
 */
void test18_command_set_principal_cmd();
/**
 * @test Test the command set status function
 * @pre An cmd as a parameter
 * @post The status is OK
 */
void test1_command_set_status();
/**
 * @test Test the command set status function
 * @pre The cmd to set the status is NULL
 * @post It should return ERROR
 */
void test2_command_set_status();
/**
 * @test Test the command set status function
 * @pre The status is NULL
 * @post It should return ERROR
 */
void test3_command_set_status();
/**
 * @test Test the command set argument function
 * @pre An cmd as a parameter
 * @post The argument of the cmd is argument
 */
void test1_command_set_argument();
/**
 * @test Test the command set argument function
 * @pre An cmd NULL as a parameter
 * @post It should be an ERROR
 */
void test2_command_set_argument();
/**
 * @test Test the command set argument function
 * @pre The argument is NULL
 * @post It should be an ERROR
 */
void test3_command_set_argument();
/**
 * @test Test the command destroy function
 * @pre The cmd as a parameter
 * @post No problems destroying the command
 */
void test1_command_destroy();
/**
 * @test Test the command destroy function
 * @pre The cmd to destroy is a NULL pointer
 * @post It should be an ERROR
 */
void test2_command_destroy();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is "no se que estoy poniendo" (unknown command)
 * @post The principal cmd must be unknow
 */
void test1_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is "\n" (unknown)
 * @post The argument must be "\0"
 */
void test2_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is e (exit)
 * @post The principal cmd must be exit
 */
void test3_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is e (exit)
 * @post The principal cmd must be exit
 */
void test4_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is t (take without argument)
 * @post The argument should be "\0"
 */
void test5_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is take 2 (take and the argument is 2)
 * @post The principal cmd must be take
 */
void test6_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is take 2 (take and the argument is 2)
 * @post The principal cmd must be take and the argument must be 2
 */
void test7_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is i space (inspect and the argument is space)
 * @post The principal cmd must be inspect and the argument must be space
 */
void test8_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is inspect object (inspect and the argument is object)
 * @post The principal cmd must be inspect and the argument must be object
 */
void test9_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is m n (move and the argument is n)
 * @post The principal cmd must be move and the argument must be n
 */
void test10_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is move south (move and the argument is south)
 * @post The principal cmd must be move and the argument must be south
 */
void test11_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is n next (next)
 * @post The principal cmd must be next and the argument must be "\0"
 */
void test12_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is next (next)
 * @post The principal cmd must be next and the argument must be "\0"
 */
void test13_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is b (back)
 * @post The principal cmd must be back and the argument must be "\0"
 */
void test14_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is back (back)
 * @post The principal cmd must be back and the argument must be "\0"
 */
void test15_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is r (right)
 * @post The principal cmd must be right and the argument must be "\0"
 */
void test16_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is right (right)
 * @post The principal cmd must be right and the argument must be "\0"
 */
void test17_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is l (left)
 * @post The principal cmd must be left and the argument must be "\0"
 */
void test18_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is left da igual (left)
 * @post The principal cmd must be left and the argument must be "\0"
 */
void test19_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is rl (roll)
 * @post The principal cmd must be roll and the argument must be "\0"
 */
void test20_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is roll (roll)
 * @post The principal cmd must be roll and the argument must be "\0"
 */
void test21_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is d Pep (drop with Pep as argument)
 * @post The principal cmd must be drop and the argument must be Pep
 */
void test22_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is drop Pep (drop with Pep as argument)
 * @post The principal cmd must be drop and the argument must be Pep
 */
void test23_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is tn O (turn O)
 * @post The principal cmd must be turn on and the argument must be O
 */
void test24_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is turn on O (turn O)
 * @post The principal cmd must be turn on and the argument must be O
 */
void test25_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is tf 0 (turn off O)
 * @post The principal cmd must be turn off and the argument must be O
 */
void test26_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is turn off O (turn O)
 * @post The principal cmd must be turn off and the argument must be O
 */
void test27_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is open LNK with O (open with "LNK with O" as argument)
 * @post The principal cmd must be open and the argument must be LNK with O
 */
void test28_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is o LNK with O (open with "LNK with O" as argument)
 * @post The principal cmd must be open and the argument must be LNK with O
 */
void test29_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is tl with Pep (talk with "with Pep" as a argument)
 * @post The principal cmd must be talk and the argument must be with Pep
 */
void test30_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is talk with Pep (talk with "with Jhon" as a argument)
 * @post The principal cmd must be talk and the argument must be with Jhon
 */
void test31_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is a Pep (accuse with "P" as a argument)
 * @post The principal cmd must be accuse and the argument must be P
 */
void test32_command_get_user_input();
/**
 * @test Test the command get user input function
 * @pre Use the text file with the instructions, in this case, the instruction is accuse Pep (accuse with "P" as a argument)
 * @post The principal cmd must be accuse and the argument must be P
 */
void test33_command_get_user_input();

#endif
