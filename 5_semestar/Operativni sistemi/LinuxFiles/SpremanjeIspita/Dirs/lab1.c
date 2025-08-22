#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

void exer(const char* msg)
{
	printf("\nGreska\n%s\n", msg);
	exit(1);
}

void processDir(char* n, const char* s);

int main(int argc, char* argv[])
{
	struct stat statbuf;

	if(argc < 3) exer("Nedovoljno argumenata!");

	if(stat(argv[1], &statbuf) == -1) exer("Ne moze se otvoriti dir");

	if(S_ISDIR(statbuf.st_mode))
		processDir(argv[1], argv[2]);
	else
		exer("Nije prosledjen direktorijum!");

	return 0;

}

void processDir(char* name, const char* str)
{
	DIR* dp;
	struct dirent* dirp;
	struct stat statbuf;

	char path[1024];

	printf("Dirname: %s | String: %s\n", name, str);

	if((dp = opendir(name)) == NULL) exer("Greska, lose ime direktorijuma!");

	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		sprintf(path, "%s/%s", name, dirp->d_name);

		if(stat(path, &statbuf) == -1) exer("Stat u direktorijumu nekog fajla je posao po zlu");

		if(S_ISREG(statbuf.st_mode))
			if(strstr(dirp->d_name, str) != NULL)
				printf("Datoteka | %s\n", path);
	}

	rewinddir(dp);
	closedir(dp);

	return;
}
