/** \file game.h
 * The header file of the game.c file. Here you cand find the protoypes of all functions of this file
 * */

#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>

#include "ai.h"
#include "graphics.h"
#include "othellier.h"
#include "structures.h"
#include "user.h"


/** \brief This function initializes the Game structure
 * \return game : the initialized pointer to the Game structure
 * 
 * Allocates the game, initializes all the values needed for the game such as the players' names, their types, levels, 
 * the cursors ans put the first turn to BLACK. Makes a call to the function init_othellier() to initialize the Othellier structure */
Game* init_game();


/** \brief This functions loads and/or initializes the coefficients for the evaluation function 
 * @param coefs : the coefficients array
 * 
 * Tests if the file containing the coefficients exists. If so, loads them from it. Otherwise, initializes them to 1. */
void load_coefs(float coefs[]);


/** \brief This function allows to update the field showing the player who has the turn
 * @param game : pointer to the Game structure 
 * 
 * Makes a simple call to the function whose_turn_is_it() to determine the player who has the turn.
 * It changes the field turn in the Game structure */
void update_turn(Game* game);


/** \brief This function determines which player has the turn
 * @param game : a pointer to the Game structure
 * @param color : the color of the player who has just played
 * \return The color of the player who has the turn, END_OF_GAME otherwise
 * 
 * Tests if the supposed next player still has possible moves on the board. If so, he is the next player. If not, tests whither the ohter player still has possible moves. 
 * If so, he is the next player, if not, the game is over. */
short whose_turn_is_it(Game* game, int color);


/** \brief This function destroy the Game structure
 * 
 * Frees the played moves memory, the board (Othellier structure) and finally the Game structure */
void destroy_game(Game* game);


/** \brief This function determines if the player passed in argument is still able to play on the board
 * @param game : pointer to the Game structure 
 * @param color : the color of the player
 * \return YES if the player still has possible moves, NO otherwise
 * 
 * After changing the turn to the color of the player, updates the state of the board, and for each square, tests if the move is legal
 * If so, changes again the turn and return YES, return NO otherwise. */
short has_legal_move(Game* game, int color);


/** \brief This function frees the moves array from a cursor to another. It is used especially for freeing the end of the array, when a new move is played (after a cancellation).
 * @param game : pointer to the Game structure 
 * \return 1 if at least 1 cell of the array has been freed, 0 otherwise
 * 
 * Tests if the cursors are equal or not. If not so, frees all cells of the array from the end to the cursor of the game.
 * Reallocates a memory place for the new array (which is smaller). */
short destroy_end_moves_tab(Game* game);


/** \brief This function determines whether the game is over or not
 * @param game : a pointer to the Game structure
 * \return YES if so, NO otherwise
 * 
 * Tests if the at least one player has no remaining pawn on the board. If so, the game is over. If not, tests if at least one player still have remaining possible moves. 
 * If not, the game is over, otherwise it is not.*/
short end_of_game(Game* game);


/** \brief This function tells if the game in progress is a computer game or not
 * @param game : pointer to the Game structure
 * \return YES for a positive answer, NO otherwise
 *
 * Tests if one of the two players is the computer */
short is_computer_game(Game* game);


/** \brief This function chooses the action to realize when the game reaches its end.
 * @param game : pointer to the Game structure 
 * \return game : the new initialized pointer to the Game structure or the game pointer freed (NULL).
 * 
 * Tests whether the game has indeed reached its end. Then informs the players who has won ans asks them for the saving of the game.
 * Asks for a new game, and returns the pointer to the new game initialized, returns NULL otherwise. */
Game* end_of_game_action(Game* game);


/** \brief  This function allows the AI to play a turn, if it has to
 * @param game : a pointer to the Game structure
 * \return the game structre, as it may very well be deallocated in this function (if the game reaches its end)
 * 
 * Tests if the turn is really to the computer (AI). Then, calls the min_max() function to find the best move to play. Tests whether or not its the end of the game, and returns the game structure or perform 
 * an action of end of game if so. */
Game* play_ai(Game* game);

#endif
