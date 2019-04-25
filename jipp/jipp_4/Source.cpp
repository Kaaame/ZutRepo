#include <iostream>
#include <vector>
#include <complex>
#include <stdio.h>
#include <math.h>
#include <conio.h>

using namespace std;

class Container
{
public:
	void wyswietlenie();
protected:
	vector<int> wejs;
	vector<complex<float>> wyjs = vector<complex<float>>(14);
	int a, b, c, d;
	float x1r, x2r, x3r, x4r, x1u, x2u, x3u, x4u;
	float deltar, deltau, pdeltar, pdeltau;
	float sr, su, rr, ru, ir, iu;
	Container(int, int, int, int);
	Container();
	virtual ~Container() {}
	void podaj_dane(int * a, int * b, int * c, int * d);
	void formatowanie();
	float oblicz_d_r(int a, int b, int c);
	float oblicz_d_u(int a, int d);
	//virtual void oblicz_delta() = 0;
	virtual float oblicz_p_d_r(float deltar, float deltau) { return 0.0; };
	virtual float oblicz_p_d_u(float deltar, float deltau) { return 0.0; };
	virtual void oblicz_pierwiastki() = 0;
	void dodaj();
	void odejmij();
	void pomnoz();
	//void wyswietlenie(int a, int b, int c, int d, float x1r, float x1u,
	//	float x2r, float x2u, float x3r, float x3u, float x4r, float x4u, float sr, float su,
	//	float rr, float ru, float ir, float iu);
	//void wyswietlenie();
};

Container::Container(int _a, int _b, int _c, int _d)
{
	this->wejs.push_back(_a);
	this->wejs.push_back(_b);
	this->wejs.push_back(_c);
	this->wejs.push_back(_d);

	this->a = _a;
	this->b = _b;
	this->c = _c;
	this->d = _d;
}

Container::Container()
{
	//this->podaj_dane(&this->a, &this->b, &this->c, &this->d);
}

void Container::dodaj()
{
	sr = x1r + x2r + x3r + x4r;
	su = x1u + x2u + x3u + x4u;
}

void Container::odejmij()
{
	rr = x1r - x2r - x3r - x4r;
	ru = x1u - x2u - x3u - x4u;
}

void Container::pomnoz()
{
	rr = x1r * x2r * x3r * x4r;
	ru = x1u * x2u * x3u * x4u;
}

void Container::formatowanie()
{
	if (a != 0)printf("%dx^2 + ", a);
	if (b != 0)printf("%dx + ", b);
	if (c != 0)printf("%d + ", c);
	if (d != 0)printf("%d i", d);
	printf("\n");
}

void Container::podaj_dane(int * a, int * b, int * c, int * d)
{
	printf("Podaj a:");
	scanf("%d", a);
	printf("Podaj b:");
	scanf("%d", b);
	printf("Podaj c:");
	scanf("%d", c);
	printf("Podaj d:");
	scanf("%d", d);
}

//void Container::wyswietlenie(int a, int b, int c, int d, float x1r, float x1u,
//	float x2r, float x2u, float x3r, float x3u, float x4r, float x4u, float sr, float su,
//	float rr, float ru, float ir, float i)
void Container::wyswietlenie()
{
	if (wejs[0] != 0 && wejs[3] == 0)
	{
		//oblicz_d_r(a, b, c);
		if (this->deltar > 0)
		{
			cout << "x1 =" << wyjs[0];
			cout << "x2 =" << wyjs[1];

			printf("x1r = %.2f\n", x1r);
			printf("x2r = %.2f", x2r);

		}
		else if (deltar == 0)
		{
			cout << "x1 =" << wyjs[0];

			printf("x1r = %.2f\n", x1r);
		}
		else
		{
			cout << "x1 =" << wyjs[0];

			printf("x1r = %.2f\n", x1r);
			printf("x1u = %.2f\n", x1u);
		}
	}
	else if ((wejs[0] == 0) && (wejs[1] != 0) && (wejs[3] == 0))
	{
		cout << "x1 =" << wyjs[0];

		printf("x1r = %.2f\n", x1r);
	}
	else if ((wejs[0] == 0) && (wejs[1] == 0) && ((wejs[3] != 0) || (wejs[2] != 0)))
	{
		printf("Rownanie sprzeczne.\n");
	}
	else if ((wejs[0] == 0) && (wejs[1] == 0) && (wejs[3] == 0) && (wejs[2] == 0))
	{
		printf("Rownanie tozsame.\n");
	}
	else if ((wejs[0]== 0) && (wejs[1] != 0) && (wejs[3] != 0))
	{
		cout << "x1 =" << wyjs[0];

		printf("x1r = %.2f\n", x1r);
		printf("x1u = %.2f\n", x1u);
	}
	else
	{
		cout << "x1 =" << wyjs[0];
		cout << "x2 =" << wyjs[0];
		cout << "x3 =" << wyjs[0];
		cout << "x4 =" << wyjs[0];

		printf("x1r = %.2f\n", x1r);
		printf("x2r = %.2f\n", x2r);
		printf("x3r = %.2f\n", x3r);
		printf("x4r = %.2f\n", x4r);

		printf("x1u = %.2f\n", x1u);
		printf("x2u = %.2f\n", x2u);
		printf("x3u = %.2f\n", x3u);
		printf("x4u = %.2f\n", x4u);
	}
}


float Container::oblicz_d_r(int a, int b, int c)
{
	this->wyjs[4] = (this->wejs[1] * this->wejs[1] - (4 * this->wejs[0] * this->wejs[2] * 1.0));
	deltar = (this->wejs[1]*this->wejs[1] - (4 * this->wejs[0] *this->wejs[2] *1.0));
	return 0.0;
}

float Container::oblicz_d_u(int a, int d)
{
	this->wyjs[5] = ((-4)*this->wejs[0]*this->wejs[3]*1.0);


	deltau = ((-4)*this->wejs[0]*this->wejs[3]*1.0);
	return 0.0;
}


class Real : virtual public Container
{
public:
	//Real();
	Real(int, int, int, int);
private:
	using Container::Container;
	using Container::wyswietlenie;
	//virtual void oblicz_delta();
	virtual float oblicz_p_d_r();
	virtual float oblicz_p_d_u();

	virtual void oblicz_pierwiastki();
};

Real::Real(int _a, int _b, int _c, int _d = 0)
{
	this->a = _a;
	this->b = _b;
	this->c = _c;
	this->d = 0;
	oblicz_d_r(a, b, c);
	oblicz_d_u(a, d);
	oblicz_p_d_r();
	oblicz_p_d_u();
	oblicz_pierwiastki();
}

void Real::oblicz_pierwiastki()
{
	if (a != 0)
	{
		//oblicz_d_r(a, b, c);
		if (deltar > 0)
		{
			printf("pdeltar = %.2f\n", pdeltar);

			x1r = (((-b - pdeltar) / (2 * a*1.0)));
			x2r = (((-b + pdeltar) / (2 * a*1.0)));
		}
		else if (deltar == 0)
		{
			x1r = 1.0*(-b / (2 * a));
		}
		else
		{
			x1r = (-b / (2 * a*1.0));
			x1u = -pdeltar / (2 * a*1.0);

			x2r = x1r;
			x2u = -x1u;
		}
	}
	else if ((a == 0) && (b != 0))
	{
		x1r = (-c*1.0) / b*1.0;
	}
	else if ((a == 0) && (b == 0) && (c == 0))
	{
		printf("Rownanie tozsame.\n");
	}
}

float Real::oblicz_p_d_r()
{
	this->pdeltar = sqrtf(((sqrtf((fabs(deltar*deltar)) + (deltau*deltau)) + fabs(deltar)) / 2));
	return 0.0;
}

float Real::oblicz_p_d_u()
{
	this->pdeltau = 0;
	return 0.0;
}
/*
void Real::oblicz_delta()
{
this->deltar = (b*b - (4 * a*c*1.0));
this->deltau = 0;
this->pdeltar = sqrt(deltar);
this->pdeltau = 0;
}
*/
class Imag : virtual public Container
{
public:
	Imag(int, int, int, int);
private:
	using Container::Container;
	using Container::wyswietlenie;
	virtual float oblicz_p_d_r();
	virtual float oblicz_p_d_u();
	//virtual void oblicz_delta();
	virtual void oblicz_pierwiastki();
};

Imag::Imag(int _a, int _b, int _c, int _d)
{
	wejs.push_back(_a);
	wejs.push_back(_b);
	wejs.push_back(_c);
	wejs.push_back(_d);

	//this->a = _a;
	//this->b = _b;
	//this->c = _c;
	//this->d = _d;
	oblicz_d_r(wejs[0], wejs[1], wejs[2]);
	oblicz_d_u(wejs[0], wejs[3]);
	oblicz_p_d_r();
	oblicz_p_d_u();
	oblicz_pierwiastki();
}

void Imag::oblicz_pierwiastki()
{

	if ((wejs[0] == 0) && (wejs[1] == 0) && ((wejs[2] != 0) || (wejs[3] != 0)))
	{
		//printf("Rownanie sprzeczne.\n");
	}
	else if ((wejs[0] == 0) && (wejs[1] == 0) && (wejs[3] == 0) && (wejs[2] == 0))
	{
		//printf("Rownanie tozsame.\n");
	}
	else if ((wejs[0] == 0) && (wejs[1] != 0) && (wejs[3] != 0))
	{
		wyjs[0] = ((-wejs[2]) / wejs[1] * 1.0, (-wejs[3]) / wejs[1] * 1.0);
		x1r = (-wejs[2]) / wejs[1]*1.0;
		x1u = (-wejs[3]) / wejs[1]*1.0;
	}
	else
	{
		
		wyjs[0] = real((-wejs[1] * 1.0 - pdeltar) / (2 * wejs[0])) + imag(pdeltau / (2.0f * wejs[0]));
		wyjs[1] = (((-wejs[1] * 1.0 + pdeltar) / (2 * wejs[0])), (pdeltau / (2.0f * wejs[0])));
		wyjs[2] = (real(-wejs[0]), imag(wejs[1]));
		wyjs[3] = (real(-wejs[0]), imag(wejs[0]));


		x1r = ((-wejs[1]*1.0 - pdeltar) / (2 * wejs[0]));
		x2r = ((-wejs[1]*1.0 + pdeltar) / (2 * wejs[0]));
		x1u = (-pdeltau / (2 * wejs[0]));
		x2u = (pdeltau / (2 * wejs[0]));
		x3r = -x1r;
		x4r = -x1r;
		x3u = x2u;
		x4u = x1u;
	}
}

float Imag::oblicz_p_d_r()
{
	//this->pdeltar = sqrtf(((sqrtf((deltar*deltar) + (deltau*deltau)) + deltar) / 2));
	//complex<float> dziel (2.0f, 0.0f);
	this->wyjs[6] = sqrt(((sqrt(wyjs[4] * wyjs[4]) - wyjs[4]) / 2.0f));
	this->pdeltar = sqrtf(((sqrtf((deltar*deltar) + (deltau*deltau)) + deltar) / 2));

	return 0.0;
}

float Imag::oblicz_p_d_u()
{
	//complex<float> a = (2,0);
	this->wyjs[7] = sqrt(((sqrt(wyjs[4]* wyjs[4]) - wyjs[4]) / 2.0f));
	this->pdeltau = sqrtf(((sqrtf((deltar*deltar) + (deltau*deltau)) - deltar) / 2));
	return 0.0;
}

int main()
{
	int a = 0, b = 0, c = 0, d = 0;
	Container * ptr = NULL;
	printf("Podaj a:");
	scanf("%d", &a);
	printf("Podaj b:");
	scanf("%d", &b);
	printf("Podaj c:");
	scanf("%d", &c);
	printf("Podaj d:");
	scanf("%d", &d);
	//ptr = new Real(;
	if (d == 0) ptr = new Real(a, b, c, d);
	else ptr = new Imag(a, b, c, d);

	ptr->wyswietlenie();
	_getch();
}