#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <conio.h>

#define LINEAR 1
#define DOUBLE 2

#define HASH_SIZE 997
#define ARR_SIZE 2000

void init(int * arr);
int search(int key, int * arr, int type);
void insert(int key, int * arr, int type);
bool del(int key, int * arr);
inline int hash(int key);
inline int dhash(int key);
void show(int * arr, int, int);
void generate(int x, int * arr, int type);


int main()
{
	srand(time(NULL));

	int x, k1, k2, k3, k4;

	FILE * fp = fopen("inlab06.txt", "r");
	if (fp != NULL)
	{
		fscanf(fp, "%d %d %d %d %d", &x, &k1, &k2, &k3, &k4);
		fclose(fp);
	}

	clock_t start, stop;//, timelinear, timedouble;

	//int *hashtable = NULL;
	int hashtable[ARR_SIZE];


	start = clock();
	init(hashtable);
	del(k1, hashtable);
	insert(k1, hashtable, LINEAR);

	show(hashtable, 0, 100);
	generate(x, hashtable, LINEAR);
	show(hashtable, 0, 100);
	insert(k2, hashtable, LINEAR);
	insert(k3, hashtable, LINEAR);
	insert(k4, hashtable, LINEAR);
	show(hashtable, 500, 600);
	del(k3, hashtable);
	del(k4, hashtable);
	show(hashtable, 0, 100);
	show(hashtable, 500, 600);
	stop = clock();
	//timelinear = stop - start;
	printf("Czas trwania z adresowaniem liniowym: %lu ms\n", (stop - start));
	_getch();

	start = clock();
	init(hashtable);
	del(k1, hashtable);
	insert(k1, hashtable, DOUBLE);
	show(hashtable, 0, 100);
	generate(x, hashtable, DOUBLE);
	show(hashtable, 0, 100);
	insert(k2, hashtable, DOUBLE);
	insert(k3, hashtable, DOUBLE);
	insert(k4, hashtable, DOUBLE);
	show(hashtable, 500, 600);
	del(k3, hashtable);
	del(k4, hashtable);
	show(hashtable, 0, 100);
	show(hashtable, 500, 600);
	stop = clock();
	//timelinear = stop - start;
	printf("Czas trwania z adresowaniem liniowym: %lu ms\n", (stop - start));
	_getch();
}

void init(int * arr)
{
	//arr = (int *)malloc(sizeof(int) * ARR_SIZE);
	for (int i = 0; i < ARR_SIZE; i++)
	{
		arr[i] = 0;
	}
}

void generate(int x, int * arr, int type)
{
	int rng;// = rand() % 20001 + 20000;
	int flag;// = -1;
	for (int i = 0; i < x; i++)
	{
		do
		{
			rng = rand() % 20001 + 20000;
			flag = search(rng, arr, type);
		} while (flag != -1);
		insert(rng, arr, type);
	}
}

int search(int key, int * arr, int type)//-1 jak nie ma
{
	/*for (int i = 0; i < ARR_SIZE; i++)
	{
		if (arr[i] == key)
		{
			return i;//zwraca indeks
		}
	}
	return -1;//nie znalazlow*/
	int hashed = hash(key);
	int additional = 0;
	if (type == LINEAR)
	{
		while (arr[hashed + additional] != key)
		{
			additional++;
			if (hashed + additional >= ARR_SIZE) return -1;
		}
		return hashed + additional;
	}
	if (type == DOUBLE)
	{
		while (arr[hashed + additional] != key)
		{
			if (hashed + additional >= ARR_SIZE) return -1;
			additional = additional + dhash(key);
		}
		return hashed + additional;
	}
}

void insert(int key, int * arr, int type)
{
	int hashed;
	int additional = 0;
	if (type == LINEAR)
	{
		//additional = 0;
		hashed = hash(key);
		while (arr[hashed + additional] != 0 || arr[hashed + additional] == -1)
		{
			additional++;
		}
		arr[hashed + additional] = key;
	}
	if (type == DOUBLE)
	{
		hashed = hash(key);
		while (arr[hashed + additional] != 0 || arr[hashed + additional] == -1)
		{
			additional = additional + dhash(key);
		}
		arr[hashed + additional] = key;
	}
	//return true;
}

bool del(int key, int * arr)
{
	for (int i = 0; i < ARR_SIZE; i++)
	{
		if (arr[i] == key)
		{
			arr[i] = -1;
			return true;
		}
	}
	printf("Nie znaleziono klucza\n");
	return false;
}

inline int hash(int key)
{
	//if (key == 0 || HASH_SIZE%key) return 0;
	int hold = (int) pow(2, key % 10);
	int retval = ((key % 1000) + hold + 1) % HASH_SIZE;
	return retval;
}

inline int dhash(int key)
{
	return (((3 * key) % 19) + 1);
}

void show(int * arr, int startpos, int endpos)
{
	if (startpos > ARR_SIZE || endpos > ARR_SIZE)
	{
		printf("nie moszna\n");
		return;
	}
	for (int i = startpos; i < endpos; i++)
	{
		printf("tab[%d] = %d ", i, arr[i]);
		if (i % 3 == 0) printf("\n");
	}
}
