#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

	uid_t uid;
	gid_t gid;
	/*uid = getuid();
	gid = getgid();
	struct passwd* guid;
	guid = getpwuid(uid);
	struct group* ggid;
	ggid = getgrgid(gid);*/

void allgroups(uid_t uid, int a)
{
	uid = getuid();
	gid = getgid();
	struct group* ggid;
	ggid = getgrgid(gid);
	
	int i, j;
	i = 0;
	for(j = 0; j < 3; ++j)
	{
		char** gmem;
		gmem = getgrent() -> gr_mem;
		while(i == 0)
		{
			if(strcmp(*gmem, (ggid -> gr_name)) == 0)
			{
				i = 1;
				if(a == 0)
					printf("%d", (ggid -> gr_gid));
				else
					printf("%d(%s) ", (ggid -> gr_gid), ggid -> gr_name);
			}
			gmem++;
		}
	}
}

int main(int argc, char ** argv)
{
	uid = getuid();
	gid = getgid();
	printf("I'm came1\n");
	int u, g, G, a;
	u = g = G = a = 0;
	if (strcmp(argv[1], "-u") == 0)
		u = 1;
	if(strcmp(argv[1], "-g") == 0)
		g = 1;
	if(strcmp(argv[1], "-G") == 0)
		G = 1;
	else
		a = 1;
	if(u == 1)
	{
		printf("%d", uid);
	}
	else if(g == 1)
	{
		printf("%d", gid);
	}
	else if(G == 1)
	{
		allgroups(uid, a);
	}
	else 
	{
		printf("id = %d, gid = %d\n", uid, gid);
		
		struct passwd* guid;
		guid = getpwuid(uid);
		printf("uname = %s\n", (guid -> pw_name));
		
		struct group* ggid;
		ggid = getgrgid(gid);
		printf("gname = %s\n", (ggid -> gr_name));
		
		allgroups(uid, a);
	}
	
	return 0;
}
