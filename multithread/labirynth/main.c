#include <omp.h>

#include "maze_gen.c"


extern char **cell;
extern int w, h;

static int size_h;
static int size_w;

#define sleep_time 300 // CZAS
#define WIDTH 5
#define HEIGHT 8

void print_map();

// int threadid = 1; // glopbalna zmienna watku
// int posx=0; //pozycja startowa
// int posy=1;
// int stopflag = 0;
// const char *colors[] = {"\e[1;31m", "\e[1;32m", "\e[1;33m","\e[1;34m", "\e[1;35m", "\e[1;36m","\e[1;37m"};
// const int h=21; //rozmiar planszy
// const int w=21;
// mutex mutexplansza[h][w]; //mutex na miejsce w planszy

// void threadsafeadd() // mutexowanie id watku
// {
// 	threadidmutex.lock();
// 	threadid++;
// 	threadidmutex.unlock();
// }

// void rysujPlansze()
// {
// 	while(stopflag == 0)
// 	{
// 		system("cls");
// 		for (int i = 0; i < h; i++)
// 		{
// 			for (int j = 0; j < w; j++)
// 				switch (plansza[i][j])
// 				{
// 					case 0:{ printf("\e[1;47m"); cout <<"  "; printf("\e[0m"); break;} 
// 					case -1: cout <<"  ";  break;
// 					default: { printf("%s", colors[plansza[i][j]% 7] ); cout <<"X"<<" "; printf("\e[0m"); break; }
// 				}
// 			cout << endl;
// 		}
// 		this_thread::sleep_for(chrono::milliseconds(sleep_time)); 
// 	}
// }

// void rusz(int id, int starty, int startx)
// {
// 	vector<thread *> threads; //wektor watkow
// 	int tempx,tempy;
// 	int FatherPosX = startx;
// 	int FatherPosY = starty;
// 	int ways; //ilosc rozwidlen
	
// 	while(1)
// 	{
// 		ways = 0;
// 		tempx=FatherPosX, tempy=FatherPosY;
		
// 		if(plansza[FatherPosY+1][FatherPosX]==-1)
// 		{
// 			tempy++;
// 			ways++;
// 		}
// 		if(plansza[FatherPosY][FatherPosX+1]==-1)
// 		{
// 			if(ways < 1) tempx++;
// 			else
// 			{
// 				threadsafeadd();
// 				threads.push_back(new thread(rusz, threadid, FatherPosY, FatherPosX+1));
// 			}
// 			ways++;
// 		} 
// 		if(plansza[FatherPosY-1][FatherPosX]==-1)
// 		{
// 			if(ways < 1) tempy--;
// 			else
// 			{
// 				threadsafeadd();
// 				threads.push_back(new thread(rusz, threadid, FatherPosY - 1, FatherPosX));
// 			}
// 			ways++;
// 		}
// 		if(plansza[FatherPosY][FatherPosX-1]==-1)
// 		{
// 			if(ways < 1) tempx--;
// 			else
// 			{
// 				threadsafeadd();
// 				threads.push_back(new thread(rusz, threadid, FatherPosY, FatherPosX-1));
// 			}
// 			ways++;
// 		}
		
// 		if(mutexplansza[FatherPosY][FatherPosX].try_lock()) plansza[FatherPosY][FatherPosX] = id;
// 		else break;
		
// 		FatherPosX = tempx;
// 		FatherPosY = tempy;
		
// 		this_thread::sleep_for(chrono::milliseconds(sleep_time));
// 		if(ways == 0) break;					
// 	} 
		
// 	for(auto &i : threads) //joinujemy watki
// 	{
// 		i->join();
// 		delete i;
// 	}
// }

int main()
{
    gen_maze(WIDTH, HEIGHT);
	size_h = HEIGHT * 2 + 1;
	size_w = WIDTH * 2 + 1;

	print_map();

	return 0;
}

void print_map()
{
	// printf("{");
	for (int i = 0; i < size_h; i++)
	{
		// printf("{");
		for (int j = 0; j < size_w; j++)
		{
			printf("%d\t", cell[i][j]);
		}
		printf("\n");
	}
	// printf("};");
}