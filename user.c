/** \file user.c
 * Functions related to the interactions between players and computer, including I/O interactions (such as asking players for an action)
 * */

#include "user.h"

short choose_game_type() {
	char line[MAX_LINE];
	
	/* Asking for a choice */
	do {
		printf("\nChose what type of game you wanna play:\n");
		printf("\n1 - Human vs. Human\n");
		printf("2 - Human vs Computer - ?\n");
		printf("3 - Computer vs Computer - ? : ");
		
		/* Retrieving the name in the name string */
		fgets(line, MAX_LINE, stdin);
		
		/* Ungetting the last character readed if the string entered is too long or for ungetting the new line character */
		ungetc(line[strlen(line)-1], stdin);
		
		/* Emptying the buffer (so that extra characters won't be used for the next name) */
		empty_buffer();
		
		line[1] = '\0';
		
	} while(line[ZERO] != '1' && line[ZERO] != '2' && line[ZERO] != '3');
	
	/* Returning 1 for the first choice, 2 for the second */
	return atoi(line);
}

short choose_player_color() {
	char line[MAX_LINE];
	
	do {
		
		/* Asking for a choice */
		printf("\nChose your player's color: \n");
		printf("\n1 - BLACK Player\n");
		printf("2 - WHITE Player - ? : ");
		
		/* Retrieving the name in the name string */
		fgets(line, MAX_LINE, stdin);
		
		/* Ungetting the last character readed if the string entered is too long or for ungetting the new line character */
		ungetc(line[strlen(line)-1], stdin);
		
		/* Emptying the buffer (so that extra characters won't be used for the next name */
		empty_buffer();
		
		line[1] = '\0';
		
	} while(line[ZERO] != '1' && line[ZERO] != '2');
	
	
	/* Returning 1 for the first choice, 2 for the second */
	return (atoi(line)-1);
}


void enter_one_name(Game* game, short color) {
	char name[MAX_NAME];
	char line[MAX_LINE];
	
	/* While the user is not satisfied with the name */
	do {
		/* Label for asking the black player */
		ask_name:
		
		/* Asking for the name of the black player */
		printf("\nEnter the name of the %s player (maximumof %d characters - letters and digits only): ", (color==BLACK?"BLACK":"WHITE"), MAX_NAME-1);
		
		/* Retrieving the name in the name string */
		fgets(name, MAX_NAME, stdin);
		
		/* Ungetting the last character readed if the string entered is too long */
		ungetc(name[strlen(name)-1], stdin);
		
		/* Emptying the buffer (so that extra characters won't be used for the next name */
		empty_buffer();
		
		/* If the last character of the name is a new line (that fgets can put into a string), replacing it with a string terminating character */
		if(name[strlen(name)-1] == NL)
			name[strlen(name)-1] = '\0';
		
		/* If the name conatins other characters than letters and numbers, asking again */
		if(!contains_only_letters(name))
			goto ask_name;
			
		/* While the answer is not Yes of No, asking if the name suits the player */
		do {
			printf("\n%s, is that the name you want? (Y/N) : ", name);
			fgets(line, MAX_LINE, stdin);
			str2upper(line);
		}	 
		while(line[ZERO] != 'Y' && line[ZERO] != 'N');
	}
	while(line[ZERO] == 'N');
	
	/* If the name entered for the white player is the same as the one for te black player, asking again */
	if(color == WHITE && game->p1.player_type == HUMAN && strcmp(name, game->p1.player_name) == 0) {
		printf("\nThis name is already taken");
		goto ask_name;
	}
	
	/* Copying the string into the reserved space for it and updating the type of the player (here HUMAN) */
	if(color == BLACK) {
		strcpy(game->p1.player_name, name);
		game->p1.player_type = HUMAN;
	}
	
	else {
		strcpy(game->p2.player_name, name);
		game->p2.player_type = HUMAN;
	}
	
	
	printf("\n");
}

void enter_players_names(Game* game) {
	
	/* Making the users choose their names */
	enter_one_name(game, BLACK);
	enter_one_name(game, WHITE);
	
	return;
}

void give_computer_name(Game* game, short color) {
	
	/* If the color of the computer player is black */
	if(color == BLACK) {
		
		/* If the two strings are the same, copying an alternative name for the computer */
		if(strcmp(game->p2.player_name, COMP_NAME) == 0) {
			strcpy(game->p1.player_name, ALT_COMP_NAME);
		}
		
		else {
			strcpy(game->p1.player_name, COMP_NAME);
		}
		
		/* Setting the type for the black player as 'COMPUTER'*/
		game->p1.player_type = COMPUTER;
	}

	/* If the color of the computer player is white */	
	else {
		
		/* If the two strings are the same, copying an alternative name for the computer */
		if(strcmp(game->p1.player_name, COMP_NAME) == 0) {
			strcpy(game->p2.player_name, ALT_COMP_NAME);
		}
			
		else {
			strcpy(game->p2.player_name, COMP_NAME);
		}
		
		/* Setting the type for the white player as 'COMPUTER'*/
		game->p2.player_type = COMPUTER;
	}
}

int ask_save_game(Game* game) {
	
	/* Testing whether the game is saved of not. If not, asking the players if they want to save it */
	if(game->saved == NO) {
		
		/* If the answer is yes, retrieving the name of the file */
		if(ask_YN("Do you wish to save the game?") == YES) {
			
			char filename[MAX_FILE_NAME];
			printf("\nType the saving file's name (maximum of %d characters) : ", MAX_FILE_NAME);
			
			fgets(filename, MAX_FILE_NAME, stdin);
			
			/* Ungetting the last character readed if the string entered is too long */
			ungetc(filename[strlen(filename)-1], stdin);
			
			/* Emptying the buffer (so that extra characters won't be used for the next answer */
			empty_buffer();
			
			/* If the last character of the name is a new line (that fgets can put into a string), replacing it with a string terminating character */
			if(filename[strlen(filename)-1] == NL)
				filename[strlen(filename)-1] = '\0';
			
			/* If the file already exists and can be opened for writing, asking if the user wants to continue */
			if(exists_file(filename, W_OK) == YES) {
				printf("\nThis file already exists, saving the game will erase all its contents");
				
				/* If he doesn't want to, returning NO for the saving */
				if(ask_YN("\nDo you wish to continue?") == NO)
					return NO;
			}
			
			/* Saving the game, and if it has been saved, printing a message */
			if(game_saving(game, filename))
				printf("\nYour game has been saved in the file '%s'\n", filename);
			
			/* If it has not been saved, printing an error */
			else
				printf("\nSomething went wrong, the game has not been saved - don't get mad at me...");
		}
		
		/* If player don't want to save the game, returning NO for the saving */
		else
			return NO;
	}
	
	/* If the game was already saved, printing a message */
	else {
		printf("\nThe current game is already saved");
		
		/* Returning no for the saving */
		return NO;
	}
	
	/* Returning YES if it has been saved */
	return YES;
}

int ask_new_game() {
	
	/* Asking for a new game */
	if(ask_YN("\nDo you want to start a new game?") == YES)
		return YES;
	else
		return NO;
}

char* ask_load_game() {
	
	/* Allocating the string for the return of the file name */
	char* filename = malloc(MAX_FILE_NAME * sizeof(char));
	
	printf("\nEnter the loading file's name: ");
	
	/* Getting the file name from the user */
	fgets(filename, MAX_FILE_NAME, stdin);
	
	/* Ungetting the last character readed if the string entered is too long */
	ungetc(filename[strlen(filename)-1], stdin);
	
	/* Emptying the buffer (so that extra characters won't be used for the next answer */
	empty_buffer();
	
	/* If the last character of the name is a new line (that fgets can put into a string), replacing it with a string terminating character */
	if(filename[strlen(filename)-1] == NL)
		filename[strlen(filename)-1] = '\0';

	/* Verifying that the file exixts */
	if(exists_file(filename, R_OK) == NO) {
		
			/* If not, printing an error, freeing the string and returning NULL */
			printf("\nThis file does not exist or is not valid\n\n");
			free(filename);
			return NULL;
		}
	
	return filename;
}


void display_usage() {
	/* Displaying the usage of the game */
	printf("\nTo display the help menu and obtain a list of features, type \"h\" or \"help\"\n");
	printf("To quickly start a new game, type \"n\" or \"new\"\n\n");
}

void display_help() {
	/* Displaying the help of the Othello game */
	printf("\n\t############################################ AIDE ########################################\n");
	printf("\t# To start a new game, type \"N\" or \"NEW\"                                                 #\n");
	printf("\t# To load a new game from a text file, type \"L\" ou \"LOAD\"                                #\n");
	printf("\t# During a game, to play a move, type the coordinates of the case                        #\n");
	printf("\t# To cancel a move, type \"C\" ou \"CANCEL\"                                                 #\n");
	printf("\t# To cancel a previous canceled move, type \"U\" ou \"UNCANCEL\"                             #\n");
	printf("\t# To save the game while playing, type \"S\" ou \"SAVE\"                                     #\n");
	printf("\t# To display this help, type \"H\" ou \"HELP\"                                               #\n");
	printf("\t# To quit the program, type \"Q\" ou \"QUIT\"                                                #\n");
	printf("\t# Commands can be typed indifferently in upper-case or lower-case                        #\n");
	printf("\t##########################################################################################\n");
}

void display_title() {
	/* Displaying the game title */
	printf("\n\t################################################\n");
	printf("\t|**********************************************|\n");
	printf("\t|**********************************************|\n");
	printf("\t|**************                   *************|\n");
	printf("\t|**************                   *************|\n");
	printf("\t|**************      WELCOME      *************|\n");
	printf("\t|**************                   *************|\n");
	printf("\t|**************        IN         *************|\n");
	printf("\t|**************                   *************|\n");
	printf("\t|**************      OTHELLO      *************|\n");
	printf("\t|**************                   *************|\n");
	printf("\t|**************                   *************|\n");
	printf("\t|**********************************************|\n");
	printf("\t|**********************************************|\n");
	printf("\t################################################\n");
}
