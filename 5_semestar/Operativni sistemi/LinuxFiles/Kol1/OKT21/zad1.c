#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <ctype.h>

sem_t nit1S;
sem_t nit2S;
sem_t glavnaS;
sem_t mutex;

char recenica[2000];

void* nit1Fja(void* arg)
{
	int i;
	int j;
	char* tok;
	char ch;
	char temp[strlen(recenica)];
	strcpy(temp, "");


	sem_wait(&nit1S);
	sem_wait(&mutex);

	tok = strtok(recenica," ");

	while(tok!=NULL)
	{
		for(i = 0; i < strlen(tok)-1; i++)
		{
			for(j = i; j < strlen(tok); j++)
			{
				if(tok[i] > tok[j])
				{
					ch = tok[i];
					tok[i] = tok[j];
					tok[j] = ch;
				}
			}
		}
		strcat(temp, tok);
		strcat(temp, " ");
		tok = strtok(NULL, " ");
	}
	temp[strlen(temp)-1] = '\0';

	strcpy(recenica, temp);

	sem_post(&mutex);
	sem_post(&nit2S);
}


void* nit2Fja(void* arg)
{
	int i;
	sem_wait(&nit2S);
	sem_wait(&mutex);

	recenica[0] = toupper(recenica[0]);

	if(recenica[strlen(recenica) - 1] != '.')
	{
		recenica[strlen(recenica) + 1] = '\0';
		recenica[strlen(recenica)] = '.';
	}

	printf("Modifikovana recenica iz niti2:\n%s\n",recenica);

	sem_post(&mutex);
	sem_post(&glavnaS);

}

int main()
{
	pthread_t nit1,nit2;
	sem_init(&mutex, 0 ,1);
	sem_init(&nit1S,0,0);
	sem_init(&nit2S,0,0);
	sem_init(&glavnaS,0,1);


	pthread_create(&nit1,NULL,nit1Fja,NULL);
	pthread_create(&nit2,NULL,nit2Fja,NULL);

	sem_wait(&glavnaS);
	sem_wait(&mutex);

	printf("Uneti recenicu: ");
	fgets(recenica,sizeof(recenica), stdin);
	recenica[strlen(recenica) - 1] = '\0';

	sem_post(&mutex);
	sem_post(&nit1S);

	sem_wait(&glavnaS);
	sem_wait(&mutex);

	printf("KRAJ\n\n");

	sem_post(&nit1S);
	sem_post(&mutex);

	sem_destroy(&mutex);
	sem_destroy(&nit1S);
	sem_destroy(&nit2S);
	sem_destroy(&glavnaS);

	return 0;
}
