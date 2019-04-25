#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>

#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

char * grpserv(uid_t _entry)
{
 	//strcpy(retarr, _entry->ut_user);
 	//strcat(retarr, " ");
  char * retarr = (char *)malloc(sizeof(char) * 512);
 	struct passwd * pd = getpwuid(_entry);
	gid_t groups[100];
	int grsize = 100;
	//getgrouplist(_entry->ut_user, pd->pw_gid, groups, &grsize);
  getgrouplist(pd->pw_name, pd->pw_gid, groups, &grsize);

	for(int i = 0; i < grsize; i++)
	{
		if(i==0) strcpy(retarr, getgrgid(groups[i])->gr_name);
    else
    {
      strcat(retarr, " ");
      strcat(retarr, getgrgid(groups[i])->gr_name);
    }
	}
	return retarr;
}
