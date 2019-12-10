#include <stdio.h>
#include <math.h> 
#include <omp.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 801
#define BLOCK_SIZE(x) (x / 2)
#define MAX_COLOR_VAL 255
#define MAX_NUM_OF_THREADS 16
#define max(x,y) ((x) > (y) ? (x) : (y))

#define NR_OF_THREADS 4

#define _COUNT_LOOPS_
#define NESTED

FILE * fp;

unsigned char ppm_arr[SIZE][SIZE];
int values[SIZE][SIZE];


int isprime(int, int *);
int ulam_get_map(int, int, int);

static unsigned char thread_colors[MAX_NUM_OF_THREADS + 1][3] =
{
	{0,0,0},
	{0,0,255},
	{0,255,0},
	{255, 0, 0},
	{103,99,119},
	{225,248,114},
	{206,60,16},
	{29,137,2},
	{255,255,255},
	{23,122,255},
	{132,255,4},
	{255, 48, 20},
	{112, 20, 119},
	{200, 70, 70},
	{7, 206, 46},
	{44,137,70},
	{255, 30 ,111}
};

int main()
{

	char *filename="spiral.ppm";

	fp= fopen(filename,"wb"); /* b -  binary mode */

	fprintf(fp,"P6\n # \n %d\n %d\n %d\n", SIZE, SIZE, MAX_COLOR_VAL);

	double start_time, end_time;

	start_time = omp_get_wtime();

	int ptid;
	#ifdef _COUNT_LOOPS_
	int atomic_cnt = 0;
	#endif
	omp_set_nested(1);

	#pragma omp parallel\
			private(ptid)\
			num_threads(4)
	{
		ptid = omp_get_thread_num();

		int no_threads = omp_get_num_threads();
		printf("no_threads = %d\n", no_threads);

		//i			0		400		0		400
		//iend		400		800		400		800
		//j			0		0		400		400
		//jend		400		400		800		800
		
		int i_start, i_end, j_start, j_end;

		i_start = (ptid % 2) * BLOCK_SIZE(SIZE);
		i_end = i_start + BLOCK_SIZE(SIZE);

		j_start = (ptid/2) * BLOCK_SIZE(SIZE);
		j_end = j_start + BLOCK_SIZE(SIZE);
		printf("ptid = %d\ti_start = %d\ti_end = %d\tj_start = %d\tj_end = %d\n",
				ptid, i_start, i_end, j_start, j_end);
		#ifndef NESTED
		{
			for(int i = i_start; i < i_end; i++)
			{
				for(int j = j_start; j < j_end; j++)
				{
					#ifdef _COUNT_LOOPS_
					#pragma omp atomic
					atomic_cnt++;
					#endif
				
					// printf("ptid= %d i=%d j=%d\n",ptid, i,j);
					// printf("is=%d js=%d\n",i_start,j_start);
					// printf("ie=%d je=%d\n\n",i_end,j_end);


					// if(i <= i_end && i >= i_start &&
					// 	j <= j_end && j >= j_start)
					// {
						ppm_arr[i][j] = ptid + 1;
						if(isprime(ulam_get_map(i,j, SIZE), &values[i][j]))
						{
							
							ppm_arr[i][j] = 0;
						}
					// }
				}
			}
		}
		#endif
		#ifdef NESTED
		{
			int block = BLOCK_SIZE(SIZE);
			#pragma omp parallel\
					num_threads(4)\
					firstprivate(ptid, i_start, i_end, j_start, j_end)\
					shared(block)
			{
				int ctid = omp_get_thread_num();
				int ci_start, ci_end, cj_start, cj_end;

				// #pragma omp critical
				// {
					#ifdef _COUNT_LOOPS_
					#pragma omp atomic
					atomic_cnt++;
					#endif
					
					//eg		i 400 800; j 400 800
					//ci		400 600	400	600
					//ci_end	600	800	600	800
					//cj		400	400	600	600
					//cj_end	600	600	800	800

					ci_start = i_start + (ctid % 2) * BLOCK_SIZE(block);
					ci_end = ci_start + BLOCK_SIZE(block);

					cj_start = j_start + (ctid/2) * BLOCK_SIZE(block);
					cj_end = cj_start + BLOCK_SIZE(block);

					printf("ptid = %d\t ctid = %d\n", ptid, ctid);
					printf("cis=%d cie=%d\tcjs=%d cje=%d\n",
							ci_start, ci_end, cj_start, cj_end);
					printf("is=%d ie=%d\tjs=%d je=%d\n\n",
							i_start, i_end, j_start, j_end);
				// }
				//#pragma omp parallel for collapse(2) ordered
				for(int i = ci_start; i < ci_end; i++)
				{
					for(int j = cj_start; j < cj_end; j++)
					{
						#ifdef _COUNT_LOOPS_
						#pragma omp atomic
						atomic_cnt++;
						#endif

						// if(i <= ci_end && i >= ci_start &&
						// 	j <= cj_end && j >= cj_start)
						// {
							ppm_arr[i][j] = ctid + ptid * no_threads + 1;
							if(isprime(ulam_get_map(i,j, SIZE), &values[i][j]))
							{
								ppm_arr[i][j] = 0;
							}
						// }
					}
				}
			}
		}
		#endif
	}

	#ifdef _COUNT_LOOPS_
	printf("atomic_cnt = %d\n", atomic_cnt);
	//assert(atomic_cnt == SIZE * SIZE * 4);
	#endif

	end_time = omp_get_wtime();
	printf("time: %.6f\tnr of threads: %d\n", (end_time - start_time), 1);

	//#pragma omp parallel for collapse(2) ordered
	for (int y = 0; y < SIZE; y++)
	{
	    for (int x=0; x < SIZE; x++)
	    {
			fwrite(&thread_colors[ppm_arr[y][x]], 1, 3, fp);
	    }
	}
	fclose(fp);
	return 0;
}

int ulam_get_map(int x, int y, int n)
{
    x -= (n - 1) / 2;
    y -= n / 2;
 
    int mx = abs(x), my = abs(y);
    int l = 2 * max(mx, my);
    int d = y >= x ? l * 3 + x + y : l - x - y;
 
    return pow(l - 1, 2) + d;
}

int isprime(int n, int *p)
{
	for ((*p) = 2; (*p)*(*p) <= n; (*p)++)
		if (n%(*p) == 0) return 0;
	return n > 2;
}