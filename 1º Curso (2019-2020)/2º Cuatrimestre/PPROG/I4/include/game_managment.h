/**
* @brief Library to manage the load os spaces
*
* @file game_managment.h
* @version 1.0
* @date 08-02-2020
* @author David Teófilo Garitagoitia Romero y José Manuel García Giráldez
*/
#ifndef game_managment_H
#define game_managment_H
#include "../include/game.h"
/**
* @brief load the spaces of the game, opening the file data.dat  
*
* game_managment_load_spaces
*
* @date 06-02-2020
* @author José Manuel García Giráldez
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_load_spaces(Game *game, char *filename);
/**
* @brief load the objects of the game, opening the file data.dat  
*
* game_managment_load_objects
*
* @date 06-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_load_objects(Game *game, char *filename);
/**
* @brief load the player of the game, opening the file data.dat  
*
* game_managment_load_player
*
* @date 15-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_load_player(Game *game, char *filename);
/**
* @brief load the links of the game, opening the file data.dat  
*
* game_managment_load_links
*
* @date 15-03-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_load_links(Game *game, char *filename);
/**
* @brief save the progress of the game
*
* game_managment_save
*
* @date 15-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_save(Game *game, char *filename);
/**
* @brief load the progress of the game  
*
* game_managment_load
*
* @date 15-04-2020
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_load(Game *game, char *filename);
/**
* @brief load the cmdAnswers of the game, opening the file .dat  
*
* game_managment_load_cmdAnswers
*
* @date 15-03-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_load_CmdAnswers(Game *game, char *filename);
/**
* @brief load the npc of the game, opening the file .dat  
*
* game_managment_load_npc
*
* @date 15-03-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_load_npc(Game *game, char *filename);
/**
* @brief load the tutorial of the game, opening the file .dat  
*
* game_managment_load_tutorial
*
* @date 15-03-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_load_tutorial(Game *game, char *filename);
/**
* @brief load the ending of the game, opening the file .dat  
*
* game_managment_load_ending
*
* @date 15-03-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_managment_load_ending(Game *game, char *filename);
#endif
