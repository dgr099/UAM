#include <stdio.h>
#include "../include/test.h"
#include "../include/npc.h"
/** 
 * @brief It declares the tests for the Npc module
 * 
 * @file npc_test.h
 * @author David Teófilo Garitagoitia Romero
 * @version 1.0 
 * @date 10-06-2020
 * @copyright GNU Public License
 */

#ifndef NPC_TEST_H
#define NPC_TEST_H
/**
 * @test Test the npc creation function
 * @pre An identifier as a parameter
 * @post A non-null pointer to the created space
 */
void test1_npc_init();
/**
 * @test Test the npc creation function
 * @pre An identifier as a parameter
 * @post The npc identifier is the one entered
 */
void test2_npc_init();
/**
 * @test Test the npc creation function
 * @pre An identifier as a parameter
 * @post The guilty start at false
 */
void test3_npc_init();
/**
 * @test Test the npc creation function
 * @pre An identifier as a parameter
 * @post The position start at NO_ID
 */
void test4_npc_init();
/**
 * @test Test the npc set name function
 * @pre An identifier as a parameter and the name of the npc
 * @post The name of the npc is placed without problems
 */
void test1_npc_set_name();
/**
 * @test Test the npc set name function
 * @pre The name of the npc is NULL
 * @post The output should be ERROR
 */
void test2_npc_set_name();
/**
 * @test Test the npc set name function
 * @pre A NULL npc pointer
 * @post The name of the npc is placed without problems
 */
void test3_npc_set_name();
/**
 * @test Test the npc add dialogue function
 * @pre An identifier as a parameteer and the dialogue you want to add
 * @post The dialogue of the npc is placed without problems
 */
void test1_npc_add_dialogue();
/**
 * @test Test the npc add dialogue function
 * @pre An identifier as a parameteer but the dialogue is NULL
 * @post The output must be ERROR
 */
void test2_npc_add_dialogue();
/**
 * @test Test the npc add dialogue function
 * @pre The npc is a NULL pointer
 * @post The output must be ERROR
 */
void test3_npc_add_dialogue();
/**
 * @test Test the npc set culpability function
 * @pre The culpability of the npc
 * @post The culpability of the npc is the one you entered
 */
void test1_npc_set_culpability();
/**
 * @test Test the npc set culpability function
 * @pre The culpability of the npc but the npc is a NULL pointer
 * @post The output must be ERROR
 */
void test2_npc_set_culpability();
/**
 * @test Test the npc get random dialogue function
 * @pre The dialogues you want to add
 * @post The dialogues of the npc is shown without problems
 */
void test1_npc_get_random_dialogue();
/**
 * @test Test the npc get random dialogue function
 * @pre The npc is a NULL pointer
 * @post The output must be ERROR
 */
void test2_npc_get_random_dialogue();
/**
 * @test Test the npc get name function
 * @pre The name of the npc
 * @post The output must be the name you have written
 */
void test1_npc_get_name();
/**
 * @test Test the npc get name function
 * @pre The name of the npc but the npc is a NULL pointer
 * @post The output must be NULL
 */
void test2_npc_get_name();
/**
 * @test Test the npc get guilty function
 * @pre The guilty of the npc
 * @post The output must be the guilty you have written
 */
void test1_npc_get_guilty();
/**
 * @test Test the npc get guilty function
 * @pre The guilty of the npc
 * @post The output must be the guilty you have written
 */
void test2_npc_get_guilty();
/**
 * @test Test the npc get guilty function
 * @pre The npc is a NULL pointer
 * @post The output must be ERROR
 */
void test3_npc_get_guilty();
/**
 * @test Test the npc destroy function
 * @pre The npc you want to destroy
 * @post The npc is destroyed without problems
 */
void test1_npc_destroy();
/**
 * @test Test the npc destroy function
 * @pre The npc is a NULL pointer
 * @post The output must be ERROR
 */
void test2_npc_destroy();
/**
 * @test Test the npc set position function
 * @pre The npc is a NULL pointer
 * @post The output must be ERROR
 */
void test1_npc_set_position();
/**
 * @test Test the npc set position function
 * @pre The npc is a NULL pointer
 * @post The position was set without problems
 */
void test2_npc_set_position();
/**
 * @test Test the npc get initial function
 * @pre The npc you want to know their initial and the initial of the npc
 * @post The output must be the initial you have written
 */
void test1_npc_get_initial();
/**
 * @test Test the npc get initial function
 * @pre The npc is a NULL pointer
 * @post The output must be ERROR
 */
void test2_npc_get_initial();
/**
 * @test Test the npc set number of dialogues function
 * @pre The npc is a NULL pointer
 * @post The output must be ERROR
 */
void test1_npc_set_number_dialogues();
/**
 * @test Test the npc set number of dialogues function
 * @pre The npc and the number of dialogues you want to add
 * @post The output must be OK
 */
void test2_npc_set_number_dialogues();
/**
 * @test Test the npc set descripption function
 * @pre The npc and the description you want to add
 * @post The output must be OK
 */
void test1_npc_set_description();
/**
 * @test Test the npc set descripption function
 * @pre The npc but the description is NULL
 * @post The output must be ERROR
 */
void test2_npc_set_description();
/**
 * @test Test the npc set descripption function
 * @pre The npc is a NULL pointer
 * @post The output must be ERROR
 */
void test3_npc_set_description();
/**
 * @test Test the npc get descripption function
 * @pre The npc and the description
 * @post The output must be the description yo have written
 */
void test1_npc_get_description();
#endif