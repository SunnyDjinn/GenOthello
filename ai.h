/** \file ai.h
 * The header file of the .c file ai.c. Here you can find the protoypes of all functions of this file
 * */

#ifndef __AI_H__
#define __AI_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "constants.h"
#include "graphics.h"
#include "move.h"
#include "othellier.h"
#include "structures.h"
#include "user.h"


/** \brief This function counts the number of corner occupied by the player having the "color" color
 * @param oth : a pointer to an Othellier structure
 * @param color : the color of the player we want to find the number of corners
 * \return the number of corners occupied
 * 
 * Tests, for each corner, if it is occupied by a pawn of the color "color". Increments the counter if so and returns the counter.  */
short number_of_corners(Othellier* oth, short color);



/** \brief This function finds all of the legal moves of the player who has the turn, and stores them in the array 'tab[]'
 * @param game : a pointer to Game structure
 * @param tab : the array in which we want to store the legal moves
 * \return the number of legal moves (the length of the array)
 * 
 * Updates the game board and tells, for each squarre, if the move is legal or not. If so, stores the position of the squarre in the array.  */
short find_legal_moves(Game* game, short tab[]);



/** \brief This function returns a value as important as the alignment is long
 * @param oth : a pointer to an Othellier structure
 * @param color : the color we want to examinate
 * @param position : the position from which we want to find the alignment
 * @param direction : the direction of the alignment
 * @param weight : the weight of each position of the alignment
 * \return the weight of the alignment 
 * 
 * Gives a weight for the alignment considered. The longer the aligment is, the higher the weight is. */
short evaluate_long_alignments(Othellier* oth, short color, short position, short direction, short weight);



/** \brief This function returns a value depending on the squarre pattern size found from the corner passed in argument 
 * @param oth : a pointer to an Othellier structure
 * @param color : the color of the player who mays have the pattern 
 * @param position : the position of the corner we want to analyze 
 * @param strength : the strength to apply for a size 1 pattern 
 * 
 * Gives a weight for the pattern considered. The bigger the pattern, the higher the weight.*/
short evaluate_corner_square_pattern(Othellier* oth, short color, short position, short strength);



/** \brief This function makes a sober evaluation of the game board for the color 'color'
 * @param game : a pointer to the Game structure
 * @param color : the color we want to examinate
 * \return an evaluation of the board
 * 
 * Gives arbitrary values for most importants squarres of the board, as corners and borders. */
short positions_strength(Game* game, short color);



/** \brief This function makes a more exhaustive evaluation of the win possibilities of a player
 * @param game : a pointer to the Game structure
 * @param color : the color we want to examinate
 * @param coefs : a coefficients array 
 * \return an evaluation of the game state
 * 
 * Applies coefficients on 4 differents types of data : material, positions, mobility and the squarre pattern. Calls positions_strength() for an evaluation of the positions of the pawns. */
short evaluation_function(Game* game, short color, float coefs[]);



/** \brief This function applies the minimax algorithm on the game, using alpha-beta pruning
 * @param maximize : says if the algorithm must be in maximize position or in minimize
 * @param game : a pointer to the Game structure
 * @param playerAi : the color of the player who first called minimax (the AI player)
 * @param depth : the depth the algorithm has to scour
 * @param height : the depth min-max will scour, but height won't change during the algorithm. Used to verify if the current depth is the higher one
 * @param alpha : the value alpha for alpha-beta pruning
 * @param beta : the value beta for alpha-beta pruning
 * @param coefs : the coefficients to use in the evaluation function
 * \return the evaluation if the algorithm is ot finished, the best position to play otherwise
 * 
 * Applies the famous minimax algorithm on the Othello game. Takes into cosideration the player who is the 'AI' and the fact that the turn may not be always to the opponent after a move is played. 
 * Alpha-Beta pruning has been implemented too. */
short min_max(short maximize, Game* game, short playerAi, short depth, short height, short alpha, short beta, float coefs[]);


#endif

