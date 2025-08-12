#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

sem_t prvaNit;
sem_t drugaNit;
sem_t mutex;

int prvaGotova = 0;
int drugaGotova = 0;

void* nit1Fja(void *arg)
{
	char* file = (char*)arg;
	int i = 0;
	char line[2000];
	FILE* fi;
	FILE* f = fopen(file,"r");
	if(!f)
	{
		printf("Greska pri otvaranju fajla 1\n");
		pthread_exit(NULL);
	}

	while(fgets(line, sizeof(line), f) != NULL)
	{
		sem_wait(&prvaNit);
		sem_wait(&mutex);

		fi = fopen("zbir.txt", "a");
		if(!fi)
		{
			printf("Greska pri otvaranju fajla za izlaz\n");
			pthread_exit(NULL);
		}

		if(drugaGotova)
		{
			do
			{
				fprintf(fi, "%d. [%s] %s\n", i, file, line);
				i++;
			}while(fgets(line,sizeof(line),f) != NULL);
			break;
		}

		fprintf(fi, "%d. [%s] %s\n", i, file, line);


		fclose(fi);

		sem_post(&mutex);
		sem_post(&drugaNit);
		i++;
	}
	prvaGotova = 1;
	sem_post(&drugaNit);
	fclose(f);
	pthread_exit(NULL);
}

void* nit2Fja(void* arg)
{
	char* file = (char*)arg;
	char line[2000];
	int i = 0;
	FILE* fi;
	FILE* f = fopen(file,"r");
	if(!f)
	{
		printf("Greska pri otvaranju fajla 2\n");
		pthread_exit(NULL);
	}

	while(fgets(line, sizeof(line), f) != NULL)
	{
		sem_wait(&drugaNit);
		sem_wait(&mutex);

		fi = fopen("zbir.txt", "a");

		if(!fi)
		{
			printf("Greska pri otvaranju zbirnog fajla u niti 2\n");
			pthread_exit(NULL);
		}

		if(prvaGotova)
		{
			do
			{
				fprintf(fi,"%d. [%s] %s\n", i, file, line);
				i++;
			}while(fgets(line, sizeof(line), f) != NULL);
			break;
		}

		fprintf(fi,"%d. [%s] %s\n", i, file, line);

		fclose(fi);

		sem_post(&mutex);
		sem_post(&prvaNit);
		i++;
	}
	drugaGotova = 1;
	sem_post(&prvaNit);
	fclose(f);
	pthread_exit(NULL);

}

int main(int argc, char* argv[])
{
	pthread_t nit1, nit2;

	if(argc < 3)
	{
		printf("malo argumenata\n");
		return -1;
	}

	sem_init(&prvaNit,0, 1);
	sem_init(&drugaNit,0,0);
	sem_init(&mutex,0,1);

	pthread_create(&nit1,NULL,nit1Fja, (void*)argv[1]);
	pthread_create(&nit2,NULL,nit2Fja, (void*)argv[2]);

	pthread_join(nit1,NULL);
	pthread_join(nit2,NULL);

	sem_destroy(&mutex);
	sem_destroy(&prvaNit);
	sem_destroy(&drugaNit);

	return 0;
}
