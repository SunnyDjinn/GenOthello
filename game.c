/** \file game.c
 * File for the algorithms and functions related to the management of the game itself
 * */

#include "game.h"


Game* init_game() {
	
	/* Memory allocation */
	Game* game = malloc(sizeof(Game));
	if(!game) {
		perror("Game : Memory Allocation Failure\n");
		exit(EXIT_FAILURE);
	}
	
	/* Move cursor initialization */
	game->cursor = ZERO;
	
	/* Initializing the cursor to the end of the moves and boards arrays */
	game->movesCursor = ZERO;
	game->boardsCursor = ZERO;
	
	/* Initializing the game status (saved of not) */
	game->saved = NO;
	
	/* Initializing the turn */
	game->turn = BLACK;
	
	/* Initializing the players */
	game->p1.player_name[ZERO] = UNKNOWN;
	game->p1.player_type = UNDEFINED;
	
	game->p2.player_name[ZERO] = UNKNOWN;
	game->p2.player_type = UNDEFINED;
	
	/* Initializing the moves array and the game boards array */
	game->moves = NULL;
	game->oths = NULL;
	
	/* Initializing the game board */
	game->oth = init_othellier();
	
	/* Copying the first board in their storage emplacement */
	game_board_copy(game);
	
	/* Initializing the coefficients for the evaluation function */
	load_coefs(game->coefs);
	
	return game;
}

void load_coefs(float coefs[]) {
	short i;
	/* If the file containing the coefficients exists */
	if(exists_file(COEFS_FILENAME, R_OK)) {
		/* Opening it */
		FILE* f1 = fopen(COEFS_FILENAME, "r");
		
		/* It there was a problem during the opening */
		if(!f1) {
		perror("FILE : Error opening the file");
		exit(EXIT_FAILURE);
		}
		
		/* Otherwise, reading the coefficients and storing them in the array */
		for(i=0; i<COEF_NB; i++)
			fscanf(f1, "%f", &coefs[i]);
		
		fclose(f1);
	}
	
	/* If the file does not exist, setting the coefficients to 1 */
	else {
		for(i=0; i<COEF_NB; i++)
			coefs[i] = 1;
	}
}


void update_turn(Game* game) {
	game->turn = whose_turn_is_it(game, game->turn);
}


short whose_turn_is_it(Game* game, int color) {
	
	/* Initializing the potential next player (the one who has not just played) */
	int next = (color == BLACK?WHITE:BLACK);
	
	/* If this one still has possible moves, he will be the next to play */
	if(has_legal_move(game, next))
		return next;
	
	/* Else, if the other player still has remaining possible moves, he plays again */
	else if(has_legal_move(game, color))
		return color;
		
	/* Otherwise, the game is over */
	else
		return END_OF_GAME;
}


short has_legal_move(Game* game, int color) {
	int i, svg = game->turn;
	
	/* Changing the turn to test if the move is legal */
	game->turn = color;
	
	/* Updating the game board */
	update_othellier(game);
	
	/* For each square of the game board, testing if the square is LEGAL */
	for(i=0; i<MAX_CASE; i++)
	
		/* If so, resetting the turn and retuning YES */
		if(game->oth->array[i] == LEGAL) {
			game->turn = svg;
			update_othellier(game);
			return YES;
		}
		
	/* Otherwise, resetting the move and returning NO */
	game->turn = svg;
	update_othellier(game);
	return NO;
}


void destroy_game(Game* game) {
	int i;
	
	/* Deallocating the played moves (stored in the moves array and in the boards array) */
	destroy_end_moves_tab(game);
	destroy_end_boards_tab(game);
	
	/* Deallocating the moves array and the boards array */
	for(i=0; i<game->cursor; i++) {
		free(game->moves[i]);
		free(game->oths[i]);
	}
	free(game->oths[i]);
	
	free(game->moves);
	free(game->oths);
	
	/* Deallocating the game board */
	free(game->oth);
	
	/* Deallocating the game */
	free(game);
	
	return;
}


short destroy_end_moves_tab(Game* game) {
	int i;
	/* If the cursor are equal, there is no cell of the array to free */
	if(game->movesCursor == game->cursor)
		return 0;
	
	/* Freeing each cell of the array (because it is an array of pointers */
	for(i=game->movesCursor-1; i>game->cursor-1; i--) {
		free(game->moves[i]);
		game->movesCursor--;
	}
	
	/* Reallocating a smaller memory space for the array */
	game->moves = realloc(game->moves, game->movesCursor * sizeof(Move*));
	
	return 1;
}




short end_of_game(Game* game) {
	
	/* If one of the two player has no remaining pawn on the board, the game is over, returning YES */
	if(game->oth->piecesNb[BLACK] == 0 || game->oth->piecesNb[WHITE] == 0)
		return YES;
	
	/* If the two player don't have any possible moves remaining, the game is over too */
	else if(!has_legal_move(game, game->turn) && !has_legal_move(game, (game->turn == BLACK?WHITE:BLACK)))
		return YES;
	
	/* Otherwise, the game continues */
	else
		return NO;
}

short is_computer_game(Game* game) {
	
	/* If one of the two players is the computer, returning YES */
	if(game->p1.player_type == COMPUTER || game->p2.player_type	== COMPUTER)
		return YES;
	return NO;
}


Game* end_of_game_action(Game* game) {
	
	short gameType;
	
	/* If the game has not reached the end, there is no action to realize */
	if(!end_of_game(game))
		return NULL;
	
	/* Else, informs players the game is over */
	printf("Plus aucun coup possible : fin du jeu\n");
	
	/* If the black player has more pawn, he wins */
	if(game->oth->piecesNb[BLACK] > (game->oth->piecesNb[WHITE]))
		printf("\n%s a gagné !\n", game->p1.player_name);
		
	/* Else, if the white one has more pawn, he wins */
	else if(game->oth->piecesNb[BLACK] < (game->oth->piecesNb[WHITE]))
		printf("%s a gagné !\n", game->p2.player_name);
		
	/* Else, the two players are dead heat */
	else
		printf("%s et %s sont ex-aequo !\n", game->p1.player_name, game->p2.player_name);
		
	printf("Score : %d - %d\n", game->oth->piecesNb[BLACK], game->oth->piecesNb[WHITE]);
	
	/* Asking the players if they want to save the game */ 
	ask_save_game(game);
	
	/* Freeing the game */
	destroy_game(game);
	game = NULL;
	
	/* Asking the players if they want to play another time */
	if(ask_new_game() == YES) {
		
		/* If so, initializing the game, the players' names ans the board */
		game = init_game();
		
		/* Choosing the game type (H vs H or H vs C) */
		gameType = choose_game_type();
	
		/* If the game type is Human vs Human */
		if(gameType == H_VS_H) {
			/* Asking for the two players' names */
			enter_players_names(game);
		}
	
		/* If the game type is Human vs Computer */
		else if(gameType == H_VS_C) {
		
			/* Choosing the color of the human player, and asking for his name */
			gameType = choose_player_color();
			enter_one_name(game, gameType);
		
			/* Giving the computer the other player and giving it a name */
			give_computer_name(game, (gameType+1)%2);
		}
		
		else if(gameType == C_VS_C) {
		
		/* Giving the computer the other player and giving it a name */
			give_computer_name(game, 0);
			give_computer_name(game, 1);
		}
		clear_screen();
		display_othellier(game);
		printf("Au tour de %s de jouer :\n", game->turn==BLACK?game->p1.player_name:game->p2.player_name);
		game = play_ai(game);
	}
	/* Otherwise, clearing the screen and returning NULL */
	else
		clear_screen();

	return game;
}

Game* play_ai(Game* game) {
	
	if(!game)
		return NULL;
	
	/* If the game doesn't imply the computer, no need to play */
	if(!is_computer_game(game))
		return game;
	
	/* If the turn is not to the computer, no need to play */
	if(!((game->turn == BLACK && game->p1.player_type == COMPUTER) || (game->turn == WHITE && game->p2.player_type == COMPUTER)))
		return game;
	
	short turn = game->turn;

	printf("Loading...\n");
	
	/* Finding the best move to play */
	short position = min_max(YES, game, game->turn, GLOBAL_DEPTH, GLOBAL_DEPTH, SHRT_MIN, SHRT_MAX, game->coefs);
	
	/* If the move is not legal or the coordinates don't have the good format, which should not happen */
	if(move_processing(game, UNKNOWN, position) != 1) {
		return game;
	}
	
	destroy_end_boards_tab(game);
	destroy_end_moves_tab(game);
	
	update_othellier(game);
	
	clear_screen();
	display_othellier(game);

	/* If the end of the game is reached, performing and end of game action */
	if(end_of_game(game))
		game = end_of_game_action(game);
		
	else if(game->turn == turn) {
		printf("### %s passe son tour !###\n\n", game->turn==BLACK?game->p2.player_name:game->p1.player_name);
		printf("Au tour de %s de jouer :\n", game->turn==BLACK?game->p1.player_name:game->p2.player_name);
		game = play_ai(game);
	}
	
	else
		printf("Au tour de %s de jouer : \n", game->turn==BLACK?game->p1.player_name:game->p2.player_name);
	
	/* Playing another time if it's a C_VS_C game */
	game = play_ai(game);
	
	return game;
}

