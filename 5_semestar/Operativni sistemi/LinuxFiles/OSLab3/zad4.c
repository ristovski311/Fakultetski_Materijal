#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

int niz[5];

pthread_cond_t prvaGotova;
int prvagotova = 0;
pthread_mutex_t mutex;

void* zameniAps(void* arg)
{
	int i;

	pthread_mutex_lock(&mutex);

	for(i = 0; i < 5; i++)
	{
		if(niz[i] < 0)
			niz[i] *= -1;
	}

	prvagotova = 1;
	pthread_cond_signal(&prvaGotova);
	pthread_mutex_unlock(&mutex);
}

void* srednjaVr(void* arg)
{
	int sum =0 ;
	int i;

	pthread_mutex_lock(&mutex);

	while(!prvagotova)
		pthread_cond_wait(&prvaGotova, &mutex);

	for(i = 0; i < 5; i++)
		sum += niz[i];

	niz[0] = (sum/5);

	pthread_mutex_unlock(&mutex);

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
	pthread_cond_init(&prvaGotova, NULL);

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
	pthread_cond_destroy(&prvaGotova);

	return 0;

}

