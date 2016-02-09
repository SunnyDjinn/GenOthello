/** \file genetic.c
 * Functions related to the genetic algorithm (used to determine the different coefficients of the evaluation function)
 * */

#include "genetic.h"

float random_tenth(short lowerBound, short upperBound) {
	float x;
	
	/* Random number between lowerBound and upperBound */
	x = (float)rand()/(float)(RAND_MAX/(float)(upperBound-lowerBound));
	x += (float)lowerBound;
	
	/* Rounding to the first tenth number */
	x *= (float)10;
	x = floorf(x);
	x/= (float)10;
	return x;
}


Population* initial_population(short genNb) {
	
	/* Allocating the population */
	Population* pop = malloc(sizeof(Population));
	pop->genomes = malloc(genNb * sizeof(Genome));
	short i, j;
	
	/* Filling with random coefficients */
	for(i=0; i<genNb; i++) {
		for(j=0; j<COEF_NB; j++) {
			/* Random number between 0 and MAX_COEF */
			pop->genomes[i].coefs[j] = random_tenth(0, MAX_COEF);
		}
		/* Initializing the fitness to 0 */
		pop->genomes[i].fitness = 0;
	}
	
	pop->genNb = genNb;
	return pop;
}


void fitness(Population* pop, short gameNb, FILE* f1) {
	short i, j;
	short opponentGen;
	/* The randomized color of the genome we are testing / it can be either black or white */
	short genColor = rand() % 2;
	
	/* For each genome in the population */
	for(i=0; i<pop->genNb; i++) {
		fprintf(f1, "\t\t*****Genome %d *****\n", i);
		
		/* Making it play against gameNb other genomes */
		for(j=0; j<gameNb; j++) {
			genColor = rand() % 2;
			
			/* Randomizing a number against which the genome will play / It cannot play against itself (useless) */
			do {
				opponentGen = rand() % pop->genNb;
			} while(i == opponentGen);
			
			/* Printing in the file and dsplaying on the screen */
			fprintf(f1, "\t\t\t\tGame n°%d\n", j);
			fprintf(f1, "\t\t\t\t%d joue contre %d\n", i, opponentGen);
			printf("\t\t\t\t%d joue contre %d\n", i, opponentGen);
			
			/* Initializing the game */
			Game* game = init_game();
			
			/* Making them play against each other */
			while(!end_of_game(game)) {
				if(game->turn == genColor)
					move_processing(game, UNKNOWN, min_max(YES, game, BLACK, GLOBAL_DEPTH, GLOBAL_DEPTH, SHRT_MIN, SHRT_MAX, pop->genomes[i].coefs));
				else
					move_processing(game, UNKNOWN, min_max(YES, game, WHITE, GLOBAL_DEPTH, GLOBAL_DEPTH, SHRT_MIN, SHRT_MAX, pop->genomes[opponentGen].coefs));
			}
			
			fprintf(f1, "\t\t\t\t\t\t Nombre de coups joués : %d", game->cursor);
			
			/* Updating the fitness */
			if(game->oth->piecesNb[BLACK] > game->oth->piecesNb[WHITE])
				pop->genomes[i].fitness += 1;
			fprintf(f1, "\t\t\t\tFitness : %d\n", pop->genomes[i].fitness);
			printf("\t\t\t\tFitness : %d\n", pop->genomes[i].fitness);
			
			/* Freeing the game */
			destroy_game(game);
		}
	}
}


Population* next_generation(Population* initial) {
	
	/* Initializing a new generation */
	Population* next = malloc(sizeof(Population));
	next->genomes = malloc(initial->genNb * sizeof(Genome));
	next->genNb = initial->genNb;
	
	/* Counting the sum of fitness and initializing the fitness to 0 */
	short i, j, k = 0, fitnessSum = 0;
	for(i=0; i<initial->genNb; i++) {
		fitnessSum += initial->genomes[i].fitness;
		next->genomes[i].fitness = 0;
	}
	
	/* Biased wheel */
	short biasedWheel[fitnessSum];
	/* Filling the wheel with the number of its genome, proportionnaly to its fitness */
	for(i=0; i<initial->genNb; i++)
		for(j=0; j<initial->genomes[i].fitness; j++)
			biasedWheel[k++] = i;
			
	/* Index for localizing children */		
	j = 0;
	/* Making the reproduction (and the mutation) n/2 times, so that we still have n children */
	for(i=0; i<initial->genNb/2; i++) {
		reproduction(initial, next, biasedWheel[rand()%fitnessSum], biasedWheel[rand()%fitnessSum], j, j+1);
		mutation(next, j);
		mutation(next, j+1);
		j += 2;
	}
	return next;
}


void reproduction(Population* initial, Population* next, short parentA, short parentB, short childA, short childB) {
	short i;
	short coef;
	short reproductionDifferences;
	
	/* For each coefficient */
	for(i=0; i<COEF_NB; i++) {
		/* Randomizing the parent who will give its coefficient */
		coef = rand()%2;
		
		/* Randomizing if there will be a difference in the genome */
		reproductionDifferences = rand()%2;
		
		/* Taking the coefficients from the parents */
		next->genomes[childA].coefs[i] = ((coef == 0) ? initial->genomes[parentA].coefs[i] : initial->genomes[parentB].coefs[i]);
		next->genomes[childA].coefs[i] += (reproductionDifferences == 0) ? random_tenth(0, 0.2) : -random_tenth(0, 0.2);
		reproductionDifferences = rand()%2;
		next->genomes[childB].coefs[i] = ((coef == 0) ? initial->genomes[parentB].coefs[i] : initial->genomes[parentA].coefs[i]);
		next->genomes[childB].coefs[i] += (reproductionDifferences == 0) ? random_tenth(0, 0.2) : -random_tenth(0, 0.2);
	}
}


void mutation(Population* next, short genomeToMutate) {
	/* Random number between 0 and 1 */
	short i;
	if(random_tenth(0, 1) <= MUT_FACTOR) {
		for(i=0; i<COEF_NB; i++)
			next->genomes[genomeToMutate].coefs[i] = random_tenth(0, MAX_COEF);
	}
}


short search_best_genome(Population* pop) {
	short maxFit;
	short bestGen;
	short i;
	maxFit = pop->genomes[0].fitness;
	bestGen = 0;
	
	/* Finding the genome which has the best fitness */
	for(i=1; i<GENOMES_NB; i++) {
		if(pop->genomes[i].fitness > maxFit)
			bestGen = i;
	}
	
	return bestGen;
}


void save_coefs(float coefs[]) {
	short i;
	FILE* f1 = fopen(COEFS_FILENAME, "w");
	
	/* It there was a problem during the opening */
	if(!f1) {
		perror("FILE : Error opening the file");
		exit(EXIT_FAILURE);
	}
	
	/* Saving the coefficients in a special file */
	for(i=0; i<COEF_NB; i++) {
		fprintf(f1, "%.1f\t", coefs[i]);
	}
	
	fclose(f1);
}


void destroy_population(Population* pop) {
	free(pop->genomes);
	free(pop);
}


void genetic_algorithm() {
	
	/* Initializing the random generator seed */
	srand(time(NULL));
	
	/* Créating an initial population */
	Population* initial = initial_population(GENOMES_NB);
	Population* next;
	short i, j, k;
	short bestGen;
	FILE* f1;
		
	/* Name of the saving file for the current generation */
	char filename[] = "GEN001.txt";
	
	/* For each generation */
	for(i=0; i<GENERATION_NB; i++) {
		
		/* Modifying the filename */
		filename[3] = i/100 + '0';
		filename[4] = (i/10)%10 + '0';
		filename[5] = i%10 + '0';
		
		/* Opening the file and printing information */
		f1 = fopen(filename, "w");
		fprintf(f1, "\n#####Génération n°%d#####\n", i);	
		printf("\n#####Génération n°%d#####\n", i);
		
		/* For each individual, displaying its coefficients  */
		for(j=0; j<GENOMES_NB; j++) {
			for(k=0; k<COEF_NB; k++)
				fprintf(f1, "%f ", initial->genomes[j].coefs[k]);
		}
		
		/* Calculating the fitness (making them play against each other) */
		fitness(initial, GAME_NB, f1);
		
		/* Creating the next generation */
		next = next_generation(initial);
		
		/* Finding the best genome */
		bestGen = search_best_genome(initial);
		
		fprintf(f1, "\n");
		
		/* Printing its coefficients */
		for(j=0; j<COEF_NB; j++)
			fprintf(f1, "%.1f\t", next->genomes[bestGen].coefs[j]);
		
		/* Closing the file, freeing the initial population */
		fclose(f1);
		destroy_population(initial);
		initial = next;
	}
	
	/* Saving the best coefficients at the end of the algotrithm */
	save_coefs(next->genomes[search_best_genome(next)].coefs);
	destroy_population(next);
}
