#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define velicinaNiza 11

int niz[] = {2,7,4,1,8,4,7,2,9,3,10};

int redNaDrugu = 0;

pthread_mutex_t mutexNiza;
pthread_cond_t dalje;

void* dodaj(void* arg)
{
	int rand;
	int index;

	while(1)
	{
		pthread_mutex_lock(&mutexNiza);

		while(redNaDrugu)
			pthread_cond_wait(&dalje, &mutexNiza);

		index = random() % velicinaNiza;
		rand = random() % 20 - 10;

		niz[index] += rand;

		redNaDrugu = 1;
		pthread_cond_signal(&dalje);

		pthread_mutex_unlock(&mutexNiza);

		sleep(1);
	}
}

void* printuj(void* arg)
{
	int sum;
	int i;

	while(1)
	{
		sum = 0;

		pthread_mutex_lock(&mutexNiza);

		while(!redNaDrugu)
			pthread_cond_wait(&dalje, &mutexNiza);

		for(i = 0; i < velicinaNiza; i++)
			sum += niz[i];

		if(sum % 2 == 0)
		{
			printf("\nKako je suma niza paran broj: %d, niz je:\n", sum);
			for(i = 0; i < velicinaNiza; i++)
				printf("%3d", niz[i]);
		}

		redNaDrugu = 0;
		pthread_cond_signal(&dalje);
		pthread_mutex_unlock(&mutexNiza);
	}
}

int main(int argc, char* argv[])
{
	pthread_t nit1;
	pthread_t nit2;

	pthread_mutex_init(&mutexNiza,NULL);
	pthread_cond_init(&dalje, NULL);

	pthread_create(&nit1, NULL, dodaj, NULL);
	pthread_create(&nit2, NULL, printuj, NULL);

	pthread_join(nit1,NULL);
	pthread_join(nit2,NULL);

	pthread_mutex_destroy(&mutexNiza);
	pthread_cond_destroy(&dalje);

	return 0;
}
