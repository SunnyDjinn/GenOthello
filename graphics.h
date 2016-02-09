/** \file graphics.h
 * The header file of the graphics.c file. Here you cand find the protoypes of all functions of this file, and the macros related to the graphics of the game
 * */
 
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <stdio.h>
#include <stdlib.h>

/** \brief Preprocessor directive for the clearing of the console screen */
#define clear_screen() printf("\033[H\033[2J")

/** \brief Preprocessor directive for changing the text color and/or the background color */
#define color(param) printf("\033[%sm", param)

/** \brief Value for a text in black */
#define BLACK_TEXT "30"
/** \brief Value for a text in red */
#define RED_TEXT "31"
/** \brief Value for a text in green */
#define GREEN_TEXT "32"
/** \brief Value for a text in yellow */
#define YELLOW_TEXT "33"
/** \brief Value for a text in blue */
#define BLUE_TEXT "34"
/** \brief Value for a text in magenta */
#define MAGENTA_TEXT "35"
/** \brief Value for a text in cyan */
#define CYAN_TEXT "36"
/** \brief Value for a text in white */
#define WHITE_TEXT "37"

/** \brief Value for a background in black */
#define BLACK_BOARD "40"
/** \brief Value for a background in red */
#define RED_BOARD "41"
/** \brief Value for a background in green */
#define GREEN_BOARD "42"
/** \brief Value for a background in yellow */
#define YELLOW_BOARD "43"
/** \brief Value for a background in blue */
#define BLUE_BOARD "44"
/** \brief Value for a background in magenta*/
#define MAGENTA_BOARD "45"
/** \brief Value for a background in cyan */
#define CYAN_BOARD "46"
/** \brief Value for a background in white */
#define WHITE_BOARD "47"

/** \brief Value for a text in bold */
#define BOLD_TEXT "1"
/** \brief Value to reinitialize the background and text color */
#define REINIT "0"

/** \brief This function reinitializes the graphics (black background and white text by default) */
void reinit_graphics();

#endif


