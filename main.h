/** \file main.h
 * The header file of the main.c file. Here you cand find all the header requisites of the project, and the global variables
 * */
 
#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "constants.h"
#include "events.h"
#include "genetic.h"
#include "graphics.h"
#include "structures.h"
#include "user.h"

/** \brief The main function of the project.
 * 
 * The main function has been designed to be a kind of interpretor. Almost at any time the user can make an action, such as loading a game, saving the current one,
 *  cancelling a move or redo one. */
int main(void);

#endif
