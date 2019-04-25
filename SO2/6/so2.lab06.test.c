#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
#include <unistd.h>
#include <string.h>
//#include <crypt.h> tylko dla crypt_r

int main(int argc, char ** argv)
{
	char * pass = NULL;
	char * salt = NULL;
	int opt;
	opterr = 0;

	while((opt = getopt(argc, argv, "p:s:"))!= -1)
	{
		switch(opt)
		{
		case 'p':
			pass = optarg;
			printf("pass:%s\n", pass);
			break;
		case 's':
			salt = (char *)malloc(sizeof("$6$") + sizeof(optarg) + sizeof("$") + 1);
			strcpy(salt, "$6$");
			strcat(salt, optarg);
			strcat(salt, "$");
			printf("salt:%s\n", optarg);
			break;
		default:
			fprintf(stderr, "BAD BOY\n");
			exit(EXIT_FAILURE);
		}
	}
	if((pass == NULL) || (salt == NULL))
	{
		fprintf(stdout, "Zla liczba argumentow.\nnp. ./a.out -p [haslo] -s [domieszka].\n");
		exit(1);
	}

	char * res = crypt(pass, salt);
	if(res == NULL)
	{
		fprintf(stdout, "sie zesralo.\n");
		exit(1);
	}
	fprintf(stdout, "Haslo: %s, Domieszka: %s\nWynik: %s\n",pass,salt,res);
	char * hash = (char *)malloc(86+1);//taki rozmiar w manualu
	strncpy(hash, res + strlen(salt), 86);
	fprintf(stdout, "Hash: %s\n",hash);
	free(res);
	free(hash);
	free(salt);
	exit(0);
}
