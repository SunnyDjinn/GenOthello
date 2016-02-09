/** \file io.c
 * Functions related to the processing of Input / Output data
 * */
#include "io.h"

void display_othellier(Game* game) {
	int i, j = 1, k = ASCII_A;
	printf("\n");
	/* For each square of the game board */
	for(i=0; i<MAX_CASE; i++) {
		
		switch(game->oth->array[i]) {
			/* If the square has a black pawn */
			case BLACK: printf("  ■  |");
				break;
				
			/* If the square has a white pawn */
			case WHITE: printf("  ▲  |");
				break;
				
			/* If the square has no pawn */	
			case EMPTY: printf("     |");
				break;
			
			/* If the square is a border */
			case BORDER:
			
				/* If the border is a left border */
				if(i%MAX_DIM == 0) {
					
					/* If the border is on top or at the bottom */
					if(i == 0 || i == 90)
						printf("\t |");
						
					/* Else, displaying the number of the row */
					else
						printf("\t%d|", j++);
				}
				
				/* If the border is a right border */
				else if(i%MAX_DIM == 9)
					printf("\n\n");
					
				/* If the border is a bottom border */
				else if(i>=90)
					printf("_____|");
					
				/* If the border is a top border, displaying the letter of the column */
				else
					printf("  %c  |", k++);
				break;
				
			/* If the square is a legal move */
			case LEGAL:
				printf("  ○  |");
				break;
				
			default:
				break;
		}
	}
	/* Displaying the score and the players' names */
	printf("\t\t\tBLACK %d - %d WHITE\n\n", game->oth->piecesNb[BLACK], game->oth->piecesNb[WHITE]);
	printf(" Black Player ■  %s\n", game->p1.player_name);
	printf(" White Player ▲  %s\n", game->p2.player_name);
	printf("\n");
	printf("Move number: %d\n\n", game->cursor);
	
	/* Displaying the last move played only if a move has been played and freeing the string returned by int2str */
	if(game->cursor > 0) {
		char* coord = int2str(game->moves[game->cursor-1]->position);
		printf("Last move played: %s\n\n", coord);
		free(coord);
	}
}


char* int2str(int pos) {
	int line, col;
	
	/* Allocating a string to return with the coordinates in */
	char* position = malloc((NB_DIM + 1) * sizeof(char));
	
	/* The end of the string is a terminating character */
	position[2]='\0';
	
	/* The line (second cell of the string) is the tens digit of the position */
	line = pos/MAX_DIM + (ASCII_0);
	position[1] = (char)line;
	
	/* the column (first cell of the string) is the unit digit of the position */
	col = pos;
	while(col>=MAX_DIM) {
		col-=MAX_DIM;
	}
	/* The column is a letter, adding the ASCII code of A */
	position[0] = ASCII_A -1 + col;
	
	return position;
}

int char2int(const char* pos) {
	/* The line is the second cel of the coordinates string */
	char line = pos[1];
	
	/* The column is the first one, transforming to uppercase for uniformity */
	char col = toupper((int)pos[0]);
	
	/* The final position is the line minus the ASCII code of 0, times MAX_DIM, plus the column minus the ASCII code of A plus 1 */
	int position = ((int)line - ASCII_0) * MAX_DIM + ((int)col - ASCII_A + 1);
	
	return position;
}

int are_good_coordinates(const char* coord) {
	/* Transforming the coordinate to upercase for uniformity */
	char c = toupper((int)coord[0]);
	
	/* If the column is under 'A' */
	if(c < ASCII_A)
		return NO;
		
	/* If the column is over 'H' */
	if(c > ASCII_H)
		return NO;
		
	/* If the row is under '0' */
	if(coord[1] <= ASCII_0)
		return NO;
		
	/* If the row is over '8' */
	if(coord[1] > ASCII_8)
		return NO;
		
	/* Otherwise, coordinates are in the proper format */
	return YES;
}

int game_saving(Game* game, const char* filename) {
	int i;
	/* Creating a pointer to the stream and opening the file passed in argument */
	FILE* f1 = fopen(filename, "w");
	
	/* If the file couldn't be opened, an error is raised */
	if(!f1) {
		perror("FILE : Error opening the file");
		exit(EXIT_FAILURE);
	}
	
	char* a;
	/* For each cell in the moves array */
	for(i=0; i<game->cursor; i++) {
		
		/* If the player who made the move was the black one */
		if(game->moves[i]->color == BLACK)
			fprintf(f1,"+%s", a = int2str(game->moves[i]->position));
			
		/* If the player was the white one */
		else
			fprintf(f1, "-%s", a = int2str(game->moves[i]->position));
		
		/* freeing the string used for the conversion */
		free(a);
	}
	/* Writing the players' names and the scores in the file */
	fprintf(f1, "\n\n%s : %d", game->p1.player_name, game->oth->piecesNb[BLACK]);
	fprintf(f1, "\n%s : %d", game->p2.player_name, game->oth->piecesNb[WHITE]);
	
	/* Updating the saving status of the game */
	game->saved = YES;
	
	/* Closing the stream */
	fclose(f1);
	
	return 1;
}

Game* load_game(char* filename) {	
	/* Creating a pointer to the stream and opening the file passed in argument */
	FILE* f1 = fopen(filename, "r");
	
	/* If the file couldn't be opened, an error is raised */
	if(!f1) {
		perror("FILE : Error opening the file");
		exit(EXIT_FAILURE);
	}
	
	/* Initialization of the game before its loading */
	Game* game = init_game();
	
	char a, b[MAX_DIM], name[MAX_NAME];
	int i;
	
	/* The end of the string is a terminating character */
	b[MAX_DIM] = '\0';
	
	/* Loading the first character of the file */
	a = fgetc(f1);
	
	/* If the first character of the vide is EOF, the file is empty, charging a new game */
	if(a == EOF) {
		return game;
	}
	
	/* If it's a '+' or a '-', the line is not empty */
	if(a == '+' || a == '-') {
		
		/* While the first character loaded is a '+' or a '-', there is still moves remaining in the file */
		while( a == '+' || a == '-') {
			
			/* Loading the coordinates */
			b[0] = fgetc(f1);
			b[1] = fgetc(f1);
			
			/* Playing the move just loaded, the game turn is taken into consideration in the function move_processing() */
			move_processing(game, b, UNDEFINED);
		
			/* Loading the next character */
			a = fgetc(f1);
		}
	}
	
	/* Emptying the caracters before the name of the first player */
	while (!(is_a_letter(a) == LETTER))
		a = fgetc(f1);
	
	i = 0;
	/* Stocking the first letter returned by the last fgetc, while it is a letter or a number, it is still the name of the first player */
	while(is_a_letter(a)) {
		name[i++] = a;
		a = fgetc(f1);
	}
	
	/* At the end of the name, terminating the string by a terminating character */
	name[i] = '\0';
	
	/* Copying the string in the first player player name emplacement */
	strcpy(game->p1.player_name, name);
	
	/* If the first player is the computer, updating his type */
	if(strcmp(name, COMP_NAME) == 0 || strcmp(name, ALT_COMP_NAME) == 0)
		game->p2.player_type = COMPUTER;
	else
		game->p2.player_type = HUMAN;
		
	/* Emptying the caracters before the name of the second player */
	while (!(is_a_letter(a) == LETTER))
		a = fgetc(f1);
	
	i = 0;
	/* Stocking the first letter returned by the last fgetc, while it is a letter or a number, it is still the name of the second player */
	while(is_a_letter(a)) {
		name[i++] = a;
		a = fgetc(f1);
	}
	
	/* At the end of the name, terminating the string by a terminating character */
	name[i] = '\0';
	
	/* Copying the string in the second player player name emplacement */
	strcpy(game->p2.player_name, name);
	
	/* If the second player is the computer, updating his type */
	if(strcmp(name, COMP_NAME) == 0 || strcmp(name, ALT_COMP_NAME) == 0)
		game->p2.player_type = COMPUTER;
	else
		game->p2.player_type = HUMAN;
		
	/* Closing the stream */
	fclose(f1);
	
	game->saved = YES;
	return game;
}

int is_a_letter(char c) {
	/* If the ASCII code of the character is between those of 'A' and 'Z', it is a letter */
	if(c >= ASCII_A && c <= ASCII_Z)
		return LETTER;
		
	/* If the ASCII code of the character is between those of 'a' and 'z', it is a letter */
	if(c >= ASCII_A_MIN && c <= ASCII_Z_MIN)
		return LETTER;
	
	/* If the ASCII code of the character is between those of '0' and '9', it is a number */
	if(c >= ASCII_0 && c <= ASCII_9)
		return NUMBER;
	
	/* Else, it is neither a letter nor a number */
	return NO;
}

int contains_only_letters(char* str) {
	int i;
	
	/* For each character of the string, testing if it is a letter */
	for(i=0; i<strlen(str); i++)
	
		/* If not, it does not contain only letter or number */
		if(!is_a_letter(str[i]))
			return NO;
			
	return YES;	
}


int str2upper(char* str) {
	int i;
	/* If the string length is zero, there is no need to transform to uppercase */
	if(strlen(str) == ZERO)
		return 0;
		
	/* For each character of the string, transforming to uppercase */
	for(i=ZERO; i<strlen(str); i++)
		str[i] = toupper(str[i]);
		
	return 1;
}

void empty_buffer()
{
    char c = 0;
    
    /* While the character is not and EOF character of the end of the line ('\n'), getting the character from stdin to empty the buffer */
    while (c != '\n' && c != EOF)
        c = fgetc(stdin);
}


int exists_file(char* filename, int right) {
	
	/* If the file is accessible with the right "right", returning YES */
	if(access(filename, right) == 0)
		return YES;
	return NO;
}


int ask_YN(char* string) {
	char response[MAX_LINE];
	
	/* While the player answer isn't a Yes or a No, printing the string passed in argument and getting the answer */
	do {
		printf("\n%s (Y/N) : ", string);
		
		/* Getting the answer */
		fgets(response, MAX_LINE, stdin);
		
		/* Ungetting the last character readed if the string entered is too long */
		ungetc(response[strlen(response)-1], stdin);
		
		/* Emptying the buffer (so that extra characters won't be used for the next answer */
		empty_buffer();
		
		/* Transforming to uppercase */
		str2upper(response);
	}	 
	while(response[ZERO] != 'Y' && response[ZERO] != 'N');
	
	/* Returning YES if the answer is positive, NO otherwise */
	if(response[ZERO] == 'Y')
		return YES;
	
	return NO;	
}

