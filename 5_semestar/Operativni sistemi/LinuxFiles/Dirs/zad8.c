#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int obradiDir(char* path);

int main(int argc, char* argv[])
{
	struct stat statbuf;

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

	obradiDir(argv[1]);

	return 0;
}

int obradiDir(char* path)
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
			obradiDir(path1);
		}
		else if(S_ISREG(statbuf.st_mode) && strcmp(dirp->d_name + strlen(dirp->d_name) - 3, ".sh") == 0)
		{
			if(fork() == 0)
			{
				printf("%s\n\t\t%s\n", path1, dirp->d_name);
				execlp(path1, dirp->d_name, NULL);
				printf("\n\nGreska sa : %s\n\n", path1);
			}
			else
			{
				wait(NULL);
			}
		}

	}


	return 0;
}
