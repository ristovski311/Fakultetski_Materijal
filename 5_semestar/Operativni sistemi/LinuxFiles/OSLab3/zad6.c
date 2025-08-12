#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, malo, veliko;

void* stampajMala(void* arg)
{
	char letter = 'a';

	while(letter <= 'z')
	{
		sem_wait(&malo);
		sem_wait(&mutex);

		printf("%c", letter);

		sem_post(&mutex);
		sem_post(&veliko);

		letter += 1;
		sleep(1);
	}
}

void* stampajVelika(void* arg)
{
	char letter = 'A';

	while(letter <= 'Z')
	{
		sem_wait(&veliko);
		sem_wait(&mutex);

		printf("%c",letter);

		sem_post(&mutex);
		sem_post(&malo);

		letter += 1;
		sleep(1);
	}
}

int main()
{
	pthread_t nitMala;
	pthread_t nitVelika;

	sem_init(&mutex,0,1);
	sem_init(&malo,0,1);
	sem_init(&veliko,0,0);

	pthread_create(&nitVelika, NULL, stampajVelika, NULL);
	pthread_create(&nitMala, NULL, stampajMala, NULL);

	pthread_join(nitMala,NULL);
	pthread_join(nitVelika,NULL);

	sem_destroy(&mutex);
	sem_destroy(&malo);
	sem_destroy(&veliko);

	return 0;
}


