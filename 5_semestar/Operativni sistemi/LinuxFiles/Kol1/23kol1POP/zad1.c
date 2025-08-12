#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

struct arg
{
	int N;
	char* file;
};


#define BUF 1000

char buff[BUF];

sem_t glavnaS;
sem_t nitS;
sem_t mutex;

int procitano = 0;

int kraj = 0;

void* nitFja(void* arg)
{
	struct arg args = *((struct arg*)arg);
	int N = args.N;
	char* file = args.file;
	FILE* f = fopen(file, "wb");

	while(!kraj)
	{
		sem_wait(&nitS);
		sem_wait(&mutex);

		if(kraj)
			break;

		fwrite(buff, sizeof(char), procitano, f);

		sem_post(&mutex);
		sem_post(&glavnaS);

	}
}

int main(int argc, char* argv[])
{
	int N;
	FILE* f;
	pthread_t nit;
	int i;
	struct arg argumenti;

	if(argc < 4)
	{
		printf("Nedovoljno argumenata!\n");
		return -1;
	}

	N = atoi(argv[2]);

	argumenti.N = N;
	argumenti.file = argv[3];

	f = fopen(argv[1], "rb");

	if(!f)
	{
		printf("Nije uspesno otvorena datoteka!\n");
		return -1;
	}

	sem_init(&glavnaS,0,1);
	sem_init(&nitS, 0, 0);
	sem_init(&mutex,0,1);

	pthread_create(&nit, NULL, nitFja, &argumenti);

	while(1)
	{
		sem_wait(&glavnaS);
		sem_wait(&mutex);

		i = fread(buff, sizeof(char), N, f);
		procitano = i;
		if(i == 0)
		{
			sem_post(&mutex);
			sem_post(&nitS);
			kraj = 1;
			break;
		}

		sem_post(&mutex);
		sem_post(&nitS);
	}

	pthread_join(nit,NULL);
	sem_destroy(&mutex);
	sem_destroy(&nitS);
	sem_destroy(&glavnaS);

	return 0;
}
