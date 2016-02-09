/** \file genetic.h
 * The header file of the .c file genetic.c. Here you can find the protoypes of all functions of this file
 * */

#ifndef __GENETIC_H__
#define __GENETIC_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "constants.h"
#include "structures.h"
#include "ai.h"
#include "move.h"



/** \brief This function generates a random number between lowerBound and upperBound
 * @param lowerBound : the lower bound of the random number
 * @param upperBound : the upper bound of the random number
 * \return a random float
 * 
 *  Generates a random number between lowerBound and upperBound. Rounds it to the nearest tenth number. */
float random_tenth(short lowerBound, short upperBound);



/** \brief This function creates a random initial population
 * @param populationNb : pointer to the Game structure 
 * \return the initialized population 
 * 
 * The allocates the memory space used for a population of size populationNb. Generates random coefficients and initilizes the fitness to 0 */
Population* initial_population(short populationNb);



/** \brief This function makes genomes play against each other
 * @param pop : pointer to a population structure 
 * @param gameNb : the number of game each genome has to play
 * @param f1 : the file in which data are stored
 * 
 * Makes each genome play against gameNb others, caculates their fitness and stores data in the file.  */
void fitness(Population* pop, short gameNb, FILE* f1);



/** \brief This function creates a new generation based on the previous one
 * @param initial : pointer to the initial population structure 
 * \return the new generation created
 * 
 * Uses the system of the biased wheel in order to select most of the best genomes. Makes them reproduce to create a new generation, and makes each genome mutate. */
Population* next_generation(Population* initial);



/** \brief Allows two genomes to reproduce in order to create 2 new ones
 * @param initial : pointer to the initial population structure 
 * @param next : pointer to the next population structure 
 * @param parentA : number of the first parent
 * @param parentB : number of the second parent
 * @param childA : number of the first child
 * @param childB : number of the second child 
 * 
 * Uses random numbers to make 2 genomes reproduce and stores the result in the next population at indexs childA and childB. */
void reproduction(Population* initial, Population* next, short parentA, short parentB, short childA, short childB);



/** \brief Allows genomes to mutate
 * @param next : pointer to the next population structure 
 * @param genomeToMutate : the index of the genome to mutate in the next generation
 * 
 * Randomly chose a number between 0 and 1. If this one is below MUT_FACTOR, changes randomly all coefficients of the genome. */
void mutation(Population* next, short genomeToMutate);



/** \brief Searches the best genome in the population in argument
 * @param pop : pointer to a population structure 
 * \return the index of the ebst genome found */
short search_best_genome(Population* pop);



/** \brief Saves the coefficients passed in argument in a file with a given filename
 * @param coefs[] : the coefficients to save
 * 
 * Opens the file and saves each coefficient in it. */
void save_coefs(float coefs[]);



/** \brief Frees the memory relative to the population in argument
 * @param pop : pointer to a population structure */
void destroy_population(Population* pop);



/** \brief Gentic_algorithm : main function
 * 
 * Initializes a new population, makes each genome plays against k others, caculates their fitness, selects them using the biased wheel, makes them reproduce, mutates, and again over a defined number of 
 * generation. */
void genetic_algorithm();

#endif


