#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t mutex,parni,neparni;


void* parniUpis(void* arg)
{
	FILE* f = (FILE*)arg;
	int i;

	for(i=2;i<=20;i+=2)
	{
		sem_wait(&parni);
		sem_wait(&mutex);

		fprintf(f,"%d\n",i);

		sem_post(&mutex);
		sem_post(&neparni);
	}
}


void* neparniUpis(void* arg)
{
	FILE* f = (FILE*)arg;
	int i;

	for(i = 1; i < 20; i+=2)
	{
		sem_wait(&neparni);
		sem_wait(&mutex);

		fprintf(f,"%d\n",i);

		sem_post(&mutex);
		sem_post(&parni);
	}

}

int main(int argc, char* argv[])
{
	pthread_t nitP;
	pthread_t nitN;

	FILE* f;

	f = fopen("brojevi.txt", "w");

	if(f == 0)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	sem_init(&mutex,0,1);
	sem_init(&parni,0,0);
	sem_init(&neparni,0,1);

	pthread_create(&nitP,NULL,parniUpis, (void*)f);
	pthread_create(&nitN,NULL,neparniUpis, (void*)f);

	pthread_join(nitP,NULL);
	pthread_join(nitN,NULL);

	printf("\nZavrseno!\n");

	sem_destroy(&mutex);
	sem_destroy(&parni);
	sem_destroy(&neparni);

	fclose(f);

	return 0;
}
