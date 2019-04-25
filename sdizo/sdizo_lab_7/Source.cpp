#include <iostream>
#include <fstream>
#include <set>
#include <time.h>
#include <conio.h>

int * readarr(const char * filename);

using namespace std;

int main()
{
	srand(2137);
	clock_t timet[5];
	int wyniki[5];

	clock_t start, stop;

	set<int> secik;
	int n[] = { 100000, 150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000 };
	int * keys = readarr("rand.txt");
	int randkey;
	pair<set<int>::iterator, bool> insert(const int& x);
	set<int>::iterator it;
	for (int j = 0; j < 9; j++)
	{

		wyniki[0] = 0;//dodawanie z pliku
		wyniki[1] = 0;//wyszukiwanie z pliku
		wyniki[2] = 0;//wyszukiwanie losowo
		wyniki[3] = 0;//usuwanie losowo
		wyniki[4] = 0;//usuwanie z pliku

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j]; i++)
		{
			randkey = keys[i];// 10m
			secik.insert(randkey);
			//if (secik.count(randkey) == 1) wyniki[0]++;
			//if (secik.insert(randkey).second) wyniki[0]++;
			wyniki[0] = secik.size();

		}
		stop = clock();
		timet[0] = stop - start;
#pragma endregion onebloc

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j]; i++)
		{
			randkey = keys[i];// 10m
			
			it = secik.find(randkey);
			if (it != secik.end()) wyniki[1]++;
		}
		stop = clock();
		timet[1] = stop - start;
#pragma endregion onebloc

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j]; i++)
		{
			randkey = rand() % 25000 * (rand() % 400);// 10m

			it = secik.find(randkey);
			if (it != secik.end()) wyniki[2]++;
		}
		stop = clock();
		timet[2] = stop - start;
#pragma endregion onebloc

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j]; i++)
		{
			randkey = rand() % 25000 * (rand() % 400);// 10m

			if (secik.erase(randkey)) wyniki[3]++;
		}
		stop = clock();
		timet[3] = stop - start;
#pragma endregion onebloc

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j] / 2; i++)
		{
			randkey = keys[i];// 10m

			if (secik.erase(randkey)) wyniki[4]++;
		}
		stop = clock();
		timet[4] = stop - start;
#pragma endregion onebloc
		printf("SET\n\n");
		printf("%d elementow(z pliku): czas wstawiania = %lu ms\twstawiono: %d\n", n[j], timet[0], wyniki[0]);
		printf("%d elementow(z pliku): czas wyszukiwania = %lu ms\twyszukano: %d\n", n[j], timet[1], wyniki[1]);
		printf("%d elementow(losowo): czas wyszukiwania = %lu ms\twyszukano: %d\n", n[j], timet[2], wyniki[2]);
		printf("%d elementow(losowo): czas usuwania = %lu ms\tusunieto: %d\n", n[j], timet[3], wyniki[3]);
		printf("%d elementow(z pliku): czas usuwania = %lu ms\tusunieto: %d\n\n", n[j], timet[4], wyniki[4]);
		secik.clear();
	}
	_getch();
}


int * readarr(const char * filename)
{
	std::fstream file;
	int * arr = new int[500000];
	int counter = 0;
	file.open(filename, std::fstream::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> arr[counter];
			counter++;
		}
	}
	return arr;
}