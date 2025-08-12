#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

struct info
{
	char ime[400];
	long size;
};

int obradiDir(char* path, struct info* files, int* numOfFiles);

int main(int argc, char* argv[])
{
	struct stat statbuff;
	struct info files[200];
	int ukupnoFiles;
	int i, j;
	struct info pom;
	char path[1024];

	if(argc < 2)
	{
		printf("Niste uneli direktorijum!\n");
		return -1;
	}

	if(stat(argv[1], &statbuff) < 0)
	{
		printf("Greska sa vadjenjem statusa direktorijuma prosledjenog!\n");
		return -1;
	}

	if(!S_ISDIR(statbuff.st_mode))
	{
		printf("Niste prosledili direktorijum!\n");
		return -1;
	}

	obradiDir(argv[1], files, &ukupnoFiles);

	for(i = 0; i < ukupnoFiles - 1; i++)
	{
		for(j = i+1; j < ukupnoFiles; j++)
		{
			if(files[i].size > files[j].size)
			{
				pom = files[i];
				files[i] = files[j];
				files[j] = pom;
			}
		}
	}

	for(i = 0; i < ukupnoFiles; i++)
	{
		printf("%d > %s [%ld]\n", (i+1), files[i].ime, files[i].size);
	}

	return 0;
}

int obradiDir(char* path, struct info* files, int* numOfFiles)
{
	DIR* dir;
	struct stat statbuff;
	struct dirent* dirp;
	char path1[1024];

	dir = opendir(path);

	if(!dir)
	{
		printf("Greska sa dir!\n");
		return -1;
	}

	while((dirp = readdir(dir)) != NULL)
	{
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		strcpy(path1, path);
		strcat(path1, "/");
		strcat(path1, dirp->d_name);

		if((stat(path1, &statbuff)) < 0)
		{
			printf("Greska sa stat!\n");
			return -1;
		}

		if(S_ISDIR(statbuff.st_mode))
			obradiDir(path1, files, numOfFiles);
		else if(S_ISREG(statbuff.st_mode) && (strchr(dirp->d_name, 'p') != NULL))
		{
			strcpy(files[*numOfFiles].ime, dirp->d_name);
			files[*numOfFiles].size = statbuff.st_size;
			(*numOfFiles)++;
		}

	}

	return 0;

}


