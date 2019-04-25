#include "Header.h"


int main()
{
	field::CleanScreen();
	field * gamefield = new field(10, 15);
	for (int i = 0; i < TURNS; i++)
	{
		gamefield->CleanScreen();
		gamefield->ShowField();
		gamefield->Turn();
		cout << endl << "elementy listy: " << countList(gamefield);
		_getch();
	}
	gamefield->SaveScores();
	delete gamefield;
	gamefield->Turn();
	int x = 0;
}