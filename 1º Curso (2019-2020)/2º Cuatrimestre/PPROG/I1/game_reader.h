/**
* @brief Library to manage the load os spaces
*
* @file game_reader.h
* @version 1.0
* @date 08-02-2020
* @author David Teófilo Garitagoitia Romero
*/
#ifndef GAME_READER_H
#define GAME_READER_H
#include "types.h"
#include "game.h"
/**
* @brief load the spaces of the game, opening the file data.dat  
*
* game_load_spaces
*
* @date 06-02-2019
* @author: David Teófilo Garitagoitia Romero
*
* @param game the game from which we will get the information
* @param filename the name of the file we work with
* @return the status of the file
*/
STATUS game_reader_load_spaces(Game *game, char *filename);
#endif
