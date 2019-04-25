#define _XOPEN_SOURCE
#define _GNU_SOURCE
#define BLOCK 200
#define BILLION 1E9

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>

void * calchash(void * vptr_args);
long int * calclines(const char *, int);
long int * cleff(const char *, int);
void callthreads(const char *, const char *, const char *, int, int, int);
void calcefficency(const char *, const char *, const char *);

typedef struct args{
	const char * filename;
	const char * hash;
	const char * salt;
	long int start;
	long int end;
	int iter;
} args;

volatile sig_atomic_t passflag = 0;
volatile sig_atomic_t doneflag = 0;

typedef struct pgr{
	int progress;
	long int size;
} pgr;

pgr * spgr = NULL;
//int * progress;
char * broken = NULL;
long int fileend = 0;

int main(int argc, char ** argv)
{
	char * salt = NULL;
	char * filename = NULL;
	char * hash = NULL;
	int threadn = 0;
	int opt;
	opterr = 0;

	while((opt = getopt(argc, argv, "t:s:f:h:"))!= -1)
	{
		switch(opt)
		{
		case 't':
			//if(optarg[0] == '0') break;
			threadn = atoi(optarg);
			break;
		case 's':
			salt = optarg;
			break;
		case 'f':
			filename = optarg;
			break;
		case 'h':
			hash = optarg;
			break;
		default:
			fprintf(stderr, "BAD BOY\n");
			exit(EXIT_FAILURE);
		}
	}

	if(filename == NULL || salt == NULL || hash == NULL)
	{
		fprintf(stdout, "Insufficient args.\n./a.out -f [filename] -s [salt] -h [hash] -t [num of threads, 0 = max]\n");
		exit(EXIT_FAILURE);
	}
	if(threadn > sysconf(_SC_NPROCESSORS_CONF)) threadn = sysconf(_SC_NPROCESSORS_CONF);
	fprintf(stdout, "processors online: %d.\n", threadn);
	if(threadn != 0)callthreads(filename, salt, hash, threadn, 1, 1);
	else calcefficency(filename, salt, hash);
	exit(0);
}

long int * calclines(const char * filename, int div)
{
	FILE * f = fopen(filename, "r");
	char ch;
	int lines = 0, iter = 0;
	while(!feof(f))
	{
		ch = fgetc(f);
		if(ch == '\n') lines++;
	}

	int block = lines/div;
	int blines = 0;

	long int * res = (long int *)malloc(sizeof(long int)*div);

	fseek(f, 0, SEEK_SET);

	while(!feof(f))
	{
		ch = fgetc(f);
		if(ch == '\n') blines++;
		if(blines == block)
		{
			res[iter] = ftell(f);
			iter++;
			blines = 0;
		}
	}
	fseek(f, 0, SEEK_END);
	fileend = ftell(f);
	fclose(f);
	return res;
}

void * calchash(void * vptr_args)
{
	args * ptr = (args *)vptr_args;
	FILE * f = fopen(ptr->filename, "r");

	//printf("created a thread.\nthread id = %d\nstart = %ld\nend = %ld\n threadn = %d\n\n", pthread_self(), ptr->start, ptr->end, ptr->iter);

	long int size;
	if(ptr->end!=-1) size = ptr->end - ptr->start;
	else
	{
		size = fileend - ptr->start;
	}
	spgr[ptr->iter].size = size;
	char * buffer = (char *)malloc(sizeof(char)*size + 1);

	fseek(f, ptr->start, SEEK_SET);
	fread(buffer,1,size,f);
	//printf("%s\n", buffer);
	char * salt = (char *)malloc(strlen("$6$") + strlen(ptr->salt) + strlen("$") + 1);
	strcpy(salt, "$6$");
	strcat(salt, ptr->salt);
	strcat(salt, "$");

	struct crypt_data cryptsave;
	cryptsave.initialized = 0;
	char * res = NULL;//(char *)malloc(86);//taki rozmiar w manualu
	char * passhash = NULL;
	char * hold = NULL;
	char * savestr = NULL;
	char * token = strtok_r(buffer,"\n",&savestr);
	int saltsize = 0;

	while(token != NULL)
	{
		if(passflag == 1) pthread_exit(NULL);
		hold = malloc(strlen(token) + 1);
		strcpy(hold, token);
		res = crypt_r(hold, salt, &cryptsave);
		passhash = (char *)malloc(86 + 1);

		saltsize = strlen(salt);
		strncpy(passhash, res + saltsize, 86);

		if(strcmp(passhash, ptr->hash) == 0)
		{
			printf("Thread nr %d found the password!\n", ptr->iter);
			passflag = 1;
			broken = token;
			fclose(f);
			pthread_exit(NULL);
		}
		free(passhash);
		free(hold);
		spgr[ptr->iter].progress++;
		token = strtok_r(NULL,"\n",&savestr);
	}
	//printf("wtf\n");
	doneflag++;
	free(salt);
	free(buffer);
	fclose(f);
	pthread_exit(NULL);
}

void callthreads(const char * filename, const char * salt, const char * hash, int threadn, int wout, int calc)
{
	pthread_t * tarr = (pthread_t *)malloc(sizeof(pthread_t)*threadn);
	spgr = (pgr *)malloc(sizeof(pgr) * threadn);
	long int * lines;
	//printf("jestem tu\n");

	if(calc) lines = calclines(filename, threadn);
	else lines = cleff(filename, threadn);
	args * passarg = (args *)malloc(sizeof(args) * threadn);
	for(int i = 0; i < threadn; i++)
	{
		spgr[i].progress = 0;
		//progress[i] = 0;
		passarg[i].filename = filename;
		passarg[i].salt = salt;
		passarg[i].hash = hash;
	}

	for(int i = 0; i < threadn; i++)
	{
		if(i == 0)
		{
			passarg[i].start = 0;
			passarg[i].end = lines[0];
		}
		else
		{
			passarg[i].start = lines[i-1];
			passarg[i].end = lines[i];
		}
		passarg[i].iter = i;
		pthread_create(&tarr[i], 0, &calchash, &passarg[i]);
	}

	//printf("\n\n\n");
	if(wout)
	{
		while(!passflag)
		{
			if(doneflag == threadn) break;
			printf("\033[2J");
			//printf("done flag = %d threadn = %d", doneflag, threadn);
			for(int i = 0; i < threadn; i++) printf("Thread nr:(%d) tested %d passwords\t %.2f %%\n", i, spgr[i].progress, ((1.0*100*spgr[i].progress)/(1.0*spgr[i].size)));
			sleep(1);
		}

		printf("\033[2J");
		for(int i = 0; i < threadn; i++) printf("Thread nr:(%d) tested %d passwords\t %.2f %%\n", i, spgr[i].progress, ((1.0*100*spgr[i].progress)/(1.0*spgr[i].size)));
	}

	for(int i = 0; i < threadn; i++)
	{
		pthread_join(tarr[i], NULL);
	}
	if(wout)
	{
		if(passflag == 0) printf("Couldn't break hash.\n");
		else printf("\nZnalezione haslo: %s\n", broken);
	}
	free(spgr);
	free(passarg);
	free(tarr);
	free(lines);
	passflag = 0;
	doneflag = 0;
}

long int * cleff(const char * filename, int div)
{
	//printf("jestem tu\n");
	FILE * f = fopen(filename, "r");
	if(f==NULL) printf("Couldn't open file.\n");
	char ch;
	int lines = 0, iter = 0;
	while(!feof(f))
	{
		ch = fgetc(f);
		if(ch == '\n') lines++;
		if(lines == 1000)
		{
			fileend = ftell(f);
			break;
		}
	}
	if(lines < 1000)
	{
		fprintf(stderr, "Can't calculate efficency, file is too small.\n");
		exit(EXIT_FAILURE);
	}
	int block = lines/div;
	int blines = 0;

	long int * res = (long int *)malloc(sizeof(long int)*div);


	fseek(f, 0, SEEK_SET);
	while(!feof(f))
	{
		ch = fgetc(f);
		if(ch == '\n') blines++;
		if(blines == block)
		{
			res[iter] = ftell(f);
			iter++;
			blines = 0;
		}
		if(iter == div) break;
	}
	//printf("jestem tu\n");

	//fseek(f, 0, SEEK_END);

	fclose(f);
	return res;
}

void calcefficency(const char * filename, const char * salt, const char * hash)
{
	struct timespec start, stop;
	int threadn = sysconf(_SC_NPROCESSORS_CONF);
	//double * results = (double *)malloc(sizeof(double)*threadn);
	double res = 0;
	//printf("jestem tu\n");
	for(int i = 1; i <= threadn; i++)
	{
		clock_gettime(CLOCK_REALTIME, &start);
		callthreads(filename, salt, hash, i, 0, 0);
		clock_gettime(CLOCK_REALTIME, &stop);
		res = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)/BILLION;
		printf("For %d threads it takes %lfs to crack 1K passwords\n",i,res);
	}


}
