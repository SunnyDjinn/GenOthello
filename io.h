/** \file io.h
 * The header file of the io.c file. Here you cand find the protoypes of all functions of this file
 * */
 
#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "constants.h"
#include "game.h"
#include "move.h"
#include "structures.h"


/** \brief This function displays the game board based on the type of the square
 * @param game : pointer to the Game structure 
 * 
 * The function is made so that the display looks like a real board. It displays a square for a black pawn, a triangle for a white pawn, a circle for a legal move, 
 * and pipes and underscore to delimit the borders of the board. */
void display_othellier(Game* game);


/** \brief This function converts an integer (representing a position in an array (max. size : MAX_CASE)) to a string containing coordinates (letter of the column, number of the row)
 * @param pos : a position integer
 * \return a string containing the coordinates converted
 * 
 * The function allocates a string with 3 character (column, line and the terminating character), converts into a line using the tens digit of the pos integer, converts into
 * column using the unit digit of the pos integer, and returns the string containing the cordinates. */
char* int2str(int pos);


/** \brief This function converts a string containing coordinates (letter of the column, number of the row) to an integer (representing a position in an array (max. size : MAX_CASE))
 * @param pos : a string containing the coordinates
 * \return an integer containing the coordinates converted
 * 
 * The function allocates converts the column letter into the tens digit of an integer, and the row number into the unit digit of the same integer. */
int char2int(const char* pos);


/** \brief This function determines if the coordinates passed in argument have the proper format to be converted to an integer
 * @param coord : a string containing the coordinates
 * \return Yes if the coordinates are in the good format, NO otherwise
 * 
 * If the column is 'under' A or 'over' H, the coordinates aren't good. The same way, if the line is under 0 or over 8, the coordinates are not in the board. */
int are_good_coordinates(const char* coord);


/** \brief This function allows the user to save the game in progress
 * @param game : a pointer to theGame structure
 * @param filename : a string containing the name of the file in which the user wants to save the game
 * \return 1 if the game has been saved, exits if the file can not be open
 * 
 * Opens the file names as 'filename'. Writes the moves done during the game under the format [+][Column letter][Row number] for a black move or [-] for a white move.
 * Writes the name of the black player, followed by his score, then the name of the white player followed by his score too. Updates the status of the 'saved game' box to YES. */
int game_saving(Game* game, const char* filename);


/** \brief This function imports/loads a game from a text file and store the data int the Game structure
 * @param filename : a string containing the name of the file used to load the game
 * \return the pointer to the Game structure just loaded
 * 
 * Opens the file names as 'filename'. Initializes the Game structure ans loads the succession of moves in the moves array. For each move loaded, the function play the move
 * to have the rigth game board at the end. The pieces numbers are recalculated each time. Loads and store players' names in their allocated space, closes the file and returns 
 * the pointer to the game. */
Game* load_game(char* filename);


/** \brief This function determines if the character passed in argument is a letter, a number, or something else
 * @param c : the character to determine
 * \return LETTER if it is a letter, NUMBER if it is a number, NO otherwise
 * 
 * Tests the ASCII code of the character passed. If it is between 'A' and 'Z' or 'a' and 'z', it is a letter. If it is between 'à' or '9', it is a number. Otherwise, it is neither. */
int is_a_letter(char c);


/** \brief This function determines if the string passed in argument contains only letter and number or not
 * @param str : the string to analyze
 * \return YES if it contains only letter or number, NO otherwise
 * 
 * For each character of the string, the function tests if it is a letter or a number. If so, it returns YES at the end. If a single character is not a letter or number, it returns NO. */
int contains_only_letters(char* str);


/** \brief This function modifies the string in argument to put each character in uppercase
 * @param str : the string to modify
 * \return 1 if the string has been transformed in uppercase, 0 if the string length is null
 * 
 * For each character of the string, the function calls toupper, which puts a character into its uppercase equivalent. If there is no character to analyze, the function return 0. */
int str2upper(char* str);


/** \brief This function empty the buffer so that the remaining character in the stream (stdin) can not be used for a future retrieving of data
 * 
 * While the character is not a new line or EOF, the function calls fgetc and looses the data taken. */
void empty_buffer();


/** \brief This function determines if the file passed in argument can be opened with the rights passed in argument
 * @param filename : the name of the file to open
 * @param right : the right to test : F_OK (to test the existence of the file), R_OK (for the reading right) or W_OK (for the writing right)
 * \return YES if the file exists and has the rights required, NO otherwise
 * 
 * Calls the function access from <unistd.h> and determines the rights thanks to it. */
int exists_file(char* filename, int right);


/** \brief This function allows to ask a YES/NO question to the user with the string passed in argument
 * @param string : the string to display as a Y/N question
 * \return YES if the user answer is YES, No otherwise
 * 
 * While the user answer is not Y or N, the function displays the string followed by the item (Y/N) to inform the user the nature of the question. Each loop turn, it empty the buffer 
 * and transforms the answer in uppercase. */
int ask_YN(char* string);

#endif

