#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <dirent.h>
#include <string.h>
#include <memory.h>

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(1);
}

struct info
{
	char name[1024];
	long size;
};


void obradiDir(const char* argpath, struct info** files, int* numFiles);


int main(int argc, char* argv[])
{
	struct stat sb;
	struct info* files = NULL;
	int numFiles = 0;

	if(argc < 2) exer("Niste uneli putanju!");

	if(stat(argv[1], &sb) == -1) exer("Stat greska u main");

	if(S_ISDIR(sb.st_mode))
		obradiDir(argv[1], &files, &numFiles);
	else
		exer("Niste prosledili dir!");

	for(int i = 0; i < numFiles - 1; i++)
	{
		for(int j = i + 1; j < numFiles; j++)
		{
			if(files[i].size > files[j].size)
			{
				struct info temp;
				strcpy(temp.name, files[i].name);
				temp.size = files[i].size;
				strcpy(files[i].name, files[j].name);
				files[i].size = files[j].size;
				strcpy(files[j].name, temp.name);
				files[j].size = temp.size;
			}
		}
	}

	printf("\n%4s %-70s %10s\n","IND", "NAME", "SIZE");

	for(int i = 0; i < numFiles; i++)
		printf("%3d. %-70s %10ld\n", i+1, files[i].name, files[i].size);

	return 0;
}


void obradiDir(const char* argpath, struct info** files, int* numFiles)
{
	DIR* dp;
	struct stat sb;
	struct dirent* dirp;

	char path[1024];

	if((dp = opendir(argpath)) == NULL) exer("Greska pri otvaranju dir!");

	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp->d_name, "..") == 0 ||strcmp(dirp->d_name, ".") == 0)
			continue;

		sprintf(path, "%s/%s", argpath, dirp->d_name);

		if(stat(path, &sb) == -1) exer("Stat greska u obradiDir");

		if(S_ISDIR(sb.st_mode))
			obradiDir(path, files, numFiles);
		else if(S_ISREG(sb.st_mode))
		{
			if(strchr(dirp->d_name, 'p') != NULL)
			{
				printf("Obrada %s | numFiles: %d\n", dirp->d_name, *numFiles);
				struct info* temp = (struct info*)realloc(*files, ((*numFiles)+1)*sizeof(struct info));
				if(temp == NULL) exer("Greska pri realloc");
				*files = temp;
				(*files)[*numFiles].size = sb.st_size;
				strcpy((*files)[*numFiles].name, path);
				printf("Idalje obrada %s | name: %s | size: %ld\n", dirp->d_name,(*files)[*numFiles].name, (*files)[*numFiles].size);
				*numFiles += 1;
			}
		}
	}

	rewinddir(dp);
	closedir(dp);
}
