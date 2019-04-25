#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>

#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

#include <dlfcn.h>

char *(*fgrpserv)(uid_t);

int main(int argc, char ** argv)
{
  int hflag = 0;
  int gflag = 0;
  int index;
  int opt;
  opterr = 0;

	void * handle = dlopen("./libfetchuser.so",RTLD_LAZY);

	if (!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
	}
	if(handle)
	{
		fgrpserv = dlsym(handle, "grpserv");
	}
  while((opt = getopt(argc, argv, "hg"))!= -1)
  {
    switch(opt)
    {
      case 'h':
      hflag = 1;
      break;
      case 'g':
      gflag = 1;
      break;
      default:
      fprintf(stderr, "BAD BOY\n");
      exit(EXIT_FAILURE);
    }
  }
	struct utmp * entry = NULL;

	while((entry = getutent())!= NULL)
	{
		if(entry->ut_type != USER_PROCESS) continue;
		//fprintf(stdout, "%s ", entry->ut_user);
		fprintf(stdout, "%s ", entry->ut_user);
		struct passwd * pd = getpwnam(entry->ut_user);
		if(hflag == 1) fprintf(stdout, "%s ", entry->ut_host);
		if((handle != NULL) && (gflag == 1))
		{
			//char hold[512];
			//fgrpserv(entry, hold);
			char * hold = fgrpserv(pd->pw_uid);
			fprintf(stdout, "%s", hold);
		}
    fprintf(stdout, "\n");
	}
	dlclose(handle);
}
