/** \file othellier.c
 * Functions related to the game board, such as alignements and flips
 * */

#include "othellier.h"


/** \brief Initialisation de l'Othellier */
Othellier* init_othellier() {
	
	/* Memory allocation of the game board, exiting if an error occurs */
	Othellier *oth = malloc(sizeof(Othellier));
	if(!oth) {
		perror("Othellier : Memory Allocation Failure\n");
		exit(EXIT_FAILURE);
	}
	
	int i;
	
	/* For each sqare of the board */
	for (i=0; i<MAX_CASE; i++) {
		
		/* If the square is a border, filling it with border */
		if ((i<MAX_DIM) || (i%MAX_DIM == 0) || ((i+1)%MAX_DIM == 0) || (i>89))
			oth->array[i] = BORDER;
		/* Else, it is not a border, filling it with empty */
		else 
			oth->array[i] = EMPTY;
	}
	
	/* Then, initializing the main structure : 4 pawns in a square shape, 2 white and 2 black */
	oth->array[45] = oth->array[54] = BLACK;
	oth->array[44] = oth->array[55] = WHITE;
	
	/* Initializing the pieces number for each player */
	oth->piecesNb[BLACK] = 2;
	oth->piecesNb[WHITE] = 2;
	
	/* Setting the turn (but useless for the game board / usefull for the previous stored boards) */
	oth->turn = BLACK;
	
	/* Returning the game board */
	return oth;
}

int is_legal(Othellier* oth, Move* mov) {
	int i;
	
	/* If the square of the game board is already occupied, the move cannot be legal */
	if(oth->array[mov->position] == BLACK || oth->array[mov->position] == WHITE || oth->array[mov->position] == BORDER) {
		return NO;
	}
	
	/* Updating the flip array of the move */
	update_flip(oth, mov);
	
	/* For each cell of this array, if one is true, there is a possible flip, so the move is legal */
	for(i=0; i<MAX_FLIP; i++) {
		if(mov->flip[i] == 1)
			return YES;
	}
	
	return NO;
}

int update_flip(Othellier* oth, Move* mov) {
	
	short opponent = (mov->color == BLACK?WHITE:BLACK);
	
	/* If the square is a border, no flip are possible */
	if(oth->array[mov->position] == BORDER || oth->array[mov->position] == opponent)
		return 0;
	
	/* If the diagonal top left square is the opposite color, there may be a flip */
	if(oth->array[mov->position-11] == opponent)
		mov->flip[0] = has_alignment(oth, mov->position+TLD_DIR, mov->color, TLD_DIR);
	/* Otherwise, the square is the same color, is a border or is empty, no flip possible */
	else
		mov->flip[0] = 0;
	
	/* If the diagonal middle top square is the opposite color, there may be a flip */
	if(oth->array[mov->position-10] == opponent)
		mov->flip[1] = has_alignment(oth, mov->position+TC_DIR, mov->color, TC_DIR);
	/* Otherwise, the square is the same color, is a border or is empty, no flip possible */
	else
		mov->flip[1] = 0;
		
	/* If the diagonal top right square is the opposite color, there may be a flip */
	if(oth->array[mov->position-9] == opponent)
		mov->flip[2] = has_alignment(oth, mov->position+TRD_DIR, mov->color, TRD_DIR);
	/* Otherwise, the square is the same color, is a border or is empty, no flip possible */
	else
		mov->flip[2] = 0;
		
	/* If the left square is the opposite color, there may be a flip */
	if(oth->array[mov->position-1] == opponent)
		mov->flip[3] = has_alignment(oth, mov->position+L_DIR, mov->color, L_DIR);
	/* Otherwise, the square is the same color, is a border or is empty, no flip possible */
	else
		mov->flip[3] = 0;
		
	/* If the right square is the opposite color, there may be a flip */
	if(oth->array[mov->position+1] == opponent)
		mov->flip[4] = has_alignment(oth, mov->position+R_DIR, mov->color, +R_DIR);
	/* Otherwise, the square is the same color, is a border or is empty, no flip possible */
	else
		mov->flip[4] = 0;
		
	/* If the diagonal bottom left square is the opposite color, there may be a flip */
	if(oth->array[mov->position+9] == opponent)
		mov->flip[5] = has_alignment(oth, mov->position+BLD_DIR, mov->color, BLD_DIR);
	/* Otherwise, the square is the same color, is a border or is empty, no flip possible */
	else
		mov->flip[5] = 0;
		
	/* If the diagonal middle bottom square is the opposite color, there may be a flip */
	if(oth->array[mov->position+10] == opponent)
		mov->flip[6] = has_alignment(oth, mov->position+BC_DIR, mov->color, BC_DIR);
	/* Otherwise, the square is the same color, is a border or is empty, no flip possible */
	else
		mov->flip[6] = 0;
		
	/* If the diagonal bottom right square is the opposite color, there may be a flip */
	if(oth->array[mov->position+11] == opponent)
		mov->flip[7] = has_alignment(oth, mov->position+BRD_DIR, mov->color, BRD_DIR);
	/* Otherwise, the square is the same color, is a border or is empty, no flip possible */
	else
		mov->flip[7] = 0;
		
	return 1;
}


short has_alignment(Othellier* oth, short position, short color, short direction) {
	
	short pos = position;
	
	/* Initializing the color of the opponent */
	short opponent = (color == BLACK ? WHITE : BLACK);
	
	/* While the next squarre in the same direction is an opponent pawn */
	while(oth->array[pos] == opponent) {
		
		/* If the current square is the player pawn, there is an alignment */
		if(oth->array[pos+direction] == color)
			return 1;
		
		/* Shifting to the next squarre */
		pos+=direction;
	}
	
	return 0;
}


int update_othellier(Game* game) {
	int i, counter = 0;
	
	/* Allocating memory for the move and exiting if there is an error */
	Move* mov = malloc(sizeof(Move));
	if(!mov) {
		perror("Move : Memory Allocation Failure");
		exit(EXIT_FAILURE);
	}
	
	/* For each square of the board, if the square was LEGAL, putting it on EMPTY */
	for(i=0; i<MAX_CASE; i++) {
			if(game->oth->array[i] == LEGAL)
				game->oth->array[i] = EMPTY;
	}
	
	/* Initializing the move */
	mov->color = game->turn;
	
	/* For each square of the board */
	for(i=0; i<MAX_CASE; i++) {
		
		/* If the square is empty, setting the move on the position of the square */
		if(game->oth->array[i] == EMPTY) {
			mov->position = i;
			
			/* If the move on the square is a legal move, putting the square on LEGAL */
			if(is_legal(game->oth, mov)) {
				game->oth->array[i] = LEGAL;
				counter++;
			}
		}
	}
	
	/* Deallocating the move */
	free(mov);
	
	/* Returning the number of legal moves */
	return counter;
}


void game_board_copy(Game* game) {
	short i;
	
	/* Allocating the memory for the storage of the last board */
	game->oths = realloc(game->oths, (game->boardsCursor+1) * sizeof(Othellier*));
	game->oths[game->boardsCursor] = malloc(sizeof(Othellier));
	
	/* Copying the material of each player */
	game->oths[game->boardsCursor]->piecesNb[BLACK] = game->oth->piecesNb[BLACK];
	game->oths[game->boardsCursor]->piecesNb[WHITE] = game->oth->piecesNb[WHITE];
	
	game->oths[game->boardsCursor]->turn = game->turn;
	/* For each squarre, copying the state in the storage emplacement */
	for(i=0; i<MAX_CASE; i++) {
		game->oths[game->boardsCursor]->array[i] = game->oth->array[i];
	}
	
	/* Incrementing the cursor to the end of the array */
	game->boardsCursor++;
	
	return;
}

int destroy_end_boards_tab(Game* game) {
	int i;
	/* If the cursor are equal, there is no cell of the array to free */
	if(game->boardsCursor == game->cursor)
		return 0;
	
	/* Freeing each cell of the array (because it is an array of pointers */
	for(i=game->boardsCursor-1; i>game->cursor; i--) {
		free(game->oths[i]);
		game->boardsCursor--;
	}
	
	/* Reallocating a smaller memory space for the array */
	game->oths = realloc(game->oths, game->boardsCursor * sizeof(Othellier*));
	
	return 1;
}

