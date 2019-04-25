#define N_CHROMOSOM 24
#define POPULATION_SIZE 20000
//#define C_MAX 6
#define MAX_GENERATION 100

#define CROSS_DIVIDER 2//1 or 2
#define CROSS_CHANCE 5//from 5 to 10

#define TOURNAMENT_GROUP 3//must be less than POPULATION SIZE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <math.h>
typedef struct
{
	int value;
	int c_size;
}item;

typedef struct
{
	int * isholding;
	item * items;
	int fitness;
}individual;

individual * population = NULL;

int C_MAX = 0;

void selectstartingpopulation();
void evaluate();
individual checkbest(individual * group, int size);
float checkaverage();

void cross();
void evaluate();


void mutate();
void evaluate();

void roulette();
void tournament();
void ranked();

void sortpopulation();
int compare(const void * left, const void * right);

void knapsack();

void exportdata(float *, int *, int *, int, int);

item * itemlist = NULL;

int main()
{
	srand(time(NULL));
	knapsack();
	_getch();
}

void selectstartingpopulation()
{
	population = (individual *)malloc(sizeof(individual) * POPULATION_SIZE);
	int random = 0;
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		population[i].items = (item *)malloc(sizeof(item) * N_CHROMOSOM);
		population[i].isholding = (int *)malloc(sizeof(int) * N_CHROMOSOM);
		population[i].fitness = 0;
		
		for (int j = 0; j < N_CHROMOSOM; j++)
		{
			random = rand() % 5 + 1;
			population[i].items[j] = itemlist[j];
			if ((random) == 3) population[i].isholding[j] = 1;
			else population[i].isholding[j] = 0;
		}
	}
	/*for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < N_CHROMOSOM; j++) printf("individual[%d]: holding = %d\n", i, population[i].isholding[j]);
		printf("\n");
	}*/

	for (int i = 0; i < N_CHROMOSOM; i++)
	{
		C_MAX += itemlist[i].c_size;
	}
	C_MAX = C_MAX / 3;
}

void evaluate()
{
	int valuesum = 0;
	int weightsum = 0;
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		valuesum = 0;
		weightsum = 0;
		for (int j = 0; j < N_CHROMOSOM; j++)
		{
			if (population[i].isholding[j] == 1)
			{
				valuesum += population[i].items[j].value;
				weightsum += population[i].items[j].c_size;
			}
		}
		if (weightsum > C_MAX) population[i].fitness = 0;
		else population[i].fitness = valuesum;
	}
	//for (int i = 0; i < POPULATION_SIZE; i++)  printf("individual[%d]: fitness = %d\n", i, population[i].fitness);
}

individual checkbest(individual * group, int size)
{
	individual res = group[0];
	for (int i = 0; i < size; i++)
	{
		if (group[i].fitness > res.fitness) res = group[i];
	}
	/*
	individual * copy = (individual *)malloc(sizeof(individual) * size);
	memcpy(copy, group, size*sizeof(individual));//better safe than sorry
	qsort(copy, size, sizeof(individual), compare);
	individual res = copy[0];
	free(copy);
	*/
	return res;
}

int compare(const void * left, const void * right)
{
	individual * l = (individual *)left;
	individual * r = (individual *)right;
	if (l->fitness > r->fitness) return -1;
	if (l->fitness < r->fitness) return 1;
	return 0;
}

void sortpopulation()
{
	qsort(population, POPULATION_SIZE, sizeof(individual), compare);
}

void cross()
{
	int i, j, save, chance;
	individual * newpopulation = NULL;
	newpopulation = (individual *)malloc(sizeof(individual) * POPULATION_SIZE);
	int counter = 0;
	if (CROSS_DIVIDER == 1)
	{
		for (i = 0; i < POPULATION_SIZE; i++)
		{
			chance = rand() % 10 + 1;
			if (chance >= CROSS_CHANCE)
			{
				int divider_1 = rand() % (N_CHROMOSOM - 1) + 1;
				int random = rand() % POPULATION_SIZE;
				individual another = population[random];
				for (j = divider_1; j < N_CHROMOSOM; j++)
				{
					save = population[i].isholding[j];
					population[i].isholding[j] = another.isholding[j];
					another.isholding[j] = save;
				}
				newpopulation[counter++] = population[i];
				if (counter == POPULATION_SIZE) break;
				newpopulation[counter++] = another;
				if (counter == POPULATION_SIZE) break;
			}
		}
		for (i = counter; i < POPULATION_SIZE; i++)
		{
			newpopulation[i] = population[i];
		}
	}
	else if (CROSS_DIVIDER == 2)
	{
		for (i = 0; i < POPULATION_SIZE; i++)
		{
			chance = rand() % 10 + 1;
			if (chance >= CROSS_CHANCE)
			{
				int divider_1 = rand() % (N_CHROMOSOM - 1) + 1;
				int divider_2 = rand() % (N_CHROMOSOM - 1) + 1;
				if (divider_1 > divider_2)
				{
					save = divider_1;
					divider_1 = divider_2;
					divider_2 = save;
				}
				int random = rand() % POPULATION_SIZE;
				individual another = population[random];
				for (j = 0; j < divider_1; j++)
				{
					save = population[i].isholding[j];
					population[i].isholding[j] = another.isholding[j];
					another.isholding[j] = save;
				}
				for (j = divider_2; j < N_CHROMOSOM; j++)
				{
					save = population[i].isholding[j];
					population[i].isholding[j] = another.isholding[j];
					another.isholding[j] = save;
				}
				newpopulation[counter++] = another;
				if (counter == POPULATION_SIZE) break;
			}
		}
		for (i = counter; i < POPULATION_SIZE; i++)
		{
			newpopulation[i] = population[i];
		}
	}
	free(population);
	population = newpopulation;
	for (int i = 0; i < POPULATION_SIZE; i++) population[i] = newpopulation[i];

}

void mutate()
{
	int chance, j;
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (j = 0; j < N_CHROMOSOM; j++)
		{
			chance = rand() % 100 + 1;
			if (chance == 1)
			{
				if (population[i].isholding[j] == 1)population[i].isholding[j] = 0;
				else population[i].isholding[j] = 1;
			}
		}
	}
}

void roulette()
{
	int fitsum = 0, i;
	for (i = 0; i < POPULATION_SIZE; i++)
	{
		fitsum += population[i].fitness;
	}
	individual * newpopulation = NULL;
	newpopulation = (individual *)malloc(sizeof(individual) * POPULATION_SIZE);
	int index = 0, counter = 0, random;

	while(counter!=POPULATION_SIZE)
	{
		if (fitsum > 0)
		{		
			random = rand() % fitsum + 1;
			index = 0;
			for (i = 0; i < POPULATION_SIZE; i++)
			{
				index += population[i].fitness;
				if (random >= index)
				{
					newpopulation[counter++] = population[i];
					break;
				}
			}
		}
		else
		{
			index = rand() % POPULATION_SIZE;
			newpopulation[counter++] = population[index];
		}
	}
	free(population);
	population = newpopulation;

}

void tournament()
{
	individual * newpopulation = NULL;
	newpopulation = (individual *)malloc(sizeof(individual) * POPULATION_SIZE);
	individual * tournamentgroup = (individual *)malloc(sizeof(individual) * TOURNAMENT_GROUP);
	int index, i, counter = 0;
	individual bestguy;
	while (counter != POPULATION_SIZE)
	{
		for (i = 0; i < TOURNAMENT_GROUP; i++)
		{
			index = rand() % POPULATION_SIZE;
			tournamentgroup[i] = population[index];
		}
		bestguy = checkbest(tournamentgroup, TOURNAMENT_GROUP);
		newpopulation[counter] = bestguy;
		counter++;
	}
	//free(population);
	//population = newpopulation;
	for (int i = 0; i < POPULATION_SIZE; i++) population[i] = newpopulation[i];

}

void ranked()
{
	
	individual * newpopulation = NULL;
	newpopulation = (individual *)malloc(sizeof(individual) * POPULATION_SIZE);
	sortpopulation();
	int divider = 2;
	int counter = 0;
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < POPULATION_SIZE / divider; j++)
		{
			if (counter == POPULATION_SIZE)break;
			newpopulation[counter] = population[i];
			counter++;
		}
		if (counter == POPULATION_SIZE)break;
		divider = 4;//maybe we will have to change this
	}
	/*
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < N_CHROMOSOM; j++)
		{
			printf("individual\t[%d]: holding = %d\t newhold = %d", i, population[i].isholding[j], newpopulation[i].isholding[j]);
			printf("\n");

		}
		printf("\n");
	}
	*/
	/*
	free(population);
	population = newpopulation;
	
	individual * newpopulation = NULL;
	newpopulation = (individual *)malloc(sizeof(individual) * POPULATION_SIZE);

	sortpopulation();

	int first = round(POPULATION_SIZE / 2.0);
	int second = round(POPULATION_SIZE / 4.0);
	int third = round(POPULATION_SIZE / 8.0);
	int fourth = POPULATION_SIZE - (first+second+third);

	for (int i = 0; i < first; i++) newpopulation[i] = population[0];
	for (int i = first; i < first+second; i++) newpopulation[i] = population[1];
	for (int i = first + second; i < first + second + third; i++) newpopulation[i] = population[2];
	for (int i = first + second + third; i < first + second + third+fourth; i++) newpopulation[i] = population[3];

	free(population);
	population = newpopulation;
	*/
	//for(int i = 0; i < POPULATION_SIZE; i++) population[i] = newpopulation[i];
}

void knapsack()
{
	itemlist = (item *)malloc(sizeof(item) * N_CHROMOSOM);
	for (int i = 0; i < N_CHROMOSOM; i++)
	{
		itemlist[i].c_size = rand() % 50 + 1;
		itemlist[i].value = rand() % 200 + 1;
	}
	
	for (int i = 0; i < N_CHROMOSOM; i++)
	{
		printf("item[%d]: weight = %d\tvalue = %d\n", i, itemlist[i].c_size, itemlist[i].value);
	}

	selectstartingpopulation();
	evaluate();

	int gcount = 0;
	individual bestguy;
	int maxfitness = 0;
	float averages[MAX_GENERATION];
	int maxvars[MAX_GENERATION];

	int maxchanges[MAX_GENERATION];
	int maxcount = 0;
	while (1)
	{
		averages[gcount] = checkaverage();
		bestguy = checkbest(population, POPULATION_SIZE);
		if (bestguy.fitness > maxfitness)
		{
			maxfitness = bestguy.fitness;
			maxchanges[maxcount++] = maxfitness;
		}
		maxvars[gcount] = bestguy.fitness;
		if (++gcount == MAX_GENERATION) break;
		evaluate();
		tournament();
		cross();
		mutate();
		
	}
	bestguy = checkbest(population, POPULATION_SIZE);
	
	float meanaver = 0;
	float meanmax = 0;
	for (int i = 0; i < MAX_GENERATION; i++)
	{
		meanaver += averages[i];
		meanmax += maxvars[i];
	}
	meanaver = meanaver / MAX_GENERATION;
	meanmax = meanmax / MAX_GENERATION;
	printf("MEAN AVERAGE: %.2f\t MEAN MAX: %.2f\t MAX EVER = %d", meanaver, meanmax, maxfitness);
	for (int i = 0; i < maxcount; i++)
	{
		printf("zmiany: %d\n", maxchanges[i]);
	}
	exportdata(averages, maxvars, maxchanges, MAX_GENERATION, maxcount);
}

float checkaverage()
{
	int fitsum = 0, i;
	for (i = 0; i < POPULATION_SIZE; i++)
	{
		fitsum += population[i].fitness;
	}

	return (1.0f*fitsum) / POPULATION_SIZE;
}

void exportdata(float * average, int * max, int * maxchanges, int fbound, int mbound)
{
	FILE * f1 = fopen("avdderage.txt", "wt");
	FILE * f2 = fopen("max.txt", "wt");
	FILE * f3 = fopen("maxchanges.txt", "wt");
	if (!f1 || !f2 || !f3) printf("smutna buzia");
	float a;
	int b;
	for (int i = 0; i < fbound; i++)
	{
		a = average[i];
		b = max[i];
		fprintf(f1, "%.2f\n", a);
		fprintf(f2, "%d\n", b);
	}
	for (int i = 0; i < mbound; i++)
	{
		fprintf(f3, "%d\n", maxchanges[i]);
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);

}