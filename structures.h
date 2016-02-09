/** \file structures.h
 * A file in which one can find all the data structures used in the project
 * */

#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

/** short : Short type has been prefered as int type due to memory use. The unsigned short type takes the same amount of memory as the short type. */

/** \brief Othellier (game board) structure*/
typedef struct {
	/** Array for the game board */
	short array[MAX_CASE];
	/** Array for the storage of the number of pawn for each player */
	short piecesNb[PLAYER_NB];
	/** Number of the player who has the turn */
	short turn;
} Othellier;


/** \brief Player structure*/
typedef struct {
	/** String for the storage of the name of one player */
	char player_name[MAX_NAME];
	/** Type of the player (human/computer) */
	short player_type;
} Player;


/** \brief Move structure */
typedef struct {
	/** Positionf of the move on the game board (array) */
	short position;
	/** Color of the player who makes the move */
	short color;
	/** Array for the existence of flip if the move is played */
	short flip[MAX_FLIP];
} Move;

/** \brief Game structure */
typedef struct {
	/** Number of the move */
	short cursor;
	/** Cursor for the last cell of the moves array */
	short movesCursor;
	/** Cursor for the last cell of the boards array */
	short boardsCursor;
	/** Number of the player who has to play */
	short turn;
	/** Is the game saved ? 1 for yes, 0 for no */
	short saved;
	/** Player 1 */
	Player p1;
	/** Player 2 */
	Player p2;
	/** Moves array (for saving) */
	Move** moves;
	/** Game boards array (for saving) */
	Othellier** oths;
	/** Othellier (game board) */
	Othellier* oth;
	/** Coefficients used by the evaluation function */
	float coefs[COEF_NB];
} Game;


/** \brief Genome structure */
typedef struct {
	/** Coefficients array */
	float coefs[COEF_NB];
	/** Fitness of the genome */
	short fitness;
} Genome;


/** \brief Population structure */
typedef struct {
	/** Genomes array */
	Genome* genomes;
	/** Number of genomes in the population */
	short genNb;
} Population;



#endif

