#include "Header.h"

void animal::ListAdd(field * game)
{
	game->alist.push_back(this);
}


void animal::ListDel(field * game)
{
	for (vector<animal *>::size_type i = 0; i < game->alist.size(); i++)
	{
		if (game->alist[i] == this) game->alist.erase(game->alist.begin() + i);
	}
}

void animal::atdeath()
{
	printf(" no umieram ");
}

animal::animal(int _posx, int _posy, int _health, int _movement, int _att, int _hunger)
{
	this->posx = _posx;
	this->posy = _posy;
	this->health = _health;
	this->movement = _movement;
	this->att = _att;
	this->hunger = _hunger;
}

animal::~animal()
{

}

int animal::getPosx()
{
	return this->posx;
}
int animal::getPosy()
{
	return this->posy;
}

/*void animal::countAnimal()
{

}
*/
animal * animal::animalbyPos(int sposx, int sposy, field * game)
{
	for (vector<animal *>::size_type i = 0; i != game->alist.size(); i++)
	{
		if (game->alist[i]->posx == sposx && game->alist[i]->posy == sposy) return game->alist[i];
	}
	return NULL;
}
/*
void animal::Move(field * game)
{

}

void animal::Attack(animal * prey)
{

}
*/
void animal_deer::Move(field * game)//herbivore, diamond inheritance? x-N S y- W E
{
	int cposx, cposy;
	int dir;
	bool flag = false;
	//animal * look = NULL;
	do
	{
		dir = rand() % 4 + 1;
		flag = false;

		cposx = this->posx;
		cposy = this->posy;

		switch (dir)
		{
		case DIRECTION_W://idziemy na polnoc
		{
			cposy = cposy - this->movement;//minus bo w gore
			if (cposy < 0)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posy; i != cposy; i--)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[this->posx][i] == 1)//definiowanie zachowania zwierzaka
					{
						game->matrix[this->posx][i + 1] = 1;//pole wczesniej i+1
						this->posy = i + 1;
						break;
					}
					if (game->matrix[this->posx][i] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posy = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_E://idziemy na poludnie
		{
			cposy = cposy + this->movement;//plus bo w dol
			if (cposy > game->sizec)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posy; i != cposy; i++)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[this->posx][i] == 1)//definiowanie zachowania zwierzaka
					{
						game->matrix[this->posx][i - 1] = 1;
						this->posy = i - 1;
						break;
					}
					if (game->matrix[this->posx][i] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posy = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl

			}
			break;
		}
		case DIRECTION_N://idziemy na zachod
		{
			cposx = cposx - this->movement;//minus bo w lewo
			if (cposx < 0)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posx; i != cposx; i--)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[i][this->posy] == 1)//definiowanie zachowania zwierzaka
					{
						game->matrix[i + 1][this->posy] = 1;
						this->posx = i + 1;
						break;
					}
					if (game->matrix[i][this->posy] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posx = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl

			}

			break;
		}
		case DIRECTION_S://idziemy na wschod
		{
			cposx = cposx + this->movement;//plus bo w prawo
			if (cposx > game->sizer)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posx; i != cposx; i++)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[i][this->posy] == 1)//definiowanie zachowania zwierzaka
					{
						game->matrix[i - 1][this->posy] = 1;
						this->posx = i - 1;
						break;
					}
					if (game->matrix[i][this->posy] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posx = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		}
	} while (flag);
}

void animal_bison::Move(field * game)
{
	int cposx, cposy;
	int dir;
	bool flag = false;
	//animal * look = NULL;
	do
	{
		dir = rand() % 4 + 1;
		flag = false;
		
		cposx = this->posx;
		cposy = this->posy;

		switch (dir)
		{
		case DIRECTION_W://idziemy na polnoc
		{
			cposy = cposy - this->movement;//minus bo w gore
			if (cposy < 0)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posy; i != cposy; i--)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[this->posx][i] == 1)//definiowanie zachowania zwierzaka
					{
						game->matrix[this->posx][i + 1] = 1;//pole wczesniej i+1
						this->posy = i + 1;
						break;
					}
					if (game->matrix[this->posx][i] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posy = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_E://idziemy na poludnie
		{
			cposy = cposy + this->movement;//plus bo w dol
			if (cposy > game->sizec)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posy; i != cposy; i++)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[this->posx][i] == 1)//definiowanie zachowania zwierzaka
					{
						game->matrix[this->posx][i - 1] = 1;
						this->posy = i - 1;
						break;
					}
					if (game->matrix[this->posx][i] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posy = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_N://idziemy na zachod
		{
			cposx = cposx - this->movement;//minus bo w lewo
			if (cposx < 0)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posx; i != cposx; i--)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[i][this->posy] == 1)//definiowanie zachowania zwierzaka
					{
						//game->matrix[i + 1][this->posy] = 1;
						this->posx = i + 1;
						break;
					}
					if (game->matrix[i][this->posy] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posx = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_S://idziemy na wschod
		{
			cposx = cposx + this->movement;//plus bo w prawo
			if (cposx > game->sizer)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posx; i != cposx; i++)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[i][this->posy] == 1)//definiowanie zachowania zwierzaka
					{
						//game->matrix[i - 1][this->posy] = 1;
						this->posx = i - 1;
						break;
					}
					if (game->matrix[i][this->posy] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posx = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		}
	} while (flag);
}

void animal_wolf::Move(field * game)
{
	int cposx, cposy;
	int dir;
	bool flag = false;
	animal * prey = NULL;
	//animal * look = NULL;
	do
	{
		dir = rand() % 4 + 1;
		flag = false;

		cposx = this->posx;
		cposy = this->posy;

		switch (dir)
		{
		case DIRECTION_W://idziemy na zachod
		{
			cposy = cposy - this->movement;//minus bo w gore
			if (cposy < 0)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posy; i != cposy; i--)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[this->posx][i] == 1)//definiowanie zachowania zwierzaka
					{
						prey = animal::animalbyPos(this->posx, i, game);
						this->Attack(prey);
						if (prey->health <= 0)
						{
							//prey->ListDel(&(game->head));
							prey->ListDel(game);
							delete prey;
							field::deathEaten++;
							this->hunger = HUNGER_TURN;
							this->posy = i;
						}
						else
						{
							//game->matrix[this->posx][i + 1] = 1;//pole wczesniej i+1
							this->posy = i + 1;
						}
						
						break;
					}
					if (game->matrix[this->posx][i] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posy = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_E://idziemy na wschod
		{
			cposy = cposy + this->movement;//plus bo w dol
			if (cposy > game->sizec)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posy; i != cposy; i++)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[this->posx][i] == 1)//definiowanie zachowania zwierzaka
					{
						prey = animal::animalbyPos(this->posx, i, game);
						this->Attack(prey);
						if (prey->health <= 0)
						{
							prey->ListDel(game);
							delete prey;
							field::deathEaten++;
							this->hunger = HUNGER_TURN;
							this->posy = i;
						}
						else
						{
							//game->matrix[this->posx][i - 1] = 1;
							this->posy = i - 1;
						}
						break;
					}
					if (game->matrix[this->posx][i] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posy = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_N://idziemy na zachod
		{
			cposx = cposx - this->movement;//minus bo w lewo
			if (cposx < 0)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posx; i != cposx; i--)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[i][this->posy] == 1)//definiowanie zachowania zwierzaka
					{
						prey = animal::animalbyPos(i, this->posy, game);
						this->Attack(prey);
						if (prey->health <= 0)
						{
							prey->ListDel(game);
							delete prey;
							field::deathEaten++;
							this->hunger = HUNGER_TURN;
							this->posx = i;
						}
						else
						{
							//game->matrix[i+1][this->posy] = 1;//pole wczesniej i+1
							this->posx = i + 1;
						}
						break;
					}
					if (game->matrix[i][this->posy] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posx = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_S://idziemy na pludnie
		{
			cposx = cposx + this->movement;//plus bo w prawo
			if (cposx > game->sizer)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posx; i != cposx; i++)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[i][this->posy] == 1)//definiowanie zachowania zwierzaka
					{
						prey = animal::animalbyPos(i, this->posy, game);
						this->Attack(prey);
						if (prey->health <= 0)
						{
							prey->ListDel(game);
							delete prey;
							field::deathEaten++;
							this->hunger = HUNGER_TURN;
							this->posx = i;
						}
						else
						{
							//game->matrix[i - 1][this->posy] = 1;//pole wczesniej i+1
							this->posx = i - 1;
						}
						break;
					}
					if (game->matrix[i][this->posy] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posx = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		}
	} while (flag);
}

void animal_bear::Move(field * game)
{
	int cposx, cposy;
	int dir;
	bool flag = false;
	animal * prey = NULL;
	//animal * look = NULL;
	do
	{
		dir = rand() % 4 + 1;
		flag = false;

		cposx = this->posx;
		cposy = this->posy;

		switch (dir)
		{
		case DIRECTION_W://idziemy na polnoc
		{
			cposy = cposy - this->movement;//minus bo w gore
			if (cposy < 0)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posy; i != cposy; i--)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[this->posx][i] == 1)//definiowanie zachowania zwierzaka
					{
						prey = animal::animalbyPos(this->posx, i, game);
						this->Attack(prey);
						if (prey->health <= 0)
						{
							//prey->ListDel(&(game->head));
							prey->ListDel(game);
							delete prey;
							field::deathEaten++;
							this->hunger = HUNGER_TURN;
							this->posy = i;
						}
						else
						{
							//game->matrix[this->posx][i + 1] = 1;//pole wczesniej i+1
							this->posy = i + 1;
						}

						break;
					}
					if (game->matrix[this->posx][i] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posy = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_E://idziemy na poludnie
		{
			cposy = cposy + this->movement;//plus bo w dol
			if (cposy > game->sizec)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posy; i != cposy; i++)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[this->posx][i] == 1)//definiowanie zachowania zwierzaka
					{
						prey = animal::animalbyPos(this->posx, i, game);
						this->Attack(prey);
						if (prey->health <= 0)
						{
							prey->ListDel(game);
							delete prey;
							field::deathEaten++;
							this->hunger = HUNGER_TURN;
							this->posy = i;
						}
						else
						{
							//game->matrix[this->posx][i - 1] = 1;
							this->posy = i - 1;
						}
						break;
					}
					if (game->matrix[this->posx][i] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posy = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_N://idziemy na zachod
		{
			cposx = cposx - this->movement;//minus bo w lewo
			if (cposx < 0)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posx; i != cposx; i--)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[i][this->posy] == 1)//definiowanie zachowania zwierzaka
					{
						prey = animal::animalbyPos(i, this->posy, game);
						this->Attack(prey);
						if (prey->health <= 0)
						{
							prey->ListDel(game);
							delete prey;
							field::deathEaten++;
							this->hunger = HUNGER_TURN;
							this->posx = i;
						}
						else
						{
							//game->matrix[i + 1][this->posy] = 1;//pole wczesniej i+1
							this->posx = i + 1;
						}
						break;
					}
					if (game->matrix[i][this->posy] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posx = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		case DIRECTION_S://idziemy na wschod
		{
			cposx = cposx + this->movement;//plus bo w prawo
			if (cposx > game->sizer)//granica mapy
			{
				flag = true;
				continue;
			}
			else
			{
				game->matrix[this->posx][this->posy] = 0;//wyruszyl
				for (int i = this->posx; i != cposx; i++)//sprawdzenie wlasnego miejsca tez
				{
					if (game->matrix[i][this->posy] == 1)//definiowanie zachowania zwierzaka
					{
						prey = animal::animalbyPos(i, this->posy, game);
						this->Attack(prey);
						if (prey->health <= 0)
						{
							prey->ListDel(game);
							delete prey;
							field::deathEaten++;
							this->hunger = HUNGER_TURN;
							this->posx = i;
						}
						else
						{
							//game->matrix[i - 1][this->posy] = 1;//pole wczesniej i+1
							this->posx = i - 1;
						}
						break;
					}
					if (game->matrix[i][this->posy] == 0)//nikogo nie ma, na biezaco zmieniamy pozycje
					{
						this->posx = i;
					}
				}
				game->matrix[this->posx][this->posy] = 1;//wyruszyl
			}
			break;
		}
		}
	} while (flag);
}
/*
void animal_wolf::Move(field * game)
{

}

void animal_bear::Move(field * game)
{

}
*/

void animal_deer::Attack(animal * prey)
{

}

void animal_bison::Attack(animal * prey)
{

}

void animal_wolf::Attack(animal * prey)
{
	prey->health = prey->health - this->att;
}

void animal_bear::Attack(animal * prey)
{
	prey->health = prey->health - this->att;
}

void animal_deer::countAnimal()
{
	field::herbivores++;
}

void animal_bison::countAnimal()
{
	field::herbivores++;
}

void animal_wolf::countAnimal()
{
	field::carnivores++;
}

void animal_bear::countAnimal()
{
	field::carnivores++;
}

animal_deer::~animal_deer()
{
	this->atdeath();//przesloniecie metod
	cout << endl << "called deer destructor";
}

animal_bison::~animal_bison()
{
	cout << endl << "called bison destructor";
}

animal_wolf::~animal_wolf()
{
	this->atdeath();
	cout << endl << "called wolf destructor";
}

animal_bear::~animal_bear()
{
	cout << endl << "called bear destructor";
}

void animal_wolf::atdeath()
{
	cout << "no ja tez umieram, ale z gracja";
}