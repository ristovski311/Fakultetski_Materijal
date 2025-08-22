#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/file.h>
#include <sys/types.h>

void exer(const char* msg)
{
	printf("\nGreska\n%s\n", msg);
	exit(1);
}

void obradiDir(const char* path, const char* str);

int main(int argc, char* argv[])
{
	struct stat sb;

	if(argc < 3) exer("Nedovoljno argumenata!");

	if(stat(argv[1], &sb) == -1) exer("Greska kod stat u main");

	if(S_ISDIR(sb.st_mode))
		obradiDir(argv[1], argv[2]);
	else
		exer("Niste prosledili direktorijum");

	return 0;
}

void obradiDir(const char* argpath, const char* str)
{
	DIR* dp;
	struct dirent* dirp;
	struct stat sb;

	char path[512];

	if((dp = opendir(argpath)) == NULL) exer("Greska pri otvaranju dir u obradi");

	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		sprintf(path, "%s/%s", argpath, dirp->d_name);

		if(stat(path, &sb) == -1) exer("Greska kod stat u obradi");

		if(S_ISDIR(sb.st_mode))
			obradiDir(path, str);
		else if(S_ISREG(sb.st_mode) && strstr(dirp->d_name, str) != NULL)
			printf("DATOTEKA | %s\n", path);

	}
}



