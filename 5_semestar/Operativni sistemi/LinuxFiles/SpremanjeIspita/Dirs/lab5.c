#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/file.h>
#include <sys/types.h>

#define MAXSIZE (10*1024) //10kB

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(1);
}

void obrisiDatoteke(const char* argpath);
void obradiDir(const char* argpath, int depth);

int main(int argc, char* argv[])
{
	struct stat sb;

	if(argc < 2) exer("Niste prosledili");

	if(stat(argv[1], &sb) == -1) exer("Stat greska u main");

	if(S_ISDIR(sb.st_mode))
		obrisiDatoteke(argv[1]);
	else
		exer("Niste prosledili DIR");

	return 0;
}


void obrisiDatoteke(const char* argpath)
{
	obradiDir(argpath, 0);
}



void obradiDir(const char* argpath, int depth)
{
	DIR* dp;
	struct dirent* dirp;
	struct stat sb;

	char path[1024];

	if((dp = opendir(argpath)) == NULL) exer("Greska pri otvaranju dir-a u obradiDir");

	printf("Trenutno sam u %s\nDepth je %d\n", argpath, depth);

	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		sprintf(path, "%s/%s", argpath, dirp->d_name);

		if(stat(path, &sb) == -1) exer("Stat greska u obradiDir");

		if(S_ISDIR(sb.st_mode) && depth < 3)
		{
			obradiDir(path, depth + 1);
		}
		else if(S_ISREG(sb.st_mode) && sb.st_size > MAXSIZE)
		{
			if(fork() == 0)
			{
				printf("Brisem datoteku %s\n", path);
				execl("/bin/rm", "rm", path, NULL);
				exer("Greska pri pozivanju rm!");
			}
		}
	}

	rewinddir(dp);
	closedir(dp);
}
