#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv)
{
	if(argc == 1)
	{
		fprintf(stdout, "za malo parametrow\n");
		exit(1);
	}

	int len;

	char * firsthalf;
	char * secondhalf;

	len = strlen(argv[argc-1]);

	if(len == 1)
	{
		fprintf(stdout, "%d",getpid());
		for(int i = 1; i < argc; i++)
		{
			fprintf(stdout, " %s", argv[i]);
		}
		fprintf(stdout, "\n");
		exit(1);
	}
	if((len & (len -1)) != 0)
	{
		fprintf(stdout, "zla dlugosc parametru\n");
		exit(1);
	}

	firsthalf = (char *)malloc(sizeof(char)*(len/2) + 1);//tak wiem, ze sizeof(char to 1)
	secondhalf = (char *)malloc(sizeof(char)*(len/2) + 1);//tak wiem, ze sizeof(char to 1)

	strncpy(firsthalf, argv[argc - 1], (len/2));
	strncpy(secondhalf, argv[argc - 1] + (len/2), (len/2));

	firsthalf[(len/2) + 1] = '\0';
	secondhalf[(len/2) + 1] = '\0';

	char ** arglist1 = (char **)malloc(sizeof(char *) * (argc + 2));
	for(int i = 0; i < argc; i++)
	{
		arglist1[i] = (char *)malloc(sizeof(char) * strlen(argv[i]));
		arglist1[i] = argv[i];
	}
	arglist1[argc] = firsthalf;
	arglist1[argc + 1] = NULL;

	char ** arglist2 = (char **)malloc(sizeof(char *) * (argc + 2));
	for(int i = 0; i < argc; i++)
	{
		arglist2[i] = (char *)malloc(sizeof(char) * strlen(argv[i]));
		arglist2[i] = argv[i];
	}

	arglist2[argc] = secondhalf;
	arglist2[argc + 1] = NULL;

	pid_t p = fork();
	if(p == 0)
	{
		execv(argv[0], arglist1);
	}
	else
	{
		pid_t p2 = fork();
		if(p2 == 0)
		{
			execv(argv[0], arglist2);
		}
		else
		{
			fprintf(stdout, "%d",getpid());
			for(int i = 1; i < argc; i++)
			{
				fprintf(stdout, " %s", argv[i]);
			}
			fprintf(stdout, "\n");
			waitpid(p, NULL, 0);
			waitpid(p2, NULL, 0);
		}
	}
	free(arglist1);
	free(arglist2);
	free(firsthalf);
	free(secondhalf);
}
