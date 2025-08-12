#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>

char buff[2048];

sem_t glavna;
sem_t nit1;
sem_t nit2;

void* nit1Fja(void* arg)
{
	int len;

	while(1)
	{
		sem_wait(&nit1);

		if(strcmp(buff, "KRAJ") == 0)
		{
			sem_post(&nit2);
			break;
		}


		len = strlen(buff);
		if(buff[len - 1] != '.')
		{
			buff[len + 1] = '\0';
			buff[len] = '.';
		}

		buff[0] = toupper(buff[0]);

		sem_post(&nit2);
	}

	pthread_exit(0);
}

void* nit2Fja(void* arg)
{
	while(1)
	{
		sem_wait(&nit2);

		if(strcmp(buff, "KRAJ") == 0)
		{
			sem_post(&glavna);
			break;
		}

		int i;

		for(i = 0; i < strlen(buff); i++)
		{
			if(buff[i] == ' ')
				buff[i] = '_';
		}

		printf("-> %s\n",buff);

		sem_post(&glavna);
	}
	pthread_exit(0);
}

int main()
{
	char input[2048];
	pthread_t nit1n;
	pthread_t nit2n;

	//pthread_create(&nit1n, NULL, nit1Fja, NULL);
	//pthread_create(&nit2n, NULL, nit2Fja, NULL);

	sem_init(&glavna, 0, 1);
	sem_init(&nit1, 0, 0);
	sem_init(&nit2, 0, 0);

	pthread_create(&nit1n, NULL, nit1Fja,NULL);
	pthread_create(&nit2n,NULL, nit2Fja, NULL);


	while(1)
	{
		sem_wait(&glavna);

		printf("Unesite recenicu ili 'KRAJ' za kraj: ");
		fgets(buff, sizeof(buff)-1,stdin);

		*(strchr(buff, '\n')) = '\0';

		sem_post(&nit1);

		if(strcmp(buff, "KRAJ") == 0)
		{
			sem_post(&nit1);
			break;
		}


	}

	pthread_join(nit1n,NULL);
	pthread_join(nit2n, NULL);

	sem_destroy(&glavna);
	sem_destroy(&nit1);
	sem_destroy(&nit2);
	return 0;
}

