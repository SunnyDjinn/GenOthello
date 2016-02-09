/** \file events.c
 * File for the management of the different events the game can receive
 * */

#include "events.h"

void capture_SIGINT() {
	printf("\nThe current game will not be saved\n");
	printf("Bye bye\n");
	
	/* Exiting with failure because SIG_INT received */
	exit(EXIT_FAILURE);
}

void event_cancel(Game* game) {
	
	/* If there is a game in progress */
	if(game != NULL) {
		
		short turn = game->turn;
		
		/* Canceling the last move */
		cancel_last_move(game);
		
		/* If the game is against the computer, canceling as needed so that the human player has to play again */
		if(is_computer_game(game)) {
			while(game->turn != turn && game->cursor != 0)
			cancel_last_move(game);
		}
		
		/* Clearing the screen */
		clear_screen();
		
		/* Updating and displaying the game board */
		update_othellier(game);
		display_othellier(game);
		printf("%s's turn:\n", game->turn==BLACK?game->p1.player_name:game->p2.player_name);
		play_ai(game);
	}
}

void event_uncancel(Game* game) {
	
	/* If there is a game in progress */
	if(game != NULL) {
		
		short turn = game->turn;
		
		/* Uncanceling the last canceled move */
		uncancel_move(game);
		
		/* If the game is against the computer, uncanceling as needed so that the human player has to play again */
		if(is_computer_game(game)) {
			while(game->turn != turn && game->cursor < 60)
			uncancel_move(game);
		}
		
		/* Clearing the screen, updating the game board ans displaying it */
		clear_screen();
		update_othellier(game);
		display_othellier(game);
		printf("%s's turn:\n", game->turn==BLACK?game->p1.player_name:game->p2.player_name);
	}	
}

void event_help() {
	
	/* Displaying the help */
	clear_screen();
	display_help();
}

Game* event_load(Game* game) {
	
	/* If there is a game in progress, asking for its saving */
	if(game != NULL) {
		ask_save_game(game);
		
		/* Freeing the game after its saving */
		destroy_game(game);
		game = NULL;
	}
	
	char* filename = ask_load_game();
			
	/* If filename = NULL, the file doesn't exists */
	if(filename != NULL) {
		
		/* Loading the game from the file and clearing the screen */
		game = load_game(filename);
		free(filename);
		clear_screen();
		
		/* Updating and displaying the game board */
		update_othellier(game);
		display_othellier(game);
		
		/* If the end of game is reached */
		if(end_of_game(game))
		
			/* Performing an end of game action */
			game = end_of_game_action(game);
		else
			printf("%s's turn:\n", game->turn==BLACK?game->p1.player_name:game->p2.player_name);
	}
	
	return game;
}

void event_save(Game* game) {
	
	/* If there is a game in progress */
	if(game != NULL) {
		/* Asking for the saving of the game */
		ask_save_game(game);
	}
}

Game* event_new(Game* game) {
	short gameType;
	
	/* If there is a game in progress */
	if(game != NULL) {
		
		/* Asking for its saving and freeing it */
		ask_save_game(game);
		destroy_game(game);
		game = NULL;
	}
	
	/* Initializing a new game */
	game = init_game();
	clear_screen();
	
	/* Choosing the game type (H vs H or H vs C or C vs C) */
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
	
	/* Clearing the screen, updating and displaying the game board */
	clear_screen();
	update_othellier(game);
	display_othellier(game);
	
	printf("%s's turn: \n", game->p1.player_name);
	
	game = play_ai(game);
	
	return game;
}

Game* event_other(Game* game, char* command) {
	short coordValue;
	
	/* If there is a game in progress */
	if(game != NULL) {
		
		short turn = game->turn;
		clear_screen();
		
		/* Processing the move and displaying the game board */
		coordValue = move_processing(game, command, UNDEFINED);
		display_othellier(game);
		
		/* If the coordinates were bad */
		if(coordValue == BAD_COORDINATES)
			printf("/!\\ Invalid coordinates /!\\ \n\n");
		
		/* Else if the coordinates were illegal*/
		else if(coordValue == NOT_LEGAL)
			printf("/!\\ Illegal move /!\\ \n\n");
		
		/* If the end of game has been reached , performing an end of game action */
		if(end_of_game(game))
			game = end_of_game_action(game);
		
		/* If the turn is to the same player after a move has been played, the other player passes his turn */
		else if(game->turn == turn && coordValue == 1) {
			printf("### %s misses their turn!###\n\n", game->turn==BLACK?game->p2.player_name:game->p1.player_name);
			printf("%s' turn:\n", game->turn==BLACK?game->p1.player_name:game->p2.player_name);
			game = play_ai(game);
		}
			
		else {
			printf("%s's turn:\n", game->turn==BLACK?game->p1.player_name:game->p2.player_name);
			game = play_ai(game);
		}
	}
	
	else
		printf("Unrecognized command\n");
	
	return game;
}

void event_quit(Game* game) {
	
	/* If a game was in progress */
	if(game != NULL) {
		
		/* Asking for its saving if it was not saved before */
		if(game->saved == NO) {
			
			if(ask_YN("Do you wish to save the current game?") == YES) {
				char name[MAX_FILE_NAME];
				
				printf("\nEnter the saving file's name (maximum of %d characters) : ", MAX_FILE_NAME);
				fgets(name, MAX_FILE_NAME, stdin);
				
				/* If the game has correctly been saved */
				if(game_saving(game, name))
					printf("\nYour game has been saved in the file '%s'", name);
				else
					printf("\nSomething went wrong, the game has not been saved - don't get mad at me...");
			}
		}
		/* Freeing the game */
		destroy_game(game);
		
	}
	printf("\nBye bye!\n\n");
	/* Exiting */
	exit(EXIT_SUCCESS);
}

