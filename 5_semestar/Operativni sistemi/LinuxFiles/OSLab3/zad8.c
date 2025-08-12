#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t finished;

int firstFinished = 0;

int* niz;

void* sort1(void* arg)
{
	int N = *(int*)arg;
	int i, j, m;

	pthread_mutex_lock(&mutex);

	for(i = 0; i < N/2 - 1; i++)
	{
		for(j = i+1; j< N/2; j++)
		{
			if(niz[i] > niz[j])
			{
				m = niz[i];
				niz[i] = niz[j];
				niz[j] = m;
			}
		}
	}

	firstFinished = 1;

	pthread_cond_signal(&finished);

	pthread_mutex_unlock(&mutex);
}

void* sort2(void* arg)
{
	int i,j,m;
	int N = *(int*)arg;

	pthread_mutex_lock(&mutex);

	while(!firstFinished)
		pthread_cond_wait(&finished, &mutex);

	for(i = N/2; i < N-1; i++)
	{
		for(j = i+1; j < N; j++)
		{
			if(niz[i] < niz[j])
			{
				m = niz[i];
				niz[i] = niz[j];
				niz[j] = m;
			}
		}
	}

	pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[])
{
	int i, N, rand;
	pthread_t nit1;
	pthread_t nit2;

	printf("Unesite broj elemenata niza:\n");
	scanf("%d",&N);

	niz = (int*)malloc(sizeof(int)*N);

	for(i = 0; i < N; i++)
	{
		rand = random() % 11;
		niz[i] = rand;
	}

	printf("\nNesortirani niz:\n");
	for(i=0;i<N;i++)
		printf("%3d", niz[i]);

	printf("\n\n");

	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&finished, NULL);

	pthread_create(&nit1, NULL, sort1, &N);
	pthread_create(&nit2, NULL, sort2, &N);

	pthread_join(nit1,NULL);
	pthread_join(nit2,NULL);

	printf("\nSortirani niz:\n");
	for(i=0;i<N;i++)
		printf("%3d", niz[i]);

	printf("\n=====\n");

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&finished);

	free(niz);

	return 0;
}
