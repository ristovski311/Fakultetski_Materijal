#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define CT 5

struct info
{
	char path[100];
	long size;
};

int obradiDir(char* path, struct info* files, int* count);

int main(int argc, char* argv[])
{
	struct stat statbuf;
	struct info files[CT];
	int i;
	int count = 0;

	if(argc < 2)
	{
		printf("Greska, nije proslednjen folder!\n");
		return -1;
	}

	if(stat(argv[1], &statbuf) == -1)
	{
		printf("Greska, stat u main-u!\n");
		return -1;
	}

	if(!S_ISDIR(statbuf.st_mode))
	{
		printf("Greska, niste prosledili direktorijum!\n");
		return -1;
	}

	obradiDir(argv[1], files, &count);

	for(i = 0; i < CT; i++)
	{
		printf("%d\t%-60s\t[%ld]\n", (i+1) ,files[i].path, files[i].size);
	}

	return 0;
}

int obradiDir(char* path, struct info* files, int* count)
{
	DIR* dir;
	struct dirent* dirp;
	struct stat statbuf;
	char path1[1024];
	int i;

	dir = opendir(path);
	if(!dir)
	{
		printf("Neuspesno otvoren dir %s!\n", path);
		return -1;
	}

	while((dirp = readdir(dir)) != NULL)
	{
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		strcpy(path1, path);
		strcat(path1, "/");
		strcat(path1, dirp->d_name);

		if(stat(path1, &statbuf) == -1)
		{
			printf("Greska! Stat je vratio -1\n");
			return -1;
		}

		if(S_ISDIR(statbuf.st_mode))
		{
			obradiDir(path1, files, count);
		}
		else if(S_ISREG(statbuf.st_mode))
		{
			if(*count < CT)
			{
				strcpy(files[*count].path, path1);
				files[*count].size = statbuf.st_size;
				(*count)++;
			}
			else
			{
				for(i = 0; i < CT; i++)
				{
					if(files[i].size > statbuf.st_size)
					{
						strcpy(files[i].path, path1);
						files[i].size = statbuf.st_size;
						break;
					}
				}
			}
		}

	}


	return 0;
}
