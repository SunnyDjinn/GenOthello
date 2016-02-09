/** \file move.c
 * Functions related to the processing of a move during the game
 * */

#include "move.h"


Move* create_move(Othellier* oth, short position, short color) {
	
	/* Allocating the move */
	Move* mov = malloc(sizeof(Move));
	
	if(!mov) {
		perror("Move : Memory Allocation Failure\n");
		exit(EXIT_FAILURE);
	}
	
	/* Setting its parameters */
	mov->position = position;
	mov->color = color;
	update_flip(oth, mov);
	
	return mov;
}


int play_move(Game* game, Move* mov) {
	
	/* Here, the move must be legal (verified in the move_processing function) */ 
	int i, n = 0, shift, color = (mov->color==BLACK?WHITE:BLACK), counter = 0;
	
	/* Putting the pawn on the square required by the move, incrementing the pieces number of the player who makes the move */
	game->oth->array[mov->position] = mov->color;
	game->oth->piecesNb[mov->color]++;
	counter ++;
	
	/* Updating the flip array / at least one cell of the array is true (because the move is legal) */
	update_flip(game->oth, mov);
	
	/* For each cell, so for each direction */
	for(i=0; i<MAX_FLIP; i++) {
				
		/* If a flip exixts in this direction */
		if(mov->flip[i] == 1) {
			/* Updating the n variable (describing the direction of the alignment) */
			
			switch(i) {
				case 0: n = -11;
				break;
				case 1: n= -10;
				break;
				case 2: n= -9;
				break;
				case 3: n= -1;
				break;
				case 4: n= +1;
				break;
				case 5: n= +9;
				break;
				case 6: n= +10;
				break;
				case 7: n= +11;
				break;
				default: 
				break;
			}
			
			shift = n;
			
			/* While the square is the opposite color of the player who makes the move */
			while(game->oth->array[mov->position + shift] == color){
				
				/* Changing the square color in the alignement */
				game->oth->array[mov->position + shift] = mov->color;
				counter ++;
				
				/* Updating each player pieces number */
				game->oth->piecesNb[mov->color]++;
				game->oth->piecesNb[color]--;
				
				/* Continuing in the same direction */
				shift+=n;
			}
		}
	}
	
	/* Returning the number of pawn changed + the new pawn on the board */
	return counter;
}


int move_processing(Game* game, const char* coordinates, short intCoord) {
	
	short pos;
	
	/* If the coordinates in argument are passed as an integer (used for a vs. computer game), saving the position in a local variable for a later use */
	if(intCoord != UNDEFINED) {
		pos = intCoord;
	}
	
	/* Else, the coordinates are passed as a string */
	else {
		
		/* If the coordinates have not the right format, there is no move to play */
		if(!are_good_coordinates(coordinates))
			return BAD_COORDINATES;
		pos = char2int(coordinates);
	}
	
	/* Initializing a move with the position (transformed in integer or passed as an integer) and the color */

	Move* mov = create_move(game->oth, pos, game->turn);
	
	/* Updating the legal moves of the game board */
	update_othellier(game);
	
	/* If the move is not a legal move, there is no move to play */
	if(!is_legal(game->oth, mov)) {
		free(mov);
		return NOT_LEGAL;
	}
	
	/* If a player makes a move after having canceled some moves, suppresses canceled moves from the moves arrays */
	destroy_end_moves_tab(game);
	destroy_end_boards_tab(game);
	
	/* Playing the move */
	play_move(game, mov);
	
	/* Allocating a bigger memory space for the moves array and stocking the move played at the end of the array */
	game->moves = realloc(game->moves, (game->cursor+1) * sizeof(Move*));
	game->moves[game->cursor++] = mov;

	game->movesCursor++;
	
	/* Now, the game is not saved (because a move has been played) */
	game->saved = NO;
	
	/* Updating the turn for the next person to play and the game board for the current legal moves */
	update_turn(game);
	update_othellier(game);
	
	/* Copying the new game board in the storage emplacement */
	game_board_copy(game);
	
	return 1;
}


int cancel_last_move(Game* game) {
	/* If the game cursor is zero, there is no move to cancel */
	if(game->cursor == 0)
		return 0;
		
	short i;
	
	/* Decrementing the cursor and restoring the previous board */
	game->cursor--;
	
	/* Copying the previous board in the current board */
	
	/* Copying the material of each player */
	
	game->oth->piecesNb[BLACK] = game->oths[game->cursor]->piecesNb[BLACK];
	game->oth->piecesNb[WHITE] = game->oths[game->cursor]->piecesNb[WHITE];
	
	/* For each squarre, copying the state in the storage emplacement */
	for(i=0; i<MAX_CASE; i++) {
		game->oth->array[i] = game->oths[game->cursor]->array[i];
	}
	
	game->turn = game->oths[game->cursor]->turn;
	return 1;
}

int uncancel_move(Game* game) {
	
	/* If the game cursor and the end array cursor are the same, the game is already at the end of the boards array, there is no move to uncancel */
	if(game->cursor+1 == game->boardsCursor)
		return 0;
	
	short i;
	
	/* Otherwise, there is at least one move to uncancel, re-establishing the next board */
	game->cursor++;
	
	game->oth->piecesNb[BLACK] = game->oths[game->cursor]->piecesNb[BLACK];
	game->oth->piecesNb[WHITE] = game->oths[game->cursor]->piecesNb[WHITE];
	
	/* For each squarre, copying the state in the storage emplacement */
	for(i=0; i<MAX_CASE; i++) {
		game->oth->array[i] = game->oths[game->cursor]->array[i];
	}
	
	/* Updating the turn */
	game->turn = game->oths[game->cursor]->turn;
	
	return 1;
}
