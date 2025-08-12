#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[])
{
	int niz[15];
	int pd1[2];
	int pd2[2];
	int i;
	char buff[128];


	if(pipe(pd1) == -1)
	{
		printf("Neuspesno otvaranje datavoda 1\n");
		return -1;
	}
	if(pipe(pd2) == -1)
	{
		printf("Neuspesno otvaranje datavoda 2\n");
		return -1;
	}

	if(fork() != 0)
	{
		close(pd1[0]);
		close(pd2[0]);
		printf("\nProces roditelj pocinje sa upisom brojeva!\n");
		srand(time(NULL));
		for(i = 0; i < 15; i++)
		{
			niz[i] = rand() % 100;
		}

		for(i = 0; i < 15; i++)
		{
			sprintf(buff, "%d", niz[i]);
			write(pd1[1], buff, 128);
			write(pd2[1], buff, 128);
		}
		wait(NULL);
		close(pd1[1]);
		close(pd2[1]);
		printf("\nProces roditelj je zavrsio i zatvorio svoje datavode!\n");
	}
	else if(fork() != 0)
	{
		close(pd1[1]);
		close(pd2[0]);
		close(pd2[1]);
		FILE* f;
		f = fopen("PARNI.txt", "w");
		if(f == 0)
		{
			printf("neuspesno otvoren fajl parni!\n");
			return -1;
		}
		read(pd1[0], buff, 128);
		int procitan = atoi(buff);
		if(procitan%2==0)
		{
			printf("\nDrugi proces pocinje da cita!\n");
			fprintf(f,"%d\n", procitan);
			for(i =0; i < 14; i++)
			{
				read(pd1[0], buff, 128);
				procitan = atoi(buff);
				fprintf(f, "%d\n", procitan);
			}
			printf("\nDrugi proces je zavrsio!\n");
		}
		wait(NULL);
		close(pd1[0]);
		fclose(f);
	}
	else
	{
		close(pd1[0]);
		close(pd1[1]);
		close(pd2[1]);
		read(pd2[0], buff, 128);
		int procitan = atoi(buff);
		if(procitan%2 != 0)
		{
			printf("\nProces 3 pocinje da radi!\n");
			printf("\n%d\n", procitan);
			for(i = 0; i < 14; i++)
			{
				read(pd2[0], buff, 128);
				procitan = atoi(buff);
				printf("\n%d\n", procitan);
			}
			printf("Proces 3 je zavrsio!\n");
		}
		close(pd2[0]);
	}



	return 0;
}
