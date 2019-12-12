#include <stdio.h>
#include <math.h> 
#include <omp.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 2187
#define BLOCK_SIZE(x) (x / 2)
#define MAX_COLOR_VAL 255
#define MAX_NUM_OF_THREADS 16
#define max(x,y) ((x) > (y) ? (x) : (y))

#define NR_OF_THREADS 4

#define _COUNT_LOOPS_

#define BLACK 0
#define WHITE 255

#define LEVEL_MAX	7

FILE * fp;

unsigned char ppm_arr[SIZE][SIZE];
int atomic_cnt;

void recursive_carpet(int i, int j, int level);
//size = SIZE/3^l

void fill_middle(int _i, int _j, int size)
{
	for(int i = _i; i < (_i + size); i++)
	{
		for(int j = _j; j < (_j + size); j++)
		{
			ppm_arr[i][j] = WHITE;
		}
	}
}

int main()
{
	char *filename="spiral.ppm";

	fp= fopen(filename,"wb"); /* b -  binary mode */

	fprintf(fp,"P6\n # \n %d\n %d\n %d\n", SIZE, SIZE, MAX_COLOR_VAL);

	double start_time, end_time;

	start_time = omp_get_wtime();

	end_time = omp_get_wtime();
	printf("time: %.6f\tnr of threads: %d\n", (end_time - start_time), 1);

	recursive_carpet(0,0, 1);

	for (int y = 0; y < SIZE; y++)
	{
	    for (int x=0; x < SIZE; x++)
	    {
			fwrite(&ppm_arr[y][x], 1, 1, fp);
			fwrite(&ppm_arr[y][x], 1, 1, fp);
			fwrite(&ppm_arr[y][x], 1, 1, fp);
	    }
	}
	fclose(fp);
	return 0;
}

void recursive_carpet(int _i, int _j, int level)
{
	int size = SIZE / pow(3.0,level);
	printf("_i = %d\t_j = %d\tlevel = %d\tsize = %d\n", _i, _j, level, size);
	fill_middle(_i + size, _j+size, size);
	if (level < LEVEL_MAX)
	{
		for (int i=0; i<9; i=i+1)
		{
			if(i == 4) continue;
			#pragma omp task
         	recursive_carpet(_i+(i%3)*size, _j+(i/3)*size, level + 1);
		}
	}

	#pragma omp taskwait
}