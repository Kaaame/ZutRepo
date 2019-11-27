#include <stdio.h>
#include <math.h>
 
#include <omp.h>

#define X_MAX 10000
#define Y_MAX 10000

#define MAX_COLOR_VAL 255

#define MAX_NUM_OF_THREADS 8

#define NUM_OF_THREADS 8

FILE * fp;

unsigned char ppm_arr[Y_MAX][X_MAX];

int main()
{

	char *filename="new1.ppm";

	static unsigned char thread_colors[MAX_NUM_OF_THREADS + 1][3] =
	{
		{0,0,255},
		{0,255,0},
		{255, 0, 0},
		{103,99,119},
		{225,248,114},
		{206,60,16},
		{0,0,0},
		{29,137,2},
		{255,255,255}
	};

	
	fp= fopen(filename,"wb"); /* b -  binary mode */

	fprintf(fp,"P6\n # \n %d\n %d\n %d\n", X_MAX, Y_MAX, MAX_COLOR_VAL);

	int  nthreads, id;
	double start_time, end_time;

	start_time = omp_get_wtime();
	const double CxMin=-2.5;
	const double CxMax=1.5;
	const double CyMin=-2.0;
	const double CyMax=2.0;

	const int IterationMax=200;
	
	const double EscapeRadius=2;
	double ER2=EscapeRadius*EscapeRadius;

	double PixelWidth=(CxMax-CxMin)/X_MAX;
	double PixelHeight=(CyMax-CyMin)/Y_MAX;

	double Cx,Cy;
	double Zx, Zy;
	double Zx2, Zy2; 
	int Iteration;
	
	int iY, iX;

	unsigned char color;
			
	/* sprawozdanie omowienie zadania, przerobienie kodu - wstep
	 * 2. badania: czasy dla roznej liczby watkow, dla roznej liczby rozmiarow
	 * 3. dla roznych schedule, static, dynamic, rozne chunk size
	 * 4. wnioski*/
	#pragma omp parallel private(nthreads, id) num_threads(NUM_OF_THREADS)
	{
		id = omp_get_thread_num();
		#pragma omp for private(Cx, Cy, Zx, Zy, Zx2, Zy2, Iteration, iY, iX, color) schedule(static, 100)
		for (iY = 0; iY < Y_MAX; iY++)
		{
		    Cy = CyMin + iY*PixelHeight;
		    if (fabs(Cy) < PixelHeight/2)
		    {
			    Cy=0.0;
		    }
		    for (iX=0; iX < X_MAX; iX++)
		    {         
			    Cx=CxMin + iX*PixelWidth;
			    Zx=0.0;
			    Zy=0.0;
			    Zx2=Zx*Zx;
			    Zy2=Zy*Zy;

			    for (Iteration = 0; Iteration < IterationMax && ((Zx2+Zy2)<ER2); Iteration++)
			    {
				Zy=2*Zx*Zy + Cy;
				Zx=Zx2-Zy2 +Cx;
				Zx2=Zx*Zx;
				Zy2=Zy*Zy;
			    }

			    if (Iteration==IterationMax)
			    { 
				color = MAX_NUM_OF_THREADS;
			    }
			    else 
			    {
				color = id;
			    }

			    ppm_arr[iY][iX] = color;
			}
		}
	}
	end_time = omp_get_wtime();

	printf("time: %.6f\tnr of threads: %d\n", (end_time - start_time), NUM_OF_THREADS);

	for (int y = 0; y < Y_MAX; y++)
	{
	    for (int x=0; x < X_MAX; x++)
	    {
		fwrite(&thread_colors[ppm_arr[y][x]], 1, 3, fp);
	    }
	}
	fclose(fp);
	return 0;
}
