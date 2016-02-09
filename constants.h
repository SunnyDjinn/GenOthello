/** \file constants.h
 * A file in which one can find all the macros used in the Othello Project
 * */

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

/** \brief Macro Yes */
#define YES 1
/** \brief Macro No*/
#define NO 0

/** \brief Defines if the genetic algorithm is running of not 
 * \warning Set to O for a use by real players, 1 to make the genetic alogrithm run well */
#define GEN_ALGO 0

/** \brief The depth used in the min-max algorithm */
#define GLOBAL_DEPTH 6

/** \brief The number of generations */
#define GENERATION_NB 35
/** \brief The number of game to play between genomes */
#define GAME_NB 10
/** \brief The number of coefficients in the evaluation function */
#define COEF_NB 4
/** \brief The number of genomes (total initial population) */
#define GENOMES_NB 24
/** \brief Defines the probability of a gene mutation */
#define MUT_FACTOR 0.05
/** \brief The upper bound of the random number for each coefficient used in the genetic algorithm */
#define MAX_COEF 2.5
/** \brief The name of the file in which the coefficients determined by the genetic algorithm are stored */
#define COEFS_FILENAME "GENETIC_ALGORITHM_DO_NOT_DELETE.txt"



/** \brief Macro 0 */
#define ZERO 0
/** \brief Square number of the board array */
#define MAX_CASE 100
/** \brief Board array dimension */
#define MAX_DIM 10
/** \brief Maximum number of moves during a game */
#define MAX_MOVE 60
/** \brief Black pawn code */
#define BLACK 0
/** \brief White pawn code */
#define WHITE 1
/** \brief Empty square code */
#define EMPTY 2
/** \brief Border square code */
#define BORDER 3
/** \brief Legal square code */
#define LEGAL 4

/** \brief Top left corner square code */
#define TL_CORNER 11
/** \brief Top right corner square code */
#define TR_CORNER 18
/** \brief bottom left corner square code */
#define BL_CORNER 81
/** \brief bottom right corner square code */
#define BR_CORNER 88

/** \brief Top left diagonal direction */
#define TLD_DIR -11
/** \brief Top center direction */
#define TC_DIR -10
/** \brief Top right diagonal direction */
#define TRD_DIR -9
/** \brief Left direction */
#define L_DIR -1
/** \brief Right direction */
#define R_DIR +1
/** \brief Bottom left diagonal direction */
#define BLD_DIR +9
/** \brief Bottom center diagonal direction */
#define BC_DIR +10
/** \brief Bottom right diagonal direction */
#define BRD_DIR +11

/** \brief Players number */
#define PLAYER_NB 2
/** \brief Human player type */
#define HUMAN 0
/** \brief Computer player type (AI) */
#define COMPUTER 1
/** \brief Humand vs Human return code */
#define H_VS_H 1
/** \brief Human vs Computer return code */
#define H_VS_C 2
/** \brief Computer vs Computer return code */
#define C_VS_C 3

/** \brief Number of moves under which the game is considered as early */
#define EARLY_GAME 10
/** \brief Number of moves under which the game is considered as middle */
#define MIDDLE_GAME 42
/** \brief Number of moves under which the game is considered as late */
#define LATE_GAME 60

/** \brief Maximum length of the player name string */
#define MAX_NAME 15
/** \brief Maximum length of the interpretor command string */
#define MAX_LINE 15
/** \brief Maximum length of the saving file name string */
#define MAX_FILE_NAME 20

/** \brief Size of the array for the existence of flip around a square of the board */
#define MAX_FLIP 8

/** \brief Game board dimensions number */
#define NB_DIM 2

/** \brief ASCII code of the 'A' letter */
#define ASCII_A 65
/** \brief ASCII code of the 'H' letter */
#define ASCII_H 72
/** \brief ASCII code of the 'Z' letter */
#define ASCII_Z 90
/** \brief ASCII code of the 'a' letter */
#define ASCII_A_MIN 97
/** \brief ASCII code of the 'z' letter */
#define ASCII_Z_MIN 122
/** \brief ASCII code of the '0' number */
#define ASCII_0 48
/** \brief ASCII code of the '8' number */
#define ASCII_8 56
/** \brief ASCII code of the '9' number */
#define ASCII_9 57
/** \brief New Line ASCII code */
#define NL 10
/** \brief Space ASCII code */
#define SPACE 32

/** \brief Return code for being a letter for a character */
#define LETTER 1
/** \brief Return code for being a number for a character */
#define NUMBER 2

/** \brief Return code for bad coordinates */
#define BAD_COORDINATES -1
/** \brief Return code for a not legal move */
#define NOT_LEGAL -2

/** \brief Macro for the definition of players names before knowing it */
#define UNKNOWN '\0'

/** \brief Macro for undefined initialisation */
#define UNDEFINED -1

/** \brief Macro for not modifying some values. Used during a call to a function not to modify the value concerned */
#define DONT_TOUCH -3

/** \brief Return code for the end of the game */
#define END_OF_GAME -1

/** \brief The name of the computer during a human vs computer game */
#define COMP_NAME "COMPUTER"
/** \brief The alternative name of the computer during a human vs computer game */
#define ALT_COMP_NAME "COMPUTER-IA"

#endif
