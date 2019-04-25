#include <stdio.h>
#include <math.h>
#include <conio.h>

void podaj_dane(int * a, int * b, int * c, int * d);
void formatowanie(int a, int b, int c, int d);
float oblicz_d_r(int a, int b, int c);
float oblicz_d_u(int a, int d);
float oblicz_p_d_r(float deltar, float deltau);
float oblicz_p_d_u(float deltar, float deltau);
void oblicz_pierwiastki(int a, int b, int c, int d, float * x1r,
						float * x2r, float * x3r, float * x4r, float * x1u,float * x2u, float * x3u, float * x4u);
void dodaj(float deltar, float deltau, float * x1r, float * x2r, float * x3r, float * x4r, float * x1u,
	float * x2u, float * x3u, float * x4u, float * sr, float * su);
void odejmij(float deltar, float deltau, float * x1r, float * x2r, float * x3r, float * x4r, float * x1u,
	float * x2u, float * x3u, float * x4u, float * rr, float * ru);
void pomnoz(float deltar, float deltau, float * x1r, float * x2r, float * x3r, float * x4r, float * x1u,
	float * x2u, float * x3u, float * x4u, float * ir, float * iu);
void wyswietlenie(int a, int b, int c, int d, float x1r, float x1u,
	float x2r, float x2u, float x3r, float x3u, float x4r, float x4u, float sr, float su,
	float rr, float ru, float ir, float iu);


int main()
{
	int a = 0, b = 0, c = 0, d = 0;

	float deltar = 0, deltau = 0;
	float pdeltar = 0, pdeltau = 0;
	float x1r = 0, x2r = 0, x3r = 0, x4r = 0;
	float x1u = 0, x2u = 0, x3u = 0, x4u = 0;
	float sr = 0, su = 0, rr = 0, ru = 0, ir = 0, iu = 0;

	podaj_dane(&a, &b, &c, &d);
	formatowanie(a, b, c, d);
	oblicz_pierwiastki(a, b, c, d, &x1r, &x2r, &x3r, &x4r, &x1u, &x2u, &x3u, &x4u);
	dodaj(oblicz_d_r(a, b, c), oblicz_d_u(a, d), &x1r, &x2r, &x3r, &x4r, &x1u, &x2u, &x3u, &x4u, &sr, &su);
	odejmij(oblicz_d_r(a, b, c), oblicz_d_u(a, d), &x1r, &x2r, &x3r, &x4r, &x1u, &x2u, &x3u, &x4u, &rr, &ru);
	pomnoz(oblicz_d_r(a, b, c), oblicz_d_u(a, d), &x1r, &x2r, &x3r, &x4r, &x1u, &x2u, &x3u, &x4u, &ir, &iu);

	wyswietlenie(a, b, c, d, x1r, x1u, x2r, x2u, x3r, x3u, x4r, x4u, sr, su, rr, ru, ir, iu);
	_getch();
}

void podaj_dane(int * a, int * b, int * c, int * d)
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

void formatowanie(int a, int b, int c, int d)
{
	if (a != 0)printf("%dx^2 + ", a);
	if (b != 0)printf("%dx + ", b);
	if (c != 0)printf("%d + ", c);
	if (d != 0)printf("%d i", d);
	printf("\n");
}

float oblicz_d_r(int a, int b, int c)
{
	return (b*b - (4 * a*c*1.0));
}

float oblicz_d_u(int a, int d)
{
	return ((-4)*a*d*1.0);
}

float oblicz_p_d_r(float deltar, float deltau)
{
	return sqrtf(((sqrtf((deltar*deltar) + (deltau*deltau)) + deltar) / 2));
}

float oblicz_p_d_u(float deltar, float deltau)
{
	return sqrtf(((sqrtf((deltar*deltar) + (deltau*deltau)) - deltar) / 2));
}

void oblicz_pierwiastki(int a, int b, int c, int d, float * x1r,
	float * x2r, float * x3r, float * x4r, float * x1u, float * x2u, float * x3u, float * x4u)
{
	if (a != 0 && d == 0)
	{
		//oblicz_d_r(a, b, c);
		if (oblicz_d_r(a, b, c) > 0)
		{
			*x1r = ((-b*1.0 - oblicz_p_d_r(oblicz_d_r(a, b, c), 0))/(2*a*1.0));
			*x2r = ((-b*1.0 + oblicz_p_d_r(oblicz_d_r(a, b, c), 0))/(2 * a*1.0));
		}
		else if (oblicz_d_r(a, b, c) == 0)
		{
			*x1r = 1.0*(-b / (2 * a));
		}
		else
		{
			*x2r = oblicz_d_r(a, b, c);
			*x2u = oblicz_p_d_r(-*x2r, 0);
			*x1r = (-b / (2 * a*1.0));
			*x1u = -*x2u / (2 * a*1.0);
			//printf("DELTAR = %.2f", *x2r);
			//printf("pDELTAR = %.2f", *x2u);
			*x2r = *x1r;
			*x2u = -*x1u;
			
		}
	}
	else if ((a == 0) && (b != 0) && (d == 0))
	{
		*x1r = (-c*1.0) / b*1.0;
	}
	else if ((a == 0) && (b == 0) && ((d != 0) || (c != 0)))
	{
		printf("Rownanie sprzeczne.\n");
	}
	else if ((a == 0) && (b == 0) && (d == 0) && (c == 0))
	{
		printf("Rownanie tozsame.\n");
	}
	else if ((a == 0) && (b != 0) && (d != 0))
	{
		*x1r = (-c) / b*1.0;
		*x1u = (-d) / b*1.0;
	}
	else
	{
		*x3r = oblicz_d_r(a, b, c);
		*x4r = oblicz_d_u(a, d);



		*x1r = ((-b*1.0 - oblicz_p_d_r(*x3r, *x4r))) / (2 * a);
		*x2r = ((-b*1.0 + oblicz_p_d_r(*x3r, *x4r))) / (2 * a);
		*x1u = (-oblicz_p_d_u(*x3r, *x4r)) / (2 * a);
		*x2u = (oblicz_p_d_u(*x3r, *x4r)) / (2 * a);
		*x3r = -*x1r;
		*x4r = -*x1r;
		*x3u = *x2u;
		*x4u = *x1u;
	}
}

void dodaj(float deltar, float deltau, float * x1r, float * x2r, float * x3r, float * x4r, float * x1u,
	float * x2u, float * x3u, float * x4u, float * sr, float * su)
{
	*sr = *x1r + *x2r + *x3r + *x4r;
	*su = *x1u + *x2u + *x3u + *x4u;

}
void odejmij(float deltar, float deltau, float * x1r, float * x2r, float * x3r, float * x4r, float * x1u,
	float * x2u, float * x3u, float * x4u, float * rr, float * ru)
{
	*rr = *x1r - *x2r - *x3r - *x4r;
	*ru = *x1u - *x2u - *x3u - *x4u;
}

void pomnoz(float deltar, float deltau, float * x1r, float * x2r, float * x3r, float * x4r, float * x1u,
	float * x2u, float * x3u, float * x4u, float * ir, float * iu)
{
	*ir = *x1r * *x2r * *x3r * *x4r;
	*iu = *x1u * *x2u * *x3u * *x4u;
}

void wyswietlenie(int a, int b, int c, int d, float x1r, float x1u,
	float x2r, float x2u, float x3r, float x3u, float x4r, float x4u, float sr, float su,
	float rr, float ru, float ir, float iu)
{
	printf("a: %d\tb: %d\tc: %d\td: %d\nx1r: %.2f\tx1u: %.2f\nx2r: %.2f\tx2u: %.2f\n"
		"x3r: %.2f\tx3u: %.2f\nx4r: %.2f\tx4u: %.2f\nsr: %.2f\tsu: %.2f\n"
		"rr: %.2f\tru: %.2f\nir: %.2f\tiu: %.2f\n", a, b, c, d, x1r, x1u, x2r, x2u,
		x3r, x3u, x4r, x4u, sr, su, rr, ru, ir, iu);

}
