/** \file ai.c
 * The ai.c file in which you can find all algorithms for the developement of the Artificial Intelligence of the game
 * */

#include "ai.h"


short number_of_corners(Othellier* oth, short color) {
	short number = 0;
	/* Testing the top left corner */
	if(oth->array[TL_CORNER] == color)
		number++;
		
	/* Testing the top right corner */
	if(oth->array[TR_CORNER] == color)
		number++;
		
	/* Testing the bottom left corner */
	if(oth->array[BL_CORNER] == color)
		number++;
		
	/* Testing the bottom right corner */
	if(oth->array[BR_CORNER] == color)
		number++;
	
	/* Returning the number of corners occupied */
	return number;
}


short find_legal_moves(Game* game, short tab[]) {
	int i;
	short counter = 0;
	
	/* Updating the game board */
	update_othellier(game);
	
	/* For each square of the board, incrementing the counter if the square represents a legal move */
	for(i=0; i<MAX_CASE; i++)
		if(game->oth->array[i] == LEGAL) {
			/* Saving the legal moves in the array */
			tab[counter++] = i;
		}
	
	return counter;
}


 
short evaluate_long_alignments(Othellier* oth, short color, short position, short direction, short weight) {
	
	short j = position+1;
	short strength = 0;
	
	/* While the next squarre in the direction belongs to the player 'color' */
	while(oth->array[j+direction] == color && oth->array[j+direction] != BORDER) {
		strength += weight;
		j+=direction;
	}
	return strength;
}


short evaluate_corner_square_pattern(Othellier* oth, short color, short position, short strength) {
		
	short patternFound = 1;
	short i, patternSize = 0;
	
	/* If the position is a corner */
	switch(position) {
		/* Depending on the corner */
		case TL_CORNER:
			/* While there the wanted pattern */
			while(patternFound == 1) {
				/* For each squarre of the bottom line of the pattern */
				for(i = position; oth->array[i] != BORDER; i -= L_DIR) {
					/* If the pattern isn't existant anymore */
					if(oth->array[i] != color) {
						/* Pattern not found */
						patternFound = 0;
						break;
					}
				}
				
				/* For each square of the right line of the pattern */
				for(i = position; oth->array[i] != BORDER; i -= TC_DIR) {
					/* If the pattern isn't existant anymore */
					if(oth->array[i] != color) {
						/* Pattern not found */
						patternFound = 0;
						break;
					}
				}
				position += BRD_DIR;
				patternSize++;	
			}
			
		break;
		
		/* Same as above */
		case TR_CORNER:
			while(patternFound == 1) {
				for(i = position; oth->array[i] != BORDER; i -= R_DIR) {
					if(oth->array[i] != color) {
						patternFound = 0;
						break;
					}
				}
				
				for(i = position; oth->array[i] != BORDER; i -= TC_DIR) {
					if(oth->array[i] != color) {
						patternFound = 0;
						break;
					}
				}
				position += BLD_DIR;
				patternSize++;	
			}
			
		break;
		
		/* Same as above */
		case BL_CORNER:
			while(patternFound == 1) {
				for(i = position; oth->array[i] != BORDER; i -= L_DIR) {
					if(oth->array[i] != color) {
						patternFound = 0;
						break;
					}
				}
				
				for(i = position; oth->array[i] != BORDER; i -= BC_DIR) {
					if(oth->array[i] != color) {
						patternFound = 0;
						break;
					}
				}
				position += TRD_DIR;
				patternSize++;	
			}
			
		break;
		
		/* Same as above */
		case BR_CORNER:
			while(patternFound == 1) {
				for(i = position; oth->array[i] != BORDER; i -= R_DIR) {
					if(oth->array[i] != color) {
						patternFound = 0;
						break;
					}
				}
				
				for(i = position; oth->array[i] != BORDER; i -= BC_DIR) {
					if(oth->array[i] != color) {
						patternFound = 0;
						break;
					}
				}
				position += TLD_DIR;
				patternSize++;	
			}
			
		break;
	}
	
	/* Returning the strength of the pattern */
	return strength * (patternSize-1);
}


short positions_strength(Game* game, short color) {
	
	short i;
	short strength = 0;
	short strengthArray[100] = {	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
									0, 500, -250, 30, 10, 10, 30, -250, 500, 0, 
									0, -250, -350, 0, 0, 0, 0, -350 -250, 0, 
									0, 30, 0, 1, 2, 2, 1, 0, 30, 0, 
									0, 10, 0, 2, 16, 16, 2, 0, 10, 0, 
									0, 10, 0, 2, 16, 16, 2, 0, 10, 0, 
									0, 30, 0, 1, 2, 2, 1, 0, 30, 0, 
									0, -250, -350, 0, 0, 0, 0, -350 -250, 0, 
									0, 500, -250, 30, 10, 10, 30, -250, 500, 0, 
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	
	/* For each square of the board, giving different evaluations */
	for(i=0; i<MAX_CASE; i++) {
		
		/* If the square is occupied by a 'color' pawn */
		if(game->oth->array[i] == color) {
			
			strength += strengthArray[i];
			
			switch(i) {
				
				/* Top left corner (A1)*/
				case TL_CORNER:
					
					/* If the square on the right of the corner is occupied by the IA as well as the corner, compensating the previous loss */
					if(game->oth->array[TL_CORNER+R_DIR] == color)
						strength +=250;
						
					/* Evaluating the top border line from left to right */
					strength += evaluate_long_alignments(game->oth, color, i, R_DIR, 150);
					
					/* If the square under the corner is occupied by the IA as well as the corner, compensating the previous loss */
					if(game->oth->array[TL_CORNER+BC_DIR] == color)
						strength +=250;
						
					/* Evaluating the left border line from top to bottom */
					strength += evaluate_long_alignments(game->oth, color, i, BC_DIR, 150);
					
					/* If the bottom right diagonal square is occupied by the IA as well as the corner, compensating the previous loss */
					if(game->oth->array[TL_CORNER+BRD_DIR] == color)
						strength +=350;
						
					/* Evaluating the bottom right diagonal from top to bottom */
					strength += evaluate_long_alignments(game->oth, color, i, BRD_DIR, 250);
					
				break;
				
				/* Top right corner (H1) */
				case TR_CORNER:
					if(game->oth->array[TR_CORNER+L_DIR] == color)
						strength +=250;
						
					strength += evaluate_long_alignments(game->oth, color, i, L_DIR, 150);
					
					if(game->oth->array[TR_CORNER+BC_DIR] == color)
						strength +=250;
						
					strength += evaluate_long_alignments(game->oth, color, i, BC_DIR, 150);
					
					if(game->oth->array[TR_CORNER+BLD_DIR] == color)
						strength +=350;
						
					strength += evaluate_long_alignments(game->oth, color, i, BLD_DIR, 250);
				break;
				
				/* Bottom left corner (A8) */
				case BL_CORNER:
					if(game->oth->array[BL_CORNER+TC_DIR] == color)
						strength +=250;
						
					strength += evaluate_long_alignments(game->oth, color, i, TC_DIR, 150);
					
					if(game->oth->array[BL_CORNER+R_DIR] == color)
						strength +=250;
						
					strength += evaluate_long_alignments(game->oth, color, i, R_DIR, 150);
					
					if(game->oth->array[BL_CORNER+TLD_DIR] == color)
						strength +=350;
						
					strength += evaluate_long_alignments(game->oth, color, i, TLD_DIR, 250);
				break;
				
				/* Bottom right corner (H8) */
				case BR_CORNER:
					if(game->oth->array[BR_CORNER+L_DIR] == color)
						strength +=250;
						
					strength += evaluate_long_alignments(game->oth, color, i, L_DIR, 150);
					
					if(game->oth->array[BR_CORNER+TC_DIR] == color)
						strength +=250;
						
					strength += evaluate_long_alignments(game->oth, color, i, TC_DIR, 150);
					
					if(game->oth->array[BR_CORNER+TLD_DIR] == color)
						strength +=350;
						
					strength += evaluate_long_alignments(game->oth, color, i, TLD_DIR, 250);
				break;
				
				default:
				break;
			}
		}
				
	}
	return strength;
}


short evaluation_function(Game* game, short color, float coefs[]) {
	
	/* Loading the coefficients */
	float matCoef = coefs[0];
	float mobCoef = coefs[1];
	float strengthCoef = coefs[2];
	float patternCoef = coefs[3];
	
	/* Saving the game turn */
	short turn = game->turn;
	
	float evaluation = 0.0;
	
	/* Material */
	evaluation += matCoef * (game->oth->piecesNb[color]-game->oth->piecesNb[(color+1)%2]);
	
	/* Mobility */
	/* Changing the turn to opponent */
	game->turn = (turn+1)%2;
	
	if(game->turn == color) {
		evaluation += mobCoef * update_othellier(game);
		/* Resetting the right turn */
		game->turn = turn;
		evaluation -= mobCoef * update_othellier(game);
	}
	else {
		evaluation -= mobCoef * update_othellier(game);
		/* Resetting the right turn */
		game->turn = turn;
		evaluation += mobCoef * update_othellier(game);
	}
	
	/* Strength of positions for the player */
	evaluation += strengthCoef * positions_strength(game, color);
	
	/* Strength of positions for the opponent */
	evaluation -= strengthCoef * positions_strength(game, (color+1)%2);
	
	/* Strength of square patterns from corners for each player */
	/* The black one */
	evaluation += patternCoef * evaluate_corner_square_pattern(game->oth, color, TL_CORNER, 200);
	evaluation += patternCoef * evaluate_corner_square_pattern(game->oth, color, TR_CORNER, 200);
	evaluation += patternCoef * evaluate_corner_square_pattern(game->oth, color, BL_CORNER, 200);
	evaluation += patternCoef * evaluate_corner_square_pattern(game->oth, color, BR_CORNER, 200);
	/* The white one */
	evaluation -= patternCoef * evaluate_corner_square_pattern(game->oth, (color+1)%2, TL_CORNER, 200);
	evaluation -= patternCoef * evaluate_corner_square_pattern(game->oth, (color+1)%2, TR_CORNER, 200);
	evaluation -= patternCoef * evaluate_corner_square_pattern(game->oth, (color+1)%2, BL_CORNER, 200);
	evaluation -= patternCoef * evaluate_corner_square_pattern(game->oth, (color+1)%2, BR_CORNER, 200);
	
	return (short)evaluation;
}



short min_max(short maximize, Game* game, short playerAi, short depth, short height, short alpha, short beta, float coefs[]) {
	
	short opponent = (game->turn == BLACK?WHITE:BLACK);
	
	/* If the end of game is reached or the depth is zero, returning an evaluation for the leaves */
	if(end_of_game(game) || depth < 1) {

		  return evaluation_function(game, playerAi, coefs);
	}
	
	short evalMax;
	short position;
	
	short evaluation;
	
	/* Finding the legal moves to play in advance */
	short tabLegal[MAX_CASE];
	short tabLength = find_legal_moves(game, tabLegal);
	
	int i;
	
	/* Maximizing */
	if(maximize == YES) {
		evalMax = SHRT_MIN;
		
		/* Processing, for each possible move */
		for(i=0; i<tabLength; i++) {
			/* Playing the move and updating the turn */
			move_processing(game, UNKNOWN, tabLegal[i]);
			
			
			/* If the turn passes to the opponent, calling for minimizing */
			if(game->turn == opponent)
				evaluation = min_max(NO, game, playerAi, depth-1, depth, alpha, beta, coefs);
			
			/* If the turn stays the same (the opponent cannot play), calling for maximizing */
			else
				evaluation = min_max(YES, game, playerAi, depth-1, depth, alpha, beta, coefs);
			
			/* Cancelling the move played */
			cancel_last_move(game);
			
			/* Maximizing the value */
			if(evaluation > evalMax) {
				evalMax = evaluation;
				position = tabLegal[i];
			}
			
			if(evalMax >= alpha) {
				alpha = evalMax;
				/* Beta cut-off */
				if(beta <= alpha)
					break;
			}
				
		}

	}
	
	/* Minimizing */
	else {  
		evalMax = SHRT_MAX;
		
		/* Processing, for each possible move */
		for(i=0; i<tabLength; i++) {
			/* Playing the move and updating the turn */
			move_processing(game, UNKNOWN, tabLegal[i]);
			
			/* If the turn passes to the opponent, calling for maximizing */
			if(game->turn == opponent)
				evaluation = min_max(YES, game, playerAi, depth-1, depth, alpha, beta, coefs);
			/* If the turn stays the same (the opponent cannot play), calling for minimizing */
			else
				evaluation = min_max(NO, game, playerAi, depth-1, depth, alpha, beta, coefs);
			
			/* Cancelling the move played */
			cancel_last_move(game);
			
			/* Minimizing the value */
			if(evaluation < evalMax) {
				evalMax = evaluation;
				position = tabLegal[i];
			}
			
			if(evalMax <= beta) {
				beta = evalMax;
				/* alpha cut_off */
				if(beta <= alpha)
					break;
			}
			
		}
	}
	
	/* Returning the move to play if the depth is the higher one */
	if(depth == height)
		return position;
		
	/* Returning the evaluation otherwise */
	return evalMax;
}

