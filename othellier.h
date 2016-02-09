/** \file othellier.h
 * The header file of the othellier.c file. Here you cand find the protoypes of all functions of this file
 * */

#ifndef __OTHELLIER_H__
#define __OTHELLIER_H__

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "structures.h"


/** \brief This function initializes the main structure of the game board, so that one can begin a new game
 * \return A pointer to the game board Othellier structure, initialized
 * 
 * Allocates the game board and sets each square of the board to EMPTY, except the border, which are initialized to BORDER. Then the square 45 and 54 are transformed to BLACK, 
 * and the square 44 and 55 and transformed to WHITE. The pawn number of each player is set to 2, and the game board is returned. */
Othellier* init_othellier();


/** \brief This function determines whether the move passed in argument is a legal move on the game board passed in argument too
 * @param oth: a pointer to the game board
 * @param mov : a pointer to a Move action
 * \return YES if the move is legal, NO otherwise
 * 
 * The function tests if the move is legal by testing the value of the squarre on the game board. If the squarre is not empty, the move cannot be legal. Then, it tests for each cell
 *  of the flip array if there is any legal alignment */
int is_legal(Othellier* oth, Move* mov);


/** \brief This function updates the status of each cell of the flip array for a move. If there is an alignment, the cell is set to 1, 0 otherwise
 * @param oth : a pointer to the game board Othellier structure
 * @param mov : a ponter to a Move structure action
 * \return 1 if the array has been updated, 0 if the position of the move is a border (so the array has not been updated)
 * 
 * Tests whether the square designed by the position of the move is a border. If so, returns 0, if not, for each direction, tests if there may be an alignment. 
 * Calls the appropriate function for each direction (has_alignment), and sets the corresponding cell of the array to the return valu of the function called. 
 * The function determines the validity of the alignment, or not. */
int update_flip(Othellier* oth, Move* mov);


/** \brief This function tests the validity and the existence of an alignment in the given direction (see direction Macros)
 * @param oth : a pointer to the game board Othellier structure
 * @param pos : the position where the function needs to check for an alignment
 * @param color : the color that the function needs to find at the end of the alignment to validate it
 * @param direction : the direction of the alignment
 * \return 1 if there is a valid alignment, 0 otherwise
 * 
 * While the squarre in the given direction is the opponent's color, tests the next position in the same direction. If it's the needed color, returns 1, continues the loop otherwise, until 
 * the position has another value than the opponent's color. */
short has_alignment(Othellier* oth, short pos, short color, short direction);


/** \brief This function copies the current game board state into the game board array (for saving)
 * @param game : a pointer to the game structure
 * 
 * Allocates a bigger space to add the new board. Copies material, turn and each squarre of the board. Increments the game board cursor. */
void game_board_copy(Game* game);


/** \brief This function frees the boards array from a cursor to another. It is used especially for freeing the end of the array, when a new move is played (after a cancellation).
 * @param game : pointer to the Game structure 
 * \return 1 if at least 1 cell of the array has been freed, 0 otherwise
 * 
 * Tests if the cursors are equal or not. If not so, frees all cells of the array from the end to the cursor of the game.
 * Reallocates a memory place for the new array (which is smaller). */
int destroy_end_boards_tab(Game* game);


/** \brief This function updates the status of the game board, and shows for each empty square if it is a legal move for the user who has the turn, or not.
 * @param game : a pointer to the Game structure
 * \return The number of legal squares in the new board
 * 
 * Allocates memory for a move. Sets all the previous LEGAL squares to EMPTY. Then, for each square, if it is empty, it sets the move on the position of the square and 
 * tests if the move is legal. If so, it puts the square to LEGAL and increments the counter. Then it seallocates the move and returns the counter. */
int update_othellier(Game* game);

#endif
