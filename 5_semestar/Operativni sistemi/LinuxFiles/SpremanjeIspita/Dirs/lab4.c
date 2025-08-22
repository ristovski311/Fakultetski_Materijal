#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/file.h>

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(1);
}

void prikaziDir(const char* argpath);

void obradiDir(const char* argpath, int* files, long* size);

int main(int argc, char* argv[])
{
	struct stat sb;

	if(argc < 2) exer("Nedovoljno argumenata");
	if(stat(argv[1], &sb) == -1) exer("Greska stat u main");
	if(S_ISDIR(sb.st_mode))
	{
		printf("%-25s%10s%15s\n", "NAME", "FILES", "SIZE");
		prikaziDir(argv[1]);
	}
	else
		exer("Niste uneli direktorijum!");

	return 0;
}

void prikaziDir(const char* argpath)
{
	DIR* dp;
	struct dirent* dirp;
	struct stat sb;
	long size;
	int files;

	char path[512];

	if((dp = opendir(argpath)) == NULL) exer("Greska pri otvaranju dir u prikaziDir");

	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp->d_name, "..") == 0 || strcmp(dirp->d_name, ".") == 0)
			continue;

		sprintf(path, "%s/%s", argpath, dirp->d_name);

		if(stat(path, &sb) == -1) exer("Stat u prikaziDir");

		if(S_ISDIR(sb.st_mode))
		{
			size = 0;
			files = 0;
			obradiDir(path, &files, &size);
			printf("%-25s%10d%15ld\n", dirp->d_name, files, size);
		}
	}

	return;
}

void obradiDir(const char* argpath, int* files, long* size)
{
	DIR* dp;
	struct dirent* dirp;
	struct stat sb;

	char path[512];

	if((dp = opendir(argpath)) == NULL) exer("Greska pri otvaranju dir u obradiDir");

	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp->d_name, "..") == 0 || strcmp(dirp->d_name, ".") == 0)
			continue;

		sprintf(path, "%s/%s", argpath, dirp->d_name);

		if(stat(path, &sb) == -1) exer("Stat u obradiDir");

		if(S_ISDIR(sb.st_mode))
		{
			obradiDir(path, files, size);
		}
		else if(S_ISREG(sb.st_mode))
		{
			(*files)++;
			(*size) += sb.st_size;
		}
	}


}
