#include <stdio.h>
#include <conio.h>

int a = 10, b = 2, c = 1, d = -6;

float	deltar, deltau;
float pdeltar, pdeltau;
float x1r, x2r, x3r, x4r;
float x1u, x2u, x3u, x4u;

int main()
{
	printf("(%d)*x*x + (%d)*x + (%d) + (%d)*i\n", a, b, c, d);

	if (a != 0 && d == 0)
	{
		deltar = 1.0*b*b - 4 * a*c;
		if (deltar > 0)
		{
			x1r = deltar;//obliczanie pierwiastka - pierwiastek z delty
			x2r = deltar / 2;
		loop:
			if ((1.0*a*x2r*x2r + 1.0*b*x2r + 1.0*c*x2r) >= 0.01)
			{
				x2r = (x2r + (x1r / x2r)) / 2;
				printf("x2r = %.2f\n", x2r);

				goto loop;
			}
			//x2r = (x2r + (x1r / x2r)) / 2;
			//x2r = (x2r + (x1r / x2r)) / 2;
			//x2r = (x2u + (x1r / x2r)) / 2;

			x1r = (-b - x2r) / (2 * a);
			x2r = (-b + x2r) / (2 * a);

			printf("x1r = %.2f\tx2r = %.2f", x1r, x2r);
		}
		else if (deltar == 0)
		{
			x1r = 1.0*(-b / (2 * a));
			printf("x = %.2f", x1r);
		}
		else
		{
			x1r = (-b / (2 * a*1.0));

			//x2u = x1r / 2;
			x2u = 6.0;

			x1u = -deltar;//jest ujemny to zamienic

			x2u = (x2u + (x1u / x2u)) / 2;
			x2u = (x2u + (x1u / x2u)) / 2;
			x2u = (x2u + (x1u / x2u)) / 2;
			x2u = (x2u + (x1u / x2u)) / 2;

			x1u = 1.0*((-x2u) / (2 * a));

			x2r = x1r;
			x2u = -x1u;

			printf("x1r = %.2f\tx2r = %.2f\nx1u = %.2f\tx2u = %.2f", x1r, x2r, x1u, x2u);
		}
	}
	else if ((a == 0) && (b != 0) && (d == 0))
	{
		x1r = (-c) / b*1.0;
		printf("x1r = %.2f\n", x1r);
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
		x1r = (-c) / b*1.0;
		x1u = (-d) / b*1.0;

		printf("x1r = %.2f\tx1u = %.2f", x1r, x1u);
	}
	else//podpunkt 6
	{
		
		deltar = (b*b) - (4 * a*c*1.0);
		deltau = (-4)*a*d*1.0;//dodac i

								 //obliczanie pierwiastka m^2+n^2
		x1r = (deltar*deltar)+(deltau*deltau);//m*m+n*n
		//x1r += deltau*deltau;
		printf("m*m+n*n = %.2f\n", (deltar*deltar) + (deltau*deltau));

		x2r = x1r / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;
		x2r = (x2r + (x1r / x2r)) / 2;


		printf("sqrt(m*m+n*n) = %.2f\n", x2r);

		pdeltar = (x2r + deltar) / 2.0;
		pdeltau = (x2r - deltar) / 2.0;


		x1r = pdeltar / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;
		x1r = (x1r + (pdeltar / x1r)) / 2;//pdeltar

		pdeltar = x1r;

		x1r = pdeltau / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;
		x1r = (x1r + (pdeltau / x1r)) / 2;//pdeltau

		pdeltau = x1r;
		//printf("przed = %.2f\n", x1r);

		x1r = ((-b*1.0 + pdeltar) / (2 * a));
		x2r = ((-b*1.0 - pdeltar) / (2 * a));
		x1u = (pdeltau / (2 * a));
		x2u = (-pdeltau / (2 * a));
		
		x3r = -x1r;
		x4r = -x2r;
		x3u = x2u;
		x4u = x1u;

		printf("deltau = %.2f\tpdeltau = %.2f\ndeltar= %.2f i\tpdeltar= %.2f i\n", deltau, pdeltau, deltar, pdeltar);

		printf("x1r = %.2f\tx2r = %.2f\nx1u = %.2f i\tx2u = %.2f i\n", x1r, x2r, x1u, x2u);
		printf("x3r = %.2f\tx4r = %.2f\nx3u = %.2f\tx4u = %.2f\n", x3r, x4r, x3u, x4u);
		
	}
	_getch();
}