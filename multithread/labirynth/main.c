#include <omp.h>
#include <unistd.h>

#include "maze_gen.c"

#define SLEEP_TIME 1
#define WIDTH 5
#define HEIGHT 8

// char cell[HEIGHT * 2 + 1][WIDTH * 2 + 1] ={ 
// {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
// {-1,-1,0,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,0},
// {0,-1,0,0,-1,0,0,-1,0,-1,0,-1,0,-1,0,0,0,0,0,-1,0},
// {0,-1,-1,-1,-1,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,-1,-1,0},
// {0,0,0,-1,0,0,0,0,0,-1,0,-1,0,0,0,-1,0,0,0,0,0},
// {0,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0},
// {0,-1,0,-1,0,-1,0,-1,0,0,0,-1,0,-1,0,0,0,-1,0,-1,0},
// {0,-1,-1,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0},
// {0,0,0,0,0,-1,0,-1,0,0,0,-1,0,-1,0,-1,0,0,0,-1,0},
// {0,-1,0,-1,-1,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0},
// {0,-1,0,-1,0,0,0,-1,0,-1,0,0,0,-1,0,-1,0,-1,0,0,0},
// {0,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,0,-1,0,-1,-1,-1,0},
// {0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,0,0,0,-1,0,0,0,-1,0},
// {0,-1,-1,-1,0,-1,0,-1,0,-1,-1,-1,-1,-1,0,-1,0,-1,-1,-1,0},
// {0,-1,0,0,0,-1,0,-1,0,0,0,0,0,-1,0,-1,0,-1,0,0,0},
// {0,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,0,-1,0,-1,0},
// {0,-1,0,0,0,-1,0,0,0,-1,0,-1,0,0,0,-1,0,-1,0,-1,0},
// {0,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,0,-1,0},
// {0,-1,0,-1,0,-1,0,-1,0,0,0,0,0,0,0,-1,0,0,0,-1,0},
// {0,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
// {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

extern char **cell;
omp_lock_t **cross_lock;
extern int w, h;

static int size_h;
static int size_w;

static int stopflag = 0;
static int thread_id = 1;

const char *colors[] = {"\e[0m", "\e[1;31m", "\e[1;32m", "\e[1;33m","\e[1;34m", "\e[1;35m", "\e[1;36m","\e[1;37m"};

void print_map();
void walk_maze(int, int, int);
void find_start_in_maze(int *, int *);

int main()
{
	omp_set_num_threads(1024);
    gen_maze(WIDTH, HEIGHT);
	size_h = HEIGHT * 2 + 1;
	size_w = WIDTH * 2 + 1;

	cross_lock = malloc(sizeof(omp_lock_t *) * size_h);
	for(int i = 0; i < size_h; i++)
	{
		cross_lock[i] = malloc(sizeof(omp_lock_t) * size_h);
	}

	int start_h, start_w;
	find_start_in_maze(&start_h, &start_w);

	for (int i = 0; i < size_h; i++)
	{
		for (int j = 0; j < size_w; j++)
		{
			omp_init_lock(&cross_lock[i][j]);
		}
	}

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			print_map();
		}

		#pragma omp section
		{
			// walk_maze(thread_id, 1, 1);
			walk_maze(thread_id, start_h, start_w);
			// printf("We will do something here soon\n");
		}
	}

	print_map();

	return 0;
}

void find_start_in_maze(int *h, int *w)
{
	for (int i = 0; i < size_h; i++)
	{
		for (int j = 0; j < size_w; j++)
		{
			if(cell[i][j] == -1)
			{
				*h = i;
				*w = j;
				return;
			}
		}
	}
	
}

void walk_maze(int id, int start_x, int start_y)
{
	int tmp_h = start_x;
	int tmp_w = start_y;
	
	int cur_h;
	int cur_w;

	int set;

	int ways;

	while(1)
	{
		ways = 0;
		cur_h = tmp_h;
		cur_w = tmp_w;
		set = 0;
		if(cell[cur_h + 1][cur_w]==-1)
		{
			tmp_h++;
			ways++;
		}
		if(cell[cur_h][cur_w + 1]==-1)
		{
			if(ways < 1) tmp_w++;
			else
			{
				#pragma omp atomic
				thread_id++;

				#pragma omp task
				{
					walk_maze(thread_id, cur_h, cur_w + 1);
				}
			}
			ways++;
		} 
		if(cell[cur_h-1][cur_w]==-1)
		{
			if(ways < 1) tmp_h--;
			else
			{
				#pragma omp atomic
				thread_id++;

				#pragma omp task
				{
					walk_maze(thread_id, cur_h - 1, cur_w);
				}
			}
			ways++;
		}
		if(cell[cur_h][cur_w-1]==-1)
		{
			if(ways < 1) tmp_w--;
			else
			{
				#pragma omp atomic
				thread_id++;

				#pragma omp task
				{
					walk_maze(thread_id, cur_h, cur_w - 1);
				}
			}
			ways++;
		}

		#pragma omp flush(cross_lock)
		if (omp_test_lock(&cross_lock[cur_h][cur_w]))
		{
			// omp_set_lock(&cross_lock[tmp_h][tmp_w]);
			cell[cur_h][cur_w] = id;
			set = 1;
		}
		
		if (set == 0)
		{
			break;
		}
		
		
		sleep(SLEEP_TIME);
		if(ways == 0) break;
	}
	
	#pragma omp taskwait
}

void print_map()
{
	// printf("{");
	// printf("\e7");
	while(!stopflag)
	{
		for (int i = 0; i < size_h; i++)
		{
			// printf("{");
			for (int j = 0; j < size_w; j++)
			{
				if (cell[i][j] == 0)
				{
					printf("#");
				}
				else if (cell[i][j] == -1)
				{
					printf(" ");
				}
				else
				{
					printf("%sX%s", colors[cell[i][j] % 7 + 1], colors[0]);
				}

			}
			printf("\n");
		}
		printf("\e[%dA", HEIGHT * 2 + 1);
		printf("\e[%dD", WIDTH * 2);

		sleep(SLEEP_TIME);
	}
}