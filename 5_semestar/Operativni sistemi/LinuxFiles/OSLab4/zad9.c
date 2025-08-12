#include "implicit.h"
#include <time.h>

int main(int argc, char* argv[])
{
	int pd1[2];
	int pd2[2];

	int i;
	int suma = 0;
	int niz[20];
	char buff[sizeof(int) + 1];
	int broj;

	if(pipe(pd1) == -1)
	{
		printf("Greska pipe1\n");
		return -1;
	}

	if(pipe(pd2) == -1)
	{
		printf("Greska pipe2\n");
		return -1;
	}

	if(fork() != 0)
	{
		// Roditelj

		if(fork() != 0)
		{
			close(pd1[0]);
			close(pd2[0]);

			// Roditelj
			srand(time(NULL));
			for(i = 0; i < 20; i++)
				niz[i] = random() % 100;

			for(i = 0; i < 20; i++)
				suma+=niz[i];

			sprintf(buff, "%d", suma);
			printf("\nRoditelj: suma = %d\n\n",suma);
			write(pd1[1], buff, sizeof(int));
			write(pd2[1], buff, sizeof(int));
			if(suma%2 == 0)
			{
				close(pd2[2]);
				for(i = 0;i < 20; i++)
				{
					sprintf(buff,"%d",niz[i]);
					write(pd1[1],buff,sizeof(int));
				}
				close(pd1[1]);
			}
			else
			{
				close(pd1[1]);
				for(i = 0; i < 20; i++)
				{
					sprintf(buff,"%d", niz[i]);
					write(pd2[1],buff,sizeof(int));
				}
			}
			wait(NULL);
			wait(NULL);
		}
		else
		{
			//Dete 2

			close(pd1[0]);
			close(pd1[1]);
			close(pd2[1]);

			read(pd2[0],buff,sizeof(int));
			suma = atoi(buff);
			printf("\n\nDete2: suma = %d\n\n", suma);
			if(suma%2 != 0)
			{
				for(i =0; i<20; i++)
				{
					read(pd2[0],buff,sizeof(int));
					broj = atoi(buff);
					printf("Broj: %d\n",broj);
				}

			}
			close(pd2[0]);
		}
	}
	else
	{
		// Dete 1

		close(pd1[1]);
		close(pd2[0]);
		close(pd2[1]);

		FILE* f = fopen("parniBrojevi.txt","w");
		if(!f)
		{
			printf("Greska pri otvaranu fajla!\n");
			return -1;
		}

		read(pd1[0],buff,sizeof(int));
		suma = atoi(buff);
		printf("\n\nDete 1: suma = %d\n\n", suma);
		if(suma%2==0)
		{
			for(i = 0;i<20;i++)
			{
				read(pd1[0],buff,sizeof(int));
				broj=atoi(buff);
				fprintf(f,"%d\n",broj);
			}
		}
		close(pd1[0]);
	}




	return 0;
}
