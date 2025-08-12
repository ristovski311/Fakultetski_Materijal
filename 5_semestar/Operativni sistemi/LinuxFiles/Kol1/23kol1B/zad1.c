#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

char buff[2048];

sem_t mutex;
sem_t parni;
sem_t neparni;
sem_t glavna;
sem_t niti;

void* parnaNit(void* arg)
{
	FILE* f = fopen("parni.txt","w");

	while(1)
	{
		sem_wait(&parni);
		sem_wait(&niti);
		sem_wait(&mutex);

		if(strcmp(buff,"KRAJ") == 0)
		{
			sem_post(&mutex);
			sem_post(&niti);
			sem_post(&neparni);
			break;
		}

		fprintf(f,"%s",buff);

		sem_post(&mutex);
		sem_post(&glavna);
		sem_post(&neparni);

	}

	fclose(f);

}

void* neparnaNit(void* arg)
{
	FILE* f = fopen("neparni.txt","w");

	while(1)
	{
		sem_wait(&neparni);
		sem_wait(&niti);
		sem_wait(&mutex);

		if(strcmp(buff,"KRAJ") == 0)
		{
			sem_post(&mutex);
			sem_post(&niti);
			sem_post(&parni);
			break;
		}

		fprintf(f,"%s\n",buff);

		sem_post(&mutex);
		sem_post(&glavna);
		sem_post(&parni);

	}

	fclose(f);

}


int main(int argc, char* argv[])
{
	FILE* f;
	pthread_t nitp;
	pthread_t nitn;
	char temp[2048];
	int i;

	if(argc < 2)
	{
		printf("Niste uneli dovoljno argumenata\n"); return 0;
	}

	sem_init(&mutex,0,1);
	sem_init(&parni,0,0);
	sem_init(&neparni,0,1);
	sem_init(&glavna, 0, 1);
	sem_init(&niti,0,0);

	pthread_create(&nitp,NULL,parnaNit,NULL);
	pthread_create(&nitn,NULL,neparnaNit,NULL);

	f = fopen(argv[1],"r");

	while((fgets(temp, sizeof(temp), f)) != NULL)
	{
		sem_wait(&glavna);

		sem_wait(&mutex);

		strcpy(buff, temp);

		sem_post(&mutex);

		sem_post(&niti);
	}

	sem_wait(&glavna);
	sem_wait(&mutex);
	strcpy(buff,"KRAJ");
	sem_post(&mutex);
	sem_post(&niti);

	pthread_join(nitn,NULL);
	pthread_join(nitp,NULL);

	sem_destroy(&glavna);
	sem_destroy(&mutex);
	sem_destroy(&parni);
	sem_destroy(&neparni);
	sem_destroy(&niti);

	fclose(f);

	return 0;
}
