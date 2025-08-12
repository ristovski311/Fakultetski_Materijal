#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

int N;
sem_t mutex;
sem_t nitS;
sem_t glavnaS;

void* nitFja(void* arg)
{
	int i;
	FILE* f;
	f = fopen("data.txt","r");
	if(f == 0)
		printf("greska file\n");
	char buff[255];

	while(1)
	{
		sem_wait(&nitS);
		sem_wait(&mutex);

		if(N == 99)
			break;

		for(i = 0; i < N && !feof(f); i++)
		{
			fgets(buff, sizeof(buff) ,f);
			printf("%s\n", buff);
			sleep(1);
		}

		sem_post(&mutex);
		sem_post(&glavnaS);
	}

	exit(0);
}

int main()
{
	int input;
	int i;

	pthread_t nit;

	sem_init(&mutex, 0, 1);
	sem_init(&nitS, 0, 0);
	sem_init(&glavnaS, 0, 1);

	pthread_create(&nit, NULL, nitFja, NULL);

	do
	{
		sem_wait(&glavnaS);
		sem_wait(&mutex);
		printf("Uneti ceo broj:\n");
		scanf("%d", &input);
		N = input;
		sem_post(&mutex);
		sem_post(&nitS);

	}while(input != 99);

	pthread_join(nit,NULL);

	sem_destroy(&mutex);
	sem_destroy(&nitS);
	sem_destroy(&glavnaS);

	return 0;
}
