#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdbool>
#include <ctype.h>
#include <conio.h>

#define LINE_MAX 1000

struct dlist
{
	dlist * next;
	dlist * prev;
	char * name;
	char * surname;
	char * sex;
	int age;
	unsigned long long nin;
};


struct dlist * head = NULL;
struct dlist * last = NULL;
struct dlist * sorthead = NULL;
struct dlist * sortlast = NULL;
struct dlist * current = NULL;


//logika tablicy
bool isEmpty();
int length();
void addelement();
void addFirst(char * name, char * surname, char * sex, int age, unsigned long long nin);
void addLast(char * name, char * surname, char * sex, int age, unsigned long long nin);
void addelementfile(char * name, char * surname, char * sex, int age, unsigned long long nin);
bool deleteperson(); 
void freestruct(struct dlist * delstruct);


//do posortowania
void sortlist();
bool issortEmpty();
void addsortFirst(char * name, char * surname, char * sex, int age, unsigned long long nin);
void addsortLast(char * name, char * surname, char * sex, int age, unsigned long long nin);//to samo co glowna tylko rozne listy, jestem leniwy
void addsortelement(char * name, char * surname, char * sex, int age, unsigned long long nin);


//dane z tablic
void displaydata();
void displaydatabackward();
bool findperson();
char * readline(const char * prompt);

//pliki
bool savelist();
bool loadlist();

void menu();

int main()
{
	menu();
	//_getch();
}

void displaydata()
{
	struct dlist * current = head;
	while (current != NULL)
	{
		printf("\n%s %s, %s, lat %i, pesel: %llu", current->name, current->surname,
			current->sex, current->age, current->nin);
		current = current->next;
	}
	fflush(stdout);
}

void displaydatabackward()
{
	struct dlist * current = last;
	while (current != NULL)
	{
		printf("\n%s %s, %s, lat %i, pesel: %llu", current->name, current->surname,
			current->sex, current->age, current->nin);
		current = current->prev;
	}
	fflush(stdout);
}

int length()
{
	int len = 0;
	struct dlist * current = NULL;
	for (current = head; current != NULL; current = current->next) len++;
	return len;
}

bool isEmpty()
{
	return head == NULL;
}

char * readline(const char * prompt)
{
	//uzywa malloc, ale byc moze razem ze struktura jest usuwaneXD
	fflush(stdin);
	char * hold;
	char c='\0';
	int counter = 0;

	size_t size = 20;
	hold = (char *)malloc(sizeof(char) * size);
	memset(hold, '\0', sizeof(size));
	printf("%s\n", prompt);
	do
	{
		//scanf("%c", &c);
		c = getchar();
		hold[counter++] = c;
		if (counter == size) hold = (char *)realloc(hold, sizeof(char) * (size*= 2));
	} while (c != '\r' && c != '\n');// no to to jest pomysl XD
	//hold = (char *)realloc(hold, sizeof(char) * (size *= 2)
	hold[counter-1] = '\0';
	return hold;
}

void addelement()
{
	//struct dlist * current = last;
	//struct dlist * hold = (dlist *)malloc(sizeof(dlist));
	fflush(stdin);
	char * name = "";
	char * surname;
	char * sex;
	int age;
	unsigned long long nin;
	//hold->key = current->key + 1;
	//name = readline("Podaj imie: ");
	if ((*name == '\n') || *name == '\0') { //wraz z wprowadzeniem menu, te zabiegi moga przestac miec sens
		name = readline("Zostana dodane nowe dane, wcisnij enter.");
		//for (int i =0;i<30;i++)	printf("\n");
		name = readline("Podaj imie: "); 
	}
	else name = readline("Podaj imie: ");
	surname = readline("Podaj nazwisko: ");
	sex = readline("Podaj plec: ");
	printf("Podaj wiek: \n");
	scanf(" %i", &age);
	printf("Podaj PESEL: \n");
	scanf(" %llu", &nin);
	/*if (isEmpty())
	{
		addFirst(name, surname, sex, age, nin);
	}
	else
	{
		addLast(name, surname, sex, age, nin);
	}*/
	addelementfile(name, surname, sex, age, nin);
	/*free(name);
	free(surname);
	free(sex);*/
}

void addFirst(char * name, char * surname, char * sex, int age, unsigned long long nin)//generalnie private
{
	struct dlist * link = (struct dlist *) malloc(sizeof(struct dlist));
	//link->key = key;
	link->name = name;
	link->surname = surname;
	link->sex = sex;
	link->age = age;
	link->nin = nin;

	last = link;

	link->next = head;
	head = link;
	head->next = NULL;
	head->prev = NULL;
}

void addLast(char * name, char * surname, char * sex, int age, unsigned long long nin)//generalnie private
{
	struct dlist * link = (struct dlist *) malloc(sizeof(struct dlist));

	link->name = name;
	link->surname = surname;
	link->sex = sex;
	link->age = age;
	link->nin = nin;
	
	last->next = link;
	link->prev = last;

	last = link;
	last->next = NULL;
}

bool findperson()
{
	struct dlist * current = head;
	char * hold = "";
	if ((*hold == '\n') || *hold == '\0') { //wraz z wprowadzeniem menu, te zabiegi moga przestac miec sens
		hold = readline("\nZostana wyszukane dane. Wcisnij enter\n");
		//for (int i = 0; i<30; i++)	printf("\n");
		hold = readline("Podaj szukane nazwisko");
	}
	else hold = readline("Podaj szukane nazwisko");
	while (current != NULL)
	{
		/*printf("\n%s %s, %s, lat %i, pesel: %llu", current->name, current->surname,
			current->sex, current->age, current->nin);*/

		if (!strcmp(hold, current->surname))
		{
			printf("\nZnaleziono wpis\n");
			printf("\n%s %s, %s, lat %i, pesel: %llu", current->name, current->surname,
				current->sex, current->age, current->nin); 
			return true;
		}
		current = current->next;
	}
	
	printf("\nNie znaleziono danej osoby.\n");
	fflush(stdout);
	return false;
}

bool deleteperson()//przez to ze mam globalne zmienne chyba nie trzeba uzywac struct dlist ** xD
{
	
	struct dlist * current = head;
	struct dlist * previous = NULL;
	struct dlist * delstruct = NULL;

	char * hold = "";
	if ((*hold == '\n') || *hold == '\0') { //wraz z wprowadzeniem menu, te zabiegi moga przestac miec sens
		hold = readline("Zostanie usuniety wpis. Wcisnij enter.\n");
		//for (int i = 0; i<30; i++)	printf("\n");
		hold = readline("Podaj nazwisko");
	}
	else hold = readline("Podaj nazwisko");
	if (current == NULL) return false;
	if (hold == NULL) return false;
	while (strcmp(current->name, hold) != 0)//przejdz przez liste
	{
		if (current->next == NULL)
		{
			free(hold);
			return false;
		}
		else
		{
			previous = current;
		}
		current = current->next;
	}//sprawdz gdzie sie znajduje
	if (current == head)
	{
		delstruct = head;
		head = head->next;
		//if(&((*delstruct)->name)!= NULL)freestruct(delstruct);
	}
	else
	{
		delstruct = current->prev->next;
		current->prev->next = current->next;
		//if ((*delstruct) != NULL)freestruct(delstruct);

	}

	if (current == last)
	{
		delstruct = last;
		last = current->prev;
		//if ((*delstruct) != NULL)freestruct(delstruct);

	}
	else
	{
		delstruct = current->next->prev;
		current->next->prev = current->prev;
		//if ((*delstruct) != NULL)freestruct(delstruct);
	}
	freestruct(delstruct);
	free(hold);
/*#ifndef xd
	delstruct = current;
	if ((*delstruct) == NULL || head == NULL) return true;
	if (head == (*delstruct)) head = (*delstruct)->next;
	if ((*delstruct)->next != NULL) (*delstruct)->next->prev = (*delstruct)->next;
	if ((*delstruct)->prev != NULL) (*delstruct)->prev->next = (*delstruct)->next;
	free((*delstruct));
#endif // !1*/

	return true;
}

bool savelist()
{
	struct dlist * current = head;
	char * hold = "";
	FILE * pfile;
	if ((*hold == '\n') || *hold == '\0') { //wraz z wprowadzeniem menu, te zabiegi moga przestac miec sens
		hold = readline("\nLista zostanie zapisana. Wcisnij enter.\n");
		//for (int i = 0; i<30; i++)	printf("\n");
		hold = readline("Podaj nazwe pliku");
	}
	else hold = readline("Podaj nazwe pliku");
	pfile = fopen(hold, "w");
	if (pfile == NULL)
	{
		printf("Nie udalo sie utworzyc pliku.\n");
		return false;
	}
	while (current != NULL)
	{

		fprintf(pfile, "%s;%s;%s;%i;%llu\n", current->name, current->surname,
			current->sex, current->age, current->nin);
		current = current->next;
	}
	fclose(pfile);
	return true;
}

bool loadlist()//cos nie dziala
{
	//struct dlist * current = head;
	char * hold = "";
	char buffer[LINE_MAX];
	FILE * pfile;
	
	char * name = "";
	char * surname;
	char * sex;
	int age;
	unsigned long long nin;
	if ((*hold == '\n') || *hold == '\0') { //wraz z wprowadzeniem menu, te zabiegi moga przestac miec sens
		hold = readline("\nLista zostanie wczytana. Wcisnij enter.\n");
		//for (int i = 0; i<30; i++)	printf("\n");
		hold = readline("Podaj nazwe pliku");
	}
	else hold = readline("Podaj nazwe pliku");
	pfile = fopen(hold, "r");
	if (pfile == NULL)
	{
		printf("Nie udalo sie utworzyc pliku.\n");
		return false;
	}
	
	int i = 0;
	while (fgets(buffer, LINE_MAX, pfile) != NULL)
	{
		//memcpy(holder, buffer, LINE_MAX);
		hold = strtok(buffer, " ;\n");
		while (hold != NULL)
		{
			if (i%5 == 0) name = _strdup(hold);
			if (i%5 == 1) surname = _strdup(hold);
			if (i%5 == 2) sex = _strdup(hold);
			if (i % 5 == 3) age = strtol(hold, NULL, 0);//(int)hold;
			if (i % 5 == 4) nin = strtoull(hold, NULL, 0);//(unsigned long long) hold;
			hold = strtok(NULL, " ;\n");
			i++;
		}
		addelementfile(name, surname, sex, age, nin);
	}
	fclose(pfile);
	return true;
}

void addelementfile(char * name, char * surname, char * sex, int age, unsigned long long nin)
{
	if (isEmpty())
	{
		addFirst(name, surname, sex, age, nin);
	}
	else
	{
		addLast(name, surname, sex, age, nin);
	}
}

void sortlist()//narazie nei dziala
{
	const char * alph = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
	struct dlist * current = NULL;
	struct dlist * previous = NULL;
	for (int i = 0; i < 53; i++)
	{
		current = head;
		while (current != NULL)
		{
			if (alph[i] == current->surname[0]) addsortelement(current->name, current->surname, current->sex, current->age, current->nin);
			current = current->next;
		}
	}//current juz nie potrzebne, uzyjmy jeszcze razxd
	//niby czyscimy, czy to dziala nie wiem
	current = head;//no taka zamiana
	
	head = sorthead;
	last = sortlast;
	
	while (current != NULL)
	{
		previous = current;
		current = current->next;
		freestruct(previous);
	}
	if (current != NULL) freestruct(current); //czy to dziala? XD
	sorthead = NULL;
	sortlast = NULL;
}

void addsortFirst(char * name, char * surname, char * sex, int age, unsigned long long nin)//generalnie private
{
	struct dlist * link = (struct dlist *) malloc(sizeof(struct dlist));
	//link->key = key;
	link->name = name;
	link->surname = surname;
	link->sex = sex;
	link->age = age;
	link->nin = nin;
	sortlast = link;
	link->next = sorthead;
	sorthead = link;
	sorthead->next = NULL;
	sorthead->prev = NULL;
}

void addsortLast(char * name, char * surname, char * sex, int age, unsigned long long nin)//generalnie private
{
	struct dlist * link = (struct dlist *) malloc(sizeof(struct dlist));

	link->name = name;
	link->surname = surname;
	link->sex = sex;
	link->age = age;
	link->nin = nin;
	sortlast->next = link;
	link->prev = sortlast;
	sortlast = link;
	sortlast->next = NULL;
}

void addsortelement(char * name, char * surname, char * sex, int age, unsigned long long nin)
{
	if (issortEmpty())
	{
		addsortFirst(name, surname, sex, age, nin);
	}
	else
	{
		addsortLast(name, surname, sex, age, nin);
	}
}

bool issortEmpty()
{
	return sorthead == NULL;
}

void menu()
{
	int opt=0;
	
	//scanf(" %i", &opt);
	while (opt != 8)
	{
		opt = 0;
		printf("\n[1]Dodaj wpis\n[2]Wykasuj wpis(nazwisko)\n[3]Wyszukaj osobe po nazwisku\n[4]Wyswietl liste\n"
			"[5]Odczytaj liste z pliku\n[6]Zapisz liste do pliku\n[7]Posortuj liste\n[8]Wyjscie\n");
		scanf(" %i", &opt);
		switch (opt)
		{
		case 1:
			addelement();
			break;
		case 2:
			deleteperson();
			break;
		case 3:
			findperson();
			break;
		case 4:
			displaydata();
			break;
		case 5:
			loadlist();
			break;
		case 6:
			savelist();
			break;
		case 7:
			sortlist();
			break;
		case 8:
			break;
		case 9:
			displaydatabackward();
			break;
		default:
			printf("Zla opcja\n");
			break;
		}
		printf("Wcisnij enter, by kontynuowac\n");
		_getch();
		//for (int i = 0; i<30; i++)	printf("\n");
		system("cls");//nie powinno tak sie robic
	}
}

void freestruct(struct dlist * delstruct)
{
	//delstruct->name = NULL;
	free(delstruct->name);
	free(delstruct->surname);// = NULL;
	free(delstruct->sex);// = NULL;
	delstruct->next = NULL;
	delstruct->prev = NULL;
	free(delstruct);
}