#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>

int N;
pthread_mutex_t mutex;
pthread_cond_t drugaNaRedu;
int druganaredu = 0;
pthread_cond_t prvaNaRedu;

void* nit1Fja(void* arg)
{
	int i;

	pthread_mutex_lock(&mutex);

	for(i = 0; i < N; i++)
	{
		while(druganaredu)
			pthread_cond_wait(&prvaNaRedu, &mutex);

		if(i % 7 == 0)
		{
			druganaredu = 1;
			pthread_cond_signal(&drugaNaRedu);
		}
		else
			printf("Prva : %d\n", i);

	}



	pthread_mutex_unlock(&mutex);

}


void* nit2Fja(void* arg)
{
	int i;

	pthread_mutex_lock(&mutex);

	for(i = 0; i < N; i++)
	{

		if(i % 7 == 0)
		{
			while(!druganaredu)
				pthread_cond_wait(&drugaNaRedu,&mutex);
			printf("Druga: %d\n", i);
			druganaredu = 0;
			pthread_cond_signal(&prvaNaRedu);
		}


	}


	pthread_mutex_unlock(&mutex);


}


int main(int argc, char* argv[])
{
	pthread_t nit1,nit2;

	if(argc < 2)
	{
		printf("Nedovoljno argumenata!\n");
		return -1;
	}

	N = atoi(argv[1]);

	pthread_cond_init(&drugaNaRedu, NULL);
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&prvaNaRedu, NULL);

	pthread_create(&nit1,NULL,nit1Fja,NULL);
	pthread_create(&nit2,NULL,nit2Fja,NULL);

	pthread_join(nit1,NULL);
	pthread_join(nit2,NULL);

	pthread_cond_destroy(&prvaNaRedu);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&drugaNaRedu);
	return 0;
}
