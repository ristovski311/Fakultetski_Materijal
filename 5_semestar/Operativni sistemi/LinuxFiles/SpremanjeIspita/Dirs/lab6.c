#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <memory.h>

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(1);
}

void nadjiNajvecuDatoteku(char* argpath);
void obradiDir(char* argpath, long* size, char** longestPath);

int main(int argc, char* argv[])
{
	struct stat sb;

	if(argc < 2) exer("Niste prosledili dovoljno argumenata!");

	if(stat(argv[1], &sb) == -1) exer("Stat greska u mainu");

	if(S_ISDIR(sb.st_mode))
		nadjiNajvecuDatoteku(argv[1]);
	else
		exer("Niste prosledili direktorijum");

	return 0;
}

void nadjiNajvecuDatoteku(char* argpath)
{
	long maxSize = 0;
	char* maxPath = NULL;

	obradiDir(argpath, &maxSize, &maxPath);

	printf("Najveca datoteka je | %s | %ld\n\n", maxPath, maxSize);
}

void obradiDir(char* argpath, long* size, char** longestPath)
{
	DIR* dp;
	struct dirent* dirp;
	struct stat sb;

	char path[1024];

	if((dp = opendir(argpath)) == NULL) exer("Greska pri otvaranju dir");

	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		sprintf(path, "%s/%s", argpath, dirp->d_name);

		if(stat(path, &sb) == -1) exer("Greska stat u obradiDir");

		if(S_ISREG(sb.st_mode))
		{
			printf("\nProveravam %s\n", path);

			if(sb.st_size > (*size))
			{
				printf("Naso sam novu najvecu | stari size %ld | novi size %ld\n", *size, sb.st_size);

				char* temp;
				*size = sb.st_size;
				if((temp = (char*)realloc((*longestPath), strlen(path) + 1)) == NULL)
					exer("NULL ptr u realloc");
				else
					printf("uspeh\n");
				*longestPath = temp;
				strcpy(*longestPath, path);
			}
		}
	}

	rewinddir(dp);
	closedir(dp);
}

