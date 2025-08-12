#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>


int niz[400];
int duzina;
int kraj = 0;
int sum;

sem_t glavnaS;
sem_t nitS;

void* nitFja(void* arg)
{
	int i;
	while(!kraj)
	{
		//printf("nit ceka\n");
		sem_wait(&nitS);
		if(kraj)
			break;
		sum = 0;

		for(i = 0;i < duzina; i++)
		{
			sum += niz[i];
		}
		//printf("nit gotova\n");
		sem_post(&glavnaS);
	}

}


int main()
{
	char t;
	FILE* f;
	pthread_t nit;
	int i;

	sem_init(&glavnaS,0,1);
	sem_init(&nitS,0,0);

	if((f= fopen("ulaz.txt","r")) == 0)
	{
		printf("Greska pri otvaranju datoteke\n");
		return -1;
	}

	pthread_create(&nit, NULL, nitFja, NULL);

	while(1)
	{
		//printf("glavna ceka\n");
		sem_wait(&glavnaS);
		i = 0;
		do
		{
			if(fscanf(f,"%d%c",&niz[i++],&t)!=2)
				break;
		}
		while(t != '\n' && !feof(f));
		duzina = i;
		if(feof(f))
		{
			kraj = 1;
			sem_post(&nitS);
			break;
		}
		//printf("glavna gotova\n");
		sem_post(&nitS);
		//printf("glavna ceka za sumu\n");
		sem_wait(&glavnaS);
		printf("Suma je: %d\n", sum);
		printf("Duzina niza je: %d\n",duzina);
		//printf("glavna gotova za sumu");
		sem_post(&glavnaS);
	}

	pthread_join(nit,NULL);
	fclose(f);
	sem_destroy(&glavnaS);
	sem_destroy(&nitS);

	return 0;
}
