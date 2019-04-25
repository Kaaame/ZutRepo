#include "Header.h"
#include "exceptionheader.h"
//int field::turn = 1;

int field::deathEaten = 0;
int field::deathHunger = 0;

int field::carnivores = 0;
int field::herbivores = 0;

field::field(int _sizer, int _sizec)
{

	srand(time(NULL));
	MatrixException z;
	try
	{
		if (_sizer > SIZER || _sizec > SIZEC) throw z;
		matrix = new int*[_sizer];

		
		for (int i = 0; i < _sizer; i++) matrix[i] = new int[_sizec];
		for (int i = 0; i < _sizer; i++)
			{
				for (int j = 0; j < _sizec; j++)
				{
					matrix[i][j] = 0;
				}
			}
		sizer = _sizer;
		sizec = _sizec;
		GenerateField();
	}
	catch (MatrixException& e)
	{
		cout << e.what();
		_getch();
	}
}

field::field(const field &_field)
{
	memcpy(matrix, &(_field.matrix), sizeof(_field.matrix));
	turn = _field.turn;
}

field::~field()
{
	if (res.is_open()) res.close();
	
	for (vector<animal *>::size_type i = 0; i != this->alist.size(); i++)
	{
		delete this->alist[i];
	}
	//delete &alist;
}

void field::GenerateField()
{
	int rnborn, rnanimal;
	animal * local = NULL;
	for (int i = 0; i < sizer; i++)
	{
		for (int j = 0; j < sizec; j++)
		{
			rnborn = rand() % 2;
			if (rnborn)
			{
				rnanimal = rand() % 4 + 1;
				switch (rnanimal)
				{
					case deer:
					{
						matrix[i][j] = 1;
						local = new animal_deer(i, j, 1, 3, 0, 666);
						break;
					}
					case bison:
					{
						matrix[i][j] = 1;
						local = new animal_bison(i, j, 1, 3, 0, 666);
						break;
					}
					case wolf:
					{
						matrix[i][j] = 1;
						local = new animal_wolf(i, j, 2, 3, 2, HUNGER_TURN);
						break;
					}
					case bear:
					{
						matrix[i][j] = 1;
						local = new animal_bear(i, j, 4, 3, 3, HUNGER_TURN);
						break;
					}
				}
				local->ListAdd(this);
			}
		}
	}
}

void field::ShowField()
{
	for (int i = 0; i < sizer; i++)
	{
		for (int j = 0; j < sizec; j++)
		{
			cout << matrix[i][j];
		}
		cout << endl;
	}
}

void field::SaveScores()
{
	for (vector<animal *>::size_type i = 0; i != this->alist.size(); i++)
	{
		this->alist[i]->countAnimal();
	}
	res.open("wyniki.txt", fstream::out);
	if (res.is_open())
	{
		res << "Tury: " << TURNS << endl
			<< "Liczba zwierzat, ktore przetrwaly: " << countMatrix() << endl
			<< "Roslinozercy: " << field::herbivores << endl
			<< "Miesozercy: " << field::carnivores << endl;
		res.close();
	}
	else
	{
		cout << endl << "nie mozna bylo otworzyc pliku";
	}
}

void field::Turn()
{
	animal * hold = NULL;
	int hposx, hposy;
	for (int i = 0; i < sizer; i++)
	{
		for (int j = 0; j < sizec; j++)		
		{
			hold = NULL;
			if (matrix[i][j] == 1)
			{
				hold = animal::animalbyPos(i, j, this);
				if (hold->turn != this->turn)
				{
					if (hold->hunger != 666) hold->hunger--;//wrzucic do ifa na dole
					hold->Move(this);
				}
				hold->turn = this->turn;
				if (hold->hunger <= 0)
				{
					field::deathHunger++;
					hposx = hold->getPosx();
					hposy = hold->getPosy();
					matrix[hposx][hposy] = 0;
					hold->ListDel(this);
					delete hold;
				}
			}
		}
	}
	this->turn++;
}

void field::CleanScreen()
{
	for (int i = 0; i < 50; i++)
	{
		cout << endl;
	}
}

int field::countMatrix()
{
	int counter = 0;
	for (int i = 0; i < sizer; i++)
	{
		for (int j = 0; j < sizec; j++)
		{
			if (matrix[i][j] == 1) counter++;
		}
	}
	return counter;
}

int countList(field * game)
{
	return game->alist.size();
}