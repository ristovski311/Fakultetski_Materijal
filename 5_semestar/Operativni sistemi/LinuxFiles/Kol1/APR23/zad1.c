#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>


int niz[10];

pthread_cond_t prvaGotova, drugaGotova;
int prvagotova = 0;
int drugagotova = 0;

sem_t prva;
sem_t druga;
pthread_mutex_t mutex;

void* nit1Fja(void* arg)
{
	int i;
	int j;
	srand(time(NULL));

	for(i = 0; i < 5; i++)
	{
		sem_wait(&prva);

		for(j = 0; j < 10; j+=2)
		{
			pthread_mutex_lock(&mutex);
			niz[j] = random() % 300;
			pthread_mutex_unlock(&mutex);
		}

		prvagotova = 1;
		pthread_cond_signal(&prvaGotova);

	}


}

void* nit2Fja(void* arg)
{
	int i;
	int j;
	srand(time(NULL));

	for(i = 0; i< 5; i++)
	{
		sem_wait(&druga);

		for(j = 1; j < 10; j+=2)
		{
			pthread_mutex_lock(&mutex);
			niz[j] = random()%200+300;
			pthread_mutex_unlock(&mutex);
		}

		drugagotova = 1;
		pthread_cond_signal(&drugaGotova);


	}

}

int main(int argc, char* argv[])
{
	int i;
	int sum;
	int j;

	pthread_t nit1, nit2;

	sem_init(&prva,0,1);
	sem_init(&druga,0,1);
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&prvaGotova,NULL);
	pthread_cond_init(&drugaGotova,NULL);

	pthread_create(&nit1,NULL,nit1Fja,NULL);
	pthread_create(&nit2,NULL,nit2Fja,NULL);


	for(i = 0; i < 5; i++)
	{
		sum = 0;

		pthread_mutex_lock(&mutex);

		while(!prvagotova)
			pthread_cond_wait(&prvaGotova,&mutex);

		while(!drugagotova)
			pthread_cond_wait(&drugaGotova,&mutex);

		for(j = 0; j < 10; j++)
			sum+=niz[j];

		printf("Niz: ");
		for(j = 0; j < 10; j++)
			printf("%4d", niz[j]);

		if(sum >= 2000)
			printf("\n%d. Zbir je veci od 2000!\n", i);
		else
			printf("\n%d. Zbir je manji od 2000!\n",i);


		prvagotova=0;
		drugagotova=0;

		sem_post(&prva);
		sem_post(&druga);

		pthread_mutex_unlock(&mutex);

	}

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&prvaGotova);
	pthread_cond_destroy(&drugaGotova);
	sem_destroy(&prva);
	sem_destroy(&druga);

	return 0;
}
