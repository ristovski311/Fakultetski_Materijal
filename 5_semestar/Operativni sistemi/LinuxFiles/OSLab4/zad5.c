#include "implicit.h"
#include <time.h>

int main(int argc, char* argv[])
{
	int pd1[2];
	int pd2[2];
	int i;
	FILE* f;
	char niz[20];
	char buff[5];
	int suma = 0;
	char ch;

	if(pipe(pd1) == -1)
	{
		printf("Greska pri otvaranju prvog datavoda!\n");
		return -1;
	}

	if(pipe(pd2) == -1)
	{
		printf("Greska pri otvaranju drugog datavoda!\n");
		return -1;
	}

	if(fork() != 0)
	{
		close(pd1[0]);
		close(pd2[0]);

		srand(time(NULL));

		for(i = 0; i < 20; i++)
		{
			niz[i] = (char)(random() % 128);
			suma += (int)niz[i];
		}

		for(i = 0; i < 20; i++)
			printf("Sadrzaj: %c\n", niz[i]);

		printf("\nSuma:%d\n", suma);
		sprintf(buff, "%d", suma);
		write(pd1[1], buff, sizeof(int));
		write(pd2[1], buff, sizeof(int));

		for(i = 0; i < 20; i++)
		{
			write(pd1[1], &niz[i], 1);
			write(pd2[1], &niz[i], 1);
		}

		wait(NULL);

		close(pd1[1]);
		close(pd2[1]);
	}
	else if(fork() != 0)
	{
		close(pd2[0]);
		close(pd2[1]);
		close(pd1[1]);

		read(pd1[0], buff, sizeof(int));
		suma = atoi(buff);
		//printf("Suma iz deteta 1 : %d\n", suma);
		if(suma % 2 == 0)
		{
			f = fopen("KARAKTERI.txt", "w");
			for(i = 0; i < 20; i++)
			{
				read(pd1[0], buff, 1);
				//printf("K.txt: %c\n",buff[0]);
				fprintf(f,"%c\n",buff[0]);
			}
			fclose(f);
		}
		wait(NULL);
		close(pd1[0]);
	}
	else
	{
		close(pd1[1]);
		close(pd1[0]);
		close(pd2[1]);

		read(pd2[0], buff, sizeof(int));
		suma = atoi(buff);
		//printf("Suma iz deteta 2 : %d\n", suma);
		if(suma%2 != 0)
		{
			for(i = 0; i < 20; i++)
			{
				read(pd2[0], buff, 1);
				printf("%c\n", buff[0]);
			}
		}
		close(pd2[0]);
	}

	return 0;
}
