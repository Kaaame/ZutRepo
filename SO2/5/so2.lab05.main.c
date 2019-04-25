#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

void recurse(const char *,const char *, int);

int maxdepth = 100;
int dflag = 0;
int fflag = 0;
int lflag = 0;
int Lflag = 0;
int kflag = 0;

int dircount = 0;
int filecount = 0;


int main(int argc, char ** argv)
{
	char * kdir = NULL;

	int opt;
	opterr = 0;
	while((opt = getopt(argc, argv, "dlfL:k:"))!= -1)
	{
	    switch(opt)
		{
			case 'd':
			dflag = 1;
			break;
			case 'l':
			lflag = 1;
			break;
			case 'f':
			fflag = 1;
			break;
			case 'L':
			maxdepth = atoi(optarg);
			Lflag = 1;
			break;
			case 'k':
			kflag = 1;
			kdir = optarg;
			break;
			case '?':
			fprintf(stderr, "BAD BOY\n");
			exit(EXIT_FAILURE);
		}
	}

	if(dflag) fprintf(stdout, "-d \n");
	if(lflag) fprintf(stdout, "-l \n");
	if(fflag) fprintf(stdout, "-f\n");
	if(Lflag) fprintf(stdout, "-L\n");
	if(kflag) fprintf(stdout, "-k %s\n", kdir);

	DIR * dir;
	struct dirent * ds;
	if(kflag) dir = opendir(kdir);
	else dir = opendir(".");
	int counter = 0;


	if(dir == NULL)
	{
		fprintf(stderr, "Cannot open directory.\n");
		exit(1);
	}
	while((ds = readdir(dir))!=NULL)
	{
		if((strcmp(ds->d_name, ".") == 0) || (strcmp(ds->d_name, "..") == 0)) continue;
		if(ds->d_name[0] == '.') continue;
		switch(ds->d_type)
		{
			case DT_DIR://directory
				fprintf(stdout, "DIR: %s\n", ds->d_name);
				dircount++;
				if(kflag) recurse(ds->d_name, kdir, counter+1);
				else recurse(ds->d_name, ".", counter+1);
			break;
			case DT_REG://file
				if(!dflag)
				{
					fprintf(stdout, "FILE: %s\n", ds->d_name);

				}
			break;
			case DT_LNK://link
				if(!dflag)
				{
					fprintf(stdout, "LINK: %s\n", ds->d_name);

				}
			break;

		}

	}
	closedir(dir);
	fprintf(stdout, "Files: %d\tDirectories: %d\n", filecount, dircount);

}

void recurse(const char * dir, const char * path, int tablen)
{

	DIR * rdir;
	if(dir[0] == '.') return;
	if(tablen == maxdepth) return;

	char * newpath = (char *)malloc(strlen(dir) + strlen(path) + 2);
	strcpy(newpath, path);
	strcat(newpath, "/");
	strcat(newpath, dir);


	rdir = opendir(newpath);
	if(rdir == NULL) return;
	struct dirent * ds;

	while((ds = readdir(rdir))!=NULL)
	{
		if((strcmp(ds->d_name, ".") == 0) || (strcmp(ds->d_name, "..") == 0)) continue;
		switch(ds->d_type)
		{
			case DT_DIR://directory
				for(int i = 0; i < tablen; i++) fprintf(stdout, "\t");
				fprintf(stdout, "DIR: %s\n", ds->d_name);
				dircount++;
				recurse(ds->d_name, newpath, tablen+1);
			break;
			case DT_REG://file
				if(!dflag)
				{
					for(int i = 0; i < tablen + 1; i++) fprintf(stdout, "\t");
					fprintf(stdout, "FILE: %s\n", ds->d_name);
					filecount++;
				}
			break;
			case DT_LNK://link
				if(!dflag)
				{
					for(int i = 0; i < tablen + 1; i++) fprintf(stdout, "\t");
					fprintf(stdout, "LINK: %s\n", ds->d_name);
				}
			break;

		}

	}
	free(newpath);
	closedir(rdir);
}
