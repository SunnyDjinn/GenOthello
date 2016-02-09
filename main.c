/** \file main.c
 * The main file of the project. Here is only the main fonction
 * */
 
/** \mainpage Othello 
 * 
 * This is the documentation of the program Othello, developed by S. Guiol.
 * 
 * RULES :
 * 
 * 		The Othello game is constituted of a board of 64 squares (8x8). The game is played with 2 players, the Black one and the White one. 
 * 
 * 		At the beginning, each player has 2 pawns of his color in diagonal on the center of the board.
 * 		The black player always goes first.
 * 
 * 		To make a move, the player has to put a pawn of his color on a square so that it makes the pawn(s) of his opponent framed in at least one direction.
 * 		More specifically, he can put a pawn on a square only if, in at least one of the eight directions, two of his pawns are separated by only opponent's pawns and at least one.
 * 		To form an alignment, his two pawns can not be separated by empty cases, unless they make an alignment in another direction.
 * 
 * 		For each alignment formed, all the opponent's pawns located between two of his pawns (including the one he just placed) are reversed (they become his and change their color).
 * 		
 * 		If one player don't have any possible move, the turn passes to the other player.
 * 		
 * 		The game stops when all the board is full or when the two players don't have any remaining move to make.
 * 
 * 		The winner is, at the end of the game, the one who has the more pawns of his color. If the two players have the same amount of pawn, they are dead heat.
 * 
 * USING THE SOFTWARE : 
 *  
 * 		The software is easy to use. After launching, a little usage is displayed. If you need more help, type "H" or "HELP".
 * 		The following commands are implemented : 
 * 
 * 												N or NEW : Begins a new game
 * 
 * 												L or LOAD : Loads a game from a text file
 * 
 * 												S or SAVE : Saves the game in progress in a text file
 * 
 * 												H or HELP : Displays the help
 * 
 * 												C or CANCEL : Cancels the last move played
 * 
 * 												U or UNCANCEL : Uncancels the last canceled move
 * 
 * 												Q or QUIT : Exits the game
 * 
 * 		Typing in uppercase or lowercase doesn't matter.
 * 
 * 		While in a game, all commands above are recognised, unless you are performing a typing action (answering to a question from the software for instance).
 * 		If you only want to play, when the board is displayed on the screen, just type the coordinates you want to play.
 * 
 * */
 
#include "main.h"


int main(void) {
	
	/** String for the input in the interpretor (main). Maximum length MAX_LINE */
	char line[MAX_LINE];
	
	/** String for only the first word of the input in the interpretor (main). Maximum length MAX_LINE */
	char command[MAX_LINE];

	/** Temporary string (buffer) for the remaining characters of the input. Won't be used, only to extract the first word considered as the command */
	char tmp[MAX_LINE];

	/** Integer to retreive the number of arguments of line, but used to test if there was no input failure (EOF returned by sscanf) */
	int argNb;
	
	if(GEN_ALGO) {
		printf("Commencement de l'algorithme génétique\n");
		genetic_algorithm();
	}
	
	else {
		Game* game = NULL;

		clear_screen();
		display_title();
		display_help();
		display_usage();
		
		while(1){
			printf("> ");
			
			/* Capturing any ^C signal in order to inform the user that they will lose their game in progress */
			signal(SIGINT, capture_SIGINT);
			
			/* If error of EOF is reached, exiting the program */
			if(fgets(line, MAX_LINE, stdin) == NULL) {
				exit(EXIT_FAILURE);
			}
			
			/* Retrieving only the first word of the input */
			argNb = sscanf(line, "%s %s\n", command, tmp);
			
			/* Putting the command in uppercase for uniformity */
			str2upper(command);
			
			/* If there is any reading problem, resuming the loop from the beginning */
			if(argNb == EOF)
				continue;
				
			if(!strcmp(command, "C") || !strcmp(command, "CANCEL")){
				event_cancel(game);
			}
			
			/* If the command is 'U' or 'UNCANCEL', cancelling the last move */
			else if(!strcmp(command, "U") || !strcmp(command, "UNCANCEL")){
				event_uncancel(game);
			}
			
			/* If the command is 'H' or 'HELP', displaying the help menu */
			else if(!strcmp(command, "H") || !strcmp(command, "HELP")){
				event_help();
			}
			
			/* If the command is 'L' or 'LOAD', charging a game */
			else if(!strcmp(command, "L") || !strcmp(command, "LOAD")){
				game = event_load(game);
			}
			
			/* If the command is 'S' or 'SAVE', saving the game in progress */
			else if(!strcmp(command, "S") || !strcmp(command, "SAVE")){
				event_save(game);
			}
			
			/* If the command is 'Q' or 'QUIT', exiting the program */
			else if(!strcmp(command, "Q") || !strcmp(command, "QUIT")){
				event_quit(game);
			}
			
			/* If the command is 'N' or 'NEW', beginning a new game */
			else if(!strcmp(command, "N") || !strcmp(command, "NEW")){
				game = event_new(game); 
			}
			
			/* Otherwise, the command is a coordinate or the command is unknown */
			else {
				game = event_other(game, command);
			}
			
		}
	}
	return EXIT_SUCCESS;
}
