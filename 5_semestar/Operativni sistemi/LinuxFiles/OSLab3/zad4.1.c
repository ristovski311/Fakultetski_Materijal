#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

int niz[5];

sem_t prvaNit;
sem_t drugaNit;
pthread_mutex_t mutex;

void* zameniAps(void* arg)
{
	int i;

	sem_wait(&prvaNit);
	pthread_mutex_lock(&mutex);

	for(i = 0; i < 5; i++)
	{
		if(niz[i] < 0)
			niz[i] *= -1;
	}

	pthread_mutex_unlock(&mutex);
	sem_post(&drugaNit);
}

void* srednjaVr(void* arg)
{
	int sum =0 ;
	int i;

	sem_wait(&drugaNit);
	pthread_mutex_lock(&mutex);

	for(i = 0; i < 5; i++)
		sum += niz[i];

	niz[0] = (sum/5);

	pthread_mutex_unlock(&mutex);
	sem_post(&prvaNit);

}

int main(int argc, char* argv[])
{
	int i;
	int rand;

	pthread_t nit1;
	pthread_t nit2;

	for(i = 0; i < 5; i++)
	{
		rand = random() % 20 - 10;
		niz[i] = rand;
	}

	printf("\nPre promene:\n");
	for(i=0;i<5;i++)
		printf("%3d",niz[i]);

	pthread_mutex_init(&mutex,NULL);
	sem_init(&prvaNit, 0, 1);
	sem_init(&drugaNit,0,0);

	pthread_create(&nit1, NULL, zameniAps,NULL);
	pthread_create(&nit2, NULL, srednjaVr, NULL);

	pthread_join(nit1,NULL);
	pthread_join(nit2,NULL);


	printf("\nPosle izmene:\n");
	for(i = 0; i < 5; i++)
	{
		printf("%3d", niz[i]);
	}
	printf("\n");

	pthread_mutex_destroy(&mutex);
	sem_destroy(&prvaNit);
	sem_destroy(&drugaNit);

	return 0;

}

