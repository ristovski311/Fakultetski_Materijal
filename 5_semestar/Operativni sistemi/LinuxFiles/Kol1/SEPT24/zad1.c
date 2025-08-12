#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int n;

sem_t mutex;
sem_t nit;
sem_t glavna;

void* nitFja(void* arg)
{
	int i;
	while(1)
	{
		sem_wait(&nit);
		sem_wait(&mutex);

		if(n == 999)
		{
			sem_post(&mutex);
			break;
		}

		for(i = 0; i <= n; i++)
		{
			printf("%d\n", i);
			sleep(1);
		}

		sem_post(&mutex);
		sem_post(&glavna);

	}


}


int main(int argc, char* argv[])
{
	pthread_t Nit;

	sem_init(&mutex,0,1);
	sem_init(&glavna,0,1);
	sem_init(&nit,0,0);

	pthread_create(&Nit, NULL, nitFja, NULL);

	while(1)
	{
		sem_wait(&glavna);
		sem_wait(&mutex);

		printf("\nUnesite broj (999 za kraj): ");
		scanf("%d", &n);

		sem_post(&mutex);
		sem_post(&nit);

		if(n == 999)
			break;
	}

	pthread_join(Nit,NULL);

	sem_destroy(&mutex);
	sem_destroy(&nit);
	sem_destroy(&glavna);


	return 0;
}
