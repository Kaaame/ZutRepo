#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

int main(int argc, char ** argv)
{
  int hflag = 0;
  int gflag = 0;
  int index;
  int opt;
  opterr = 0;


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
  while((entry = getutent()) != NULL)
  {
    if(entry->ut_type != USER_PROCESS) continue;
    fprintf(stdout, "%s ", entry->ut_user);
    if(hflag) fprintf(stdout, "%s ", entry->ut_host);
    if(gflag)
    {
      struct passwd * pd = getpwnam(entry->ut_user);
      gid_t groups[100];
      int grsize = 100;
      getgrouplist(entry->ut_user, pd->pw_gid, groups, &grsize);
      for(int i = 0; i < grsize; i++)
      {
        fprintf(stdout, " %s", getgrgid(groups[i])->gr_name);
      }
    }
    fprintf(stdout, "\n");
  }
  exit(EXIT_SUCCESS);
}
