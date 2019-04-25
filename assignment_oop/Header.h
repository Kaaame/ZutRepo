#pragma once
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <exception>
//#include <SFML\Graphics.hpp>
//#include <SFML\Graphics\Color.hpp>
//wyjatki zdefiniowane wlasne
//klasa abstrakcyjna przeslanianie pol i metod
//set

#define DIRECTION_N 1
#define DIRECTION_S 2
#define DIRECTION_W 3
#define DIRECTION_E 4

#define deer 1
#define bison 2
#define wolf 3
#define bear 4

#define SIZER 10//maksymalny rozmiar macierzy
#define SIZEC 15

#define HUNGER_TURN 3//musi byc mniejsze niz 666

#define TURNS 15

using std::vector;
using std::cout;
using std::endl;
using std::fstream;
using std::exception;

class field;
class animal;


class field
{
public:
	//int matrix[SIZER][SIZEC];
	int ** matrix;

	vector<animal *> alist;
	int sizer, sizec;
	int turn = 1;
	static int deathHunger;
	static int deathEaten;
	static int carnivores;
	static int herbivores;

	field(int _sizer, int _sizec);
	field(const field &_field);
	~field();
	void ShowField();
	void Turn();
	static void CleanScreen();
	void SaveScores();
private:
	fstream res;
	void GenerateField();
	int countMatrix();
};

class animal
{
public:
	virtual void Move(field * game) = 0;//klasa czysto wirtualna, abstrakcyjna
	virtual void Attack(animal * prey) = 0;
	animal(int _posx, int _posy, int _health, int _movement, int _att, int _hunger);
	virtual ~animal();

	virtual void countAnimal() = 0;

	void atdeath();

	void ListAdd(field * game);
	int turn = 0;
	static animal * animalbyPos(int sposx, int sposy, field * game);
	void ListDel(field * game);//wywolywac przed destruktorem
	
	int getPosx();
	int getPosy();

	int health;
	int hunger;
protected:
	int posx, posy;
	int movement;
	int att;
};

class animal_deer : public animal
{
	using animal::animal;
	virtual void Attack(animal * prey);
	~animal_deer();
	virtual void Move(field * game);//diamond inheritance?
	virtual void countAnimal();

};

class animal_bison : public animal
{
	using animal::animal;
	virtual void Attack(animal * prey);
	~animal_bison();
	virtual void Move(field * game);
	virtual void countAnimal();
};

class animal_wolf : public animal
{
	void atdeath();
	using animal::animal;
	~animal_wolf();
	virtual void Move(field * game);
	virtual void Attack(animal * prey);
	virtual void countAnimal();
};

class animal_bear : public animal
{
	using animal::animal;
	~animal_bear();
	virtual void Move(field * game);
	virtual void Attack(animal * prey);
	virtual void countAnimal();
};

int countList(field * game);
