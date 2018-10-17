//Не знаю, как печатать правильно формат вывода прав от функции статус в -l, рекурсия ломается на сегфалте.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <getopt.h>
#include <unistd.h>

void foo(char* name) { //name = currentdir;
	printf("%s\n", name);
	int i1, i2 = 0;                 
	char ** array_of_names;
	array_of_names = (char**)calloc(100, sizeof(char*));
	for (i1 = 0; i1 < 100;i1++) {
		array_of_names[i1] = (char*)calloc(100,sizeof(char));
	}
	DIR* d = opendir(name);
	struct dirent* dent;
	while((dent = readdir(d)) != NULL) {
		struct stat buf;
		stat(dent -> d_name, &buf); 
		printf("\n");
		printf ("mode=%d\n", buf.st_mode);
		if(S_ISDIR(buf.st_mode)) { 
			strcpy(array_of_names[i2], name);                 
			i2++;
		}
		printf("%s", dent -> d_name);
	}
	printf("\n\n\n");
	int j;
	for (j = 0; j < i2; ++j) {
		foo(array_of_names[j]);
	}
	for (i1 = 0; i1 < 100; i1++) {
		free(array_of_names[i1]);
	}
	free(array_of_names);
	closedir(d);
}

int a, l, R;
static struct option long_options[] = {
	{"all", no_argument, NULL, 'a'}, 
	{"l", no_argument, NULL, 'l'},
	{"recursive", no_argument, NULL, 'R'} 
};
int flag_a, flag_l, flag_R, flag_no, option_index, opt;

int main(int argc, char ** argv)
{
	
	char* currentdir;
	if (argc > 1) {
	while((opt = getopt_long(argc, argv, "alR", long_options, & option_index)) != -1) {
		switch (opt) {
               case 'a':
                   flag_a = 1;
                   break;
               case 'l':
                   flag_l = 1;
                   break;
               case 'R':
                   flag_R = 1;
                   break;
               }
		}
	}
    else
		flag_no = 1;
    currentdir = argv[optind];
    if(currentdir == NULL)
		currentdir = ".";
	DIR* d = opendir(currentdir);
	struct dirent* dent;
	if(flag_a == 1) {
			while((dent = readdir(d))!= NULL)
			{
				currentdir = dent -> d_name;
				printf("%s ", currentdir);
			}
	}
	if(flag_no == 1) {
		while((dent = readdir(d))!= NULL)
			{
				currentdir = dent -> d_name;
				if(currentdir[0] == '.')
					continue;
				printf("%s ", currentdir);
			}
	}
	if(flag_l == 1) {
		while((dent = readdir(d))!= NULL)
			{
				currentdir = dent -> d_name;
				struct stat* buf;
				stat(dent, buf);
				printf("%d\t%l\t%l\t",buf->st_mode, buf->st_ino, buf->st_uid);
				printf("%u\t%l\t%l\t%l\t", buf->st_gid, buf->st_size, buf->st_nlink, buf->st_ctime);
				printf("%s ", currentdir);
				printf("\n");
			}
	}
	if(flag_R == 1) {
		foo(currentdir);
	}
	closedir(d);
	return 0;
}

