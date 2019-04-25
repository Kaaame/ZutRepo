#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <conio.h>

struct dlist
{
	dlist * next;
	dlist * prev;
	int key;
	double fnum;
	char c;
};

struct dlist * head = NULL;
int keys[99900];

bool isEmpty();
bool checkKey(int key);
bool showstart(int number);
bool delelement(int key);
bool showend(int number);
bool deletelist();

void addelement(int key, double fnum, char c);
void randomize(int number);
void showelements();

struct dlist * findlast();
struct dlist * findbykey(int key);
struct dlist * returnkey(int key);

int main()
{
	srand(time(NULL));

	int x, k1, k2, k3, k4, k5;
	double timet;
	double rand = 0.1;
	clock_t start, stop;
	FILE * fp = fopen("inlab02.txt", "r");
	fscanf(fp, "%d %d %d %d %d %d", &x, &k1, &k2, &k3, &k4, &k5);
	fclose(fp);

	start = clock();

	for (int i = 0; i <= 99900; i++) keys[i] = 0;//inicjalizacja tablicy

	returnkey(k1);

	_getch();

	randomize(x);
	showelements();
	_getch();
	showstart(20);
	_getch();
	addelement(k2, rand, 'T');
	showelements();

	showstart(20);
	addelement(k3, rand, 'T');
	showelements();
	addelement(k4, rand, 'T');
	showstart(20);
	_getch();
	addelement(k5, rand, 'T');
	delelement(k3);
	showstart(20);
	delelement(k2);
	showstart(20);
	delelement(k5);
	showelements();
	checkKey(k5);
	showend(11);
	deletelist();
	showend(11);
	showelements();
	_getch();
	stop = clock();
	timet = (stop - start) / CLOCKS_PER_SEC;
	printf("Czas trwaania %d", timet);

}

bool isEmpty()
{
	return head == NULL;
}

void addelement(int key, double fnum, char c)
{
	struct dlist * link = (struct dlist *) malloc(sizeof(struct dlist));
	link->key = key;
	link->fnum = fnum;
	link->c = c;
	//keys[key - 99] = 1;
	if (isEmpty())
	{
		head = link;
		head->prev = head;
		head->next = head;
	}
	else
	{
		struct dlist * hold = findbykey(key);
		//struct dlist * hold = returnkey(key)->prev;
		//struct dlist * hold = returnkey(key)->prev;
		//if (head->next == head) hold = head;
		struct dlist * newhold = hold->next;
		hold->next = link;
		link->prev = hold;
		link->next = newhold; //trzeba prev w nastepnym ustawic na link
		newhold->prev = link;
	}
}

struct dlist * findlast()
{
	//struct dlist * link = head;
	if (head == NULL) return NULL;
	/*if (head->next == head) return head;
	while (link->next != head)
	{
		link = link->next;
	}
	return link;*/
	struct dlist * link = head;
	return link->prev;

}

struct dlist * findbykey(int key)//jako arr podac tablice keys ;oooooooooooooooo, zakladam, ze podany klucz jest nie zajety, czyli wczesniej sprawdzamy, zwraca poprzedni o jeden xD
{

	//struct dlist * link = returnkey(key);
	//link = link->prev;
	/*while (link->next != head)
	{
		if (link->key == lastkey) break;
		link = link->next;
	}*/
	struct dlist * link = head;
	if (head == NULL) return NULL;
	if (head->next == head) return head;
	while (link->key < key)
	{
		if (link->next == head) {
			break;
		}
		link = link->next;
	}

	return link;
}

void randomize(int number)
{
	for (int i = 0; i < number; i++)
	{
		int genkey = rand() % 99900 + 99;
		while (checkKey(genkey))
		{
			genkey = rand() % 99900 + 99;
		}
		double gendoub = rand() % 1000;
		char c = 'T';
		addelement(genkey, gendoub, c);
	}
}

bool checkKey(int key)
{
	//key = key-99;
	//return keys[key-99];// jezeli 1 to klucz istnieje wiec true, wiec trzeba odrzucic
	struct dlist * link = head;
	if (head == NULL)
	{
		return false;
	}
	while (link->next != head)
	{
		if (link->key == key) return true;
		link = link->next;
	}
	return false;
}

struct dlist * returnkey(int key)
{
	struct dlist * link = head;
	if (head == NULL)
	{
		printf("nie ma elementow\n");
		return NULL;
	}
	if (head->next == head)
	{
		printf("jeden element\n");
		return head;
	}
	while (link->next != head)
	{
		if (link->key == key) return link;
		link = link->next;
	}
}

bool delelement(int key)
{
	if (!checkKey(key))
	{
		printf("nie ma klucza.\n");
		return false;
	}
	else
	{
		if (head == NULL) return false;
		if (head->next == head)
		{
			//keys[head->key - 99] = 0;
			struct dlist * beingdeleted = head->next;
			free(head);
			head = beingdeleted;
			return true;
		}
		struct dlist * beingdeleted = returnkey(key);
		struct dlist * prevhold, * nexthold;
		prevhold = beingdeleted->prev;
		nexthold = beingdeleted->next;
		//keys[beingdeleted->key - 99] = 0;
		free(beingdeleted);//usuwanie
		prevhold->next = nexthold;
		nexthold->prev = prevhold;
	}
}

bool showstart(int number)
{
	if (head == NULL) return false;
	if (head->next == head)
	{
		printf("klucz = %d\n", head->key);
		return true;
	}
	struct dlist * link = head;
	for (int i = 0; i < number; i++)
	{
		printf("%d\t", link->key);
		link = link->next;
		if (link == head) return true;
	}

	printf("\n");
}

bool showend(int number)
{
	if (head == NULL) return false;
	if (head->next == head)
	{
		printf("klucz = %d\n", head->key);
		return true;
	}
	struct dlist * link = findlast();
	if (link == NULL) return true;
	for (int i = 0; i < number; i++)
	{
		if (link == head) return true;
		printf("klucz = %d\t", link->key);
		link = link->prev;
	}
	printf("\n");
}

void showelements()
{
	int counter = 0;

	if (head == NULL)
	{
		printf("\nBrak elementow\n");
		return;
	}
	if (head->next == head)
	{
		printf("\nNa liscie znajduje sie jeden element\n");
		return;
	}
	struct dlist * link = head;
	while (link->next != head)
	{
		counter++;
		link = link->next;
	}

	printf("\nna liscie znajduje sie %d elementow", counter);
}

bool deletelist()
{
	if (head == NULL) return false;
	if (head->next == head)
	{
		free(head);
		return true;
	}
	struct dlist * link = head;
	struct dlist * hold = NULL;
	while (link->next != head)
	{
		hold = link->next;
		free(link);
		link = hold;
	}
	free(hold);
	head = NULL;
}
