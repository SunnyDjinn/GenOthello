/** \file user.h
 * The header file of the user.c file. Here you cand find the protoypes of all functions of this file
 * */

#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "io.h"
#include "structures.h"


/** \brief This function allows to ask users for the type of game they wqnt to play (Human vs Human or Human vs Computer)
 * \return 1 (H_VS_H) if the choice is "Human vs Human" and 2 (H_VS_C) if the choice is "Human vs Computer"
 * 
 * While the player has not entered a correct response (1 or 2), the function asks the question again. Returns the response of the user . */
short choose_game_type();


/** \brief This function allows to ask users for the color of pawns they want to have (for a Human vs Computer game)
 * \return 0 for the color BLACK, 1 for the color WHITE
 * 
 * While the player has not entered a correct response (1 or 2), the function asks the question again. Returns the response of the user, minus 1 (to have the BLACK or WHITE code). */
short choose_player_color();



/** \brief This function allows to ask users for their player names
 * @param game : a pointer to the Game structure
 * @param color : the color to which we want to give a name 
 * 
 * While the player has not entered a correct name, the function asks the question again. When the player has entered his name, the function saves it 
 * in the Game structure in the reserved place. It verifies, if the color in argument is WHITE and the type of the black player is HUMAN, that the two names are different. */
void enter_one_name(Game* game, short color);



/** \brief This function allows to ask users for their player names
 * @param game : a pointer to the Game structure
 * 
 * Calls the function enter_one_name() with two different parameters : BLACK for the black player and WHITE for the white one. */
void enter_players_names(Game* game);


/** \brief This function assigns a name to the computer player
 * @param game : a pointer to the Game structure
 * @param color : the color of the player the computer represents
 * 
 * Tests if the computer name is not already taken by the human player, and assigns it if not. Assigns an alternative name if so.  */
void give_computer_name(Game* game, short color);


/** \brief This function allows to ask users whether they wan to save the game in progress, and does it if they want to
 * @param game : a pointer to the Game structure
 * \return YES if the game has been saved, NO otherwise
 * 
 * Asks the players if want to save the game. If so, asks for a file name. Verifies that the file does not already exists. 
 * If it does, displays a warning and ask for cancellation. If not, it saves the game in the file specified and return YES if the file has been saved without errors. */
int ask_save_game(Game* game);


/** \brief This function allows to ask users if they want to play the game again
 * \return YES if the answer is yes, NO otherwise
 * 
 * While users don't answer with a 'y' or a 'n', the function asks again. Returns the answer with YES or NO. */
int ask_new_game();


/** \brief This function allows to ask users from what file they want to load the game
 * \return A string containing file name where the game needs to be loaded, NULL if the file doesn't exist or is not reachable
 * 
 * Asks for the name of the file, tests whether the file exists and tests if it can be opened in reading mode. Returns the name of the file. */
char* ask_load_game();


/** \brief This function displays a brief usage of the program
 * 
 * The usage contains :
 * 		- N or NE : Begins a new game
 * 		- H or HELP : Displays the help */
void display_usage();


/** \brief This function displays the help of the Othello program
 * 
 * The help contains the following options :
 * 		- N or NEW : Begins a new game
 * 		- L or LOAD : Loads a game from a text file
 * 		- S or SAVE : Saves the game in progress in a text file
 * 		- H or HELP : Displays the help
 * 		- C or CANCEL : Cancel the last move played
 * 		- U or UNCANCEL : Uncancel the last canceled move
 * 		- Q or QUIT : Exits the game */
void display_help();

/** \brief This function displays the title of the program */
void display_title();

#endif
