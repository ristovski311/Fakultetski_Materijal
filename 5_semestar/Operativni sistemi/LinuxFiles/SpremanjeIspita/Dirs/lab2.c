#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>

void exer(const  char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(1);
}

void obradiDir(char* path);

int main(int argc, char* argv[])
{
	struct stat statbuf;

	if(argc < 2) exer("Niste prosledili argument!");

	if(stat(argv[1], &statbuf) == -1) exer("Stat za argument los");

	if(S_ISDIR(statbuf.st_mode))
		obradiDir(argv[1]);
	else
		exer("Niste prosledili direktorijum!");

	return 0;
}

void obradiDir(char* argpath)
{
	DIR* dp;
	struct dirent* dirp;
	struct stat statbuf;

	int brojanje[3] = {0,0,0}; //datoteke | direktorijumi | linkovi

	char path[512];

	if((dp = opendir(argpath)) == NULL) exer("Nije otvoren direktorijum!");

	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		sprintf(path, "%s/%s", argpath, dirp->d_name);

		if(stat(path, &statbuf) == -1) exer("Stat u while petlji");

		if(S_ISREG(statbuf.st_mode)) brojanje[0]++;
		else if(S_ISDIR(statbuf.st_mode)) brojanje[1]++;
		else if(S_ISLNK(statbuf.st_mode)) brojanje[2]++;
	}

	printf("Direktorijum ima:\nDATOTEKA | %d\nDIREKTORIJUMA | %d\nLINKOVA | %d\n", brojanje[0], brojanje[1], brojanje[2]);

	return;
}
