/** \file events.h
 * The header file of the events.c file. Here you cand find the protoypes of all functions of this file
 * */

#ifndef __EVENTS_H__
#define __EVENTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ai.h"
#include "constants.h"
#include "graphics.h"
#include "io.h"
#include "othellier.h"
#include "structures.h"

/** \brief This function allows the program to redirect a ^C action (SIGINT signal) in order to display a short message
 * informing them the program will quit and the game will not be saved */
void capture_SIGINT();


/** \brief This function allows the program to cancel the last move upon the resquest of the user
 * @param game : pointer to the Game structure
 *
 * Tests if a game is in progress. If so, cancels 1 move if it is a Human Vs Human game, 2 for a Human Vs Computer game. Clears the screen and displays the game board. */
void event_cancel(Game* game);


/** \brief This function allows the program to uncancel the last move upon the resquest of the user
 * @param game : pointer to the Game structure
 *
 * Tests if a game is in progress. If so, uncancels 1 move if it is a Human Vs Human game, 2 for a Human Vs Computer game. Clears the screen and displays the game board. */
void event_uncancel(Game* game);


/** \brief This function allows the program to display the help upon the resquest of the user
 *
 * Clears the current screen and displays the help. */
void event_help();


/** \brief This function allows the program to load a game from a text file upon the resquest of the user
 * @param game : pointer to the Game structure
 * \return the pointer to the modified game 
 * 
 * Tests if a game is in progress. If so, asks for its savingand destroys the current game. Loads a new game, displays the board and the turn if the end of game has not been reached. 
 * Performs ans end of game action otherwise and returns the pointer to the new game.*/
Game* event_load(Game* game);


/** \brief This function allows the program to save the current game upon the resquest of the user
 * @param game : pointer to the Game structure
 * 
 * Tests if a game is in progress. If so, asks for its saving. */
void event_save(Game* game);


/** \brief This function allows the program to create a new game upon the resquest of the user
 * @param game : pointer to the Game structure
 * \return the pointer to the modified game
 * 
 * If a game is already in progress, asks for its saving and destroys it. Initializes a new game, asks for the type of the game, asks for the names and the colors, 
 * displays the board and the turn. Calls play_ai() if the computer needs to play. returns the ne pointer to the game. */
Game* event_new(Game* game);


/** \brief This function allows the program to play the coordinates the user has entered if it was not one of the recognized commands
 * @param game : pointer to the Game structure
 * @param command : the command executed in the main, which is supposed to be the coordinate of the move
 * \return the pointer to the modified game
 * 
 * For the game in progress, tries to play the move related to the coordinates entered. If they don't have the proper format, returns an error code. Same for non legal 
 * coordinates. Once the move played, performs and end of game action if needed. Displays the turn and makes the computer play if needed. Returns the game if modified by play_ai(). */
Game* event_other(Game* game, char* command);


/** \brief This function allows the program to quit properly, by freeing the memory 
 * @param game : pointer to the Game structure
 *
 * This function tests if the current game was saved or not. If not so, it asks the user for it and demands a name for the backup file. 
 * That done, it frees the previous allocated memory and exits the program with the EXIT_SUCCESS code. */
void event_quit(Game* game);

#endif


