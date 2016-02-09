/** \file move.h
 * The header file of the move.c file. Here you cand find the protoypes of all functions of this file
 * */
 
#ifndef __MOVE_H__
#define __MOVE_H__

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "io.h"
#include "othellier.h"
#include "structures.h"


/** \brief This function creates a new Move using the parameters
 * @param oth: a pointer to the game board (Othellier structure)
 * @param position : the position of the move to initialize
 * @param color : the color of the move to initialize
 * \return a pointer to the created move
 * 
 * The function allocates a new Move structure and fills it with the parameters in argument. Fills the flip array calling update_flip(), and returns the pointer. */
Move* create_move(Othellier* oth, short position, short color);


/** \brief This function makes a move action on the game board
 * @param game : a pointer to the Game structure
 * @param mov : à pointer to a Move action
 * \return The number of fliped pawns on the game board
 * 
 * The function begins with adding a pawn on the desired position on the game board. Then, it increases the pawn number of the current player. Plus, for each direction, if there is 
 * a flip, it returns the pawns that have the opposite color and increases the pawn number too.  */
int play_move(Game* game, Move* mov);

/** \brief This function tests if the coordinates of a move are legal, and plays the move corresponding if so
 * @param game : pointer to the Game structure 
 * @param coordinates : string containing 2 characters : the first one must be the letter of the column and the second must be the number 
 * of the row where the player wants to play
 * @param intCoord : the coordinates passed as an integer. If intCoord is UNDEFINED, the function uses the string coordinates. Otherwise, it uses the integer
 * \return 1 if the move as been played, BAD_COORDINATES if the coordinates don't have the right format, and NOT_LEGAL if the move is not legal
 * 
 * Tests if the coordinates are passed as a string or as an integer and uses the right format. Tests if the coordinates have the proper format, allocates and initializes 
 * a move, tests if this move with the position is legal, frees the end of the moves array to prohibit the cancellation of old canceled moves, plays the move, 
 * reallocates the moves array and update the game status (game board and game turn). */
int move_processing(Game* game, const char* coordinates, short intCoord);


/** \brief This function cancel the last move played on the game board. If a move has already been canceled and there is still moves that can be canceled, the function does it as well.
 * @param game : a pointer to the Game structure
 * \return 1 if the last move has been canceled, 0 if there was no move to cancel
 * 
 *  Tests whether there is still moves that can be canceled. If so, decrements the game cursor and recalculates the board from the beginning with all moves in the moves array, 
 * except the canceled ones*/
int cancel_last_move(Game* game);


/** \brief This function uncancel the last move canceled on the game board. If a move has already been uncanceled and there is still moves that can be uncanceled, the function does it as well.
 * @param game : a pointer to the Game structure
 * \return 1 if the last move has been uncanceled, 0 if there was no move to uncancel
 * 
 *  Tests whether there is still moves that can be uncanceled. If so, increments the game cursor and plays the last move canceled */
int uncancel_move(Game* game);

#endif
