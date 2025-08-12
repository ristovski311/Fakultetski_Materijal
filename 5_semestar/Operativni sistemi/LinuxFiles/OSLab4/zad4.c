#include "implicit.h"

#define BUFSIZE 100

int main(int argc, char* argv[])
{
	FILE* fi;
	FILE* fo;
	int pd[2];
	int i;
	char buff[BUFSIZE];

	if(argc < 3)
	{
		printf("Nedovoljno argumenata!\n");
		return -1;
	}

	fi = fopen(argv[1], "r");
	fo = fopen(argv[2], "w");

	if(fi == 0 || fo == 0)
	{
		printf("Greska pri otvaranju datoteka!\n");
		return -1;
	}

	if(strcmp(argv[1], argv[2]) == 0)
	{
		printf("Ne sme se koristiti izvorisna za odredisnu datoteku!\n");
		return -1;
	}

	if(pipe(pd) < 0)
	{
		printf("Greska pri otvaranju datavoda!\n");
		return -1;
	}

	if(fork() != 0)
	{
		close(pd[0]);
		while(fgets(buff, BUFSIZE, fi) != NULL)
		{
			write(pd[1], buff, strlen(buff));
		}
		close(pd[1]);
		wait(NULL);
		fclose(fi);
	}
	else
	{
		close(pd[1]);

		while((i = read(pd[0],buff,BUFSIZE - 1))>0)
		{
			buff[i] = '\0';
			fprintf(fo, "%s", buff);
		}

		fclose(fo);
		close(pd[0]);
	}


	return 0;
}
