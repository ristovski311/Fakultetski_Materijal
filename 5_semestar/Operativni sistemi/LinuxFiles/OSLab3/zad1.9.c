#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define TRUE 1
#define FALSE 0

struct dim{
	int M;
	int N;
};

int** matrica;

pthread_mutex_t mutexMatrice;
sem_t vrstaNaRedu;
sem_t kolonaNaRedu;

void* sortVrste(void* arg)
{
	int i,j,k;
	int m;
	struct dim d = *(struct dim*)arg;
	for(i=0;i<d.M;i++)
	{
		sem_wait(&vrstaNaRedu);
		pthread_mutex_lock(&mutexMatrice);

		for(j = 0;j < d.N - 1;j++)
		{
			for(k = j+1; k < d.N; k++)
			{
				if(matrica[i][j] > matrica[i][k])
				{
					m = matrica[i][j];
					matrica[i][j] = matrica[i][k];
					matrica[i][k] = m;
				}
			}
		}

		printf("\n");
		for(k=0;k<d.M;k++)
		{
		for(j=0;j<d.N;j++)
			printf("%2d", matrica[k][j]);

		printf("\n");
		}

		pthread_mutex_unlock(&mutexMatrice);
		sem_post(&kolonaNaRedu);
	}
}

void* sortKolone(void* arg)
{
	int i,j,k;
	int m;
	struct dim d = *(struct dim*)arg;
	for(i=0;i<d.N;i++)
	{
		sem_wait(&kolonaNaRedu);
		pthread_mutex_lock(&mutexMatrice);

		for(j = 0;j < d.M - 1;j++)
		{
			for(k = j+1; k < d.M; k++)
			{
				if(matrica[j][i] > matrica[k][i])
				{
					m = matrica[j][i];
					matrica[j][i] = matrica[k][i];
					matrica[k][i] = m;
				}
			}
		}

		printf("\n");
	for(k=0;k<d.M;k++)
	{
		for(j=0;j<d.N;j++)
			printf("%2d", matrica[k][j]);

		printf("\n");
	}

		pthread_mutex_unlock(&mutexMatrice);
		sem_post(&vrstaNaRedu);
	}
}

int main()
{
	int i,j;
	int N,M;
	pthread_t nitVrsta;
	pthread_t nitKolona;

	struct dim dimenzije;

	pthread_mutex_init(&mutexMatrice,NULL);
	sem_init(&vrstaNaRedu,0,0);
	sem_init(&kolonaNaRedu,0,1);

	printf("Unesite dimenzije matrice: ");
	scanf("%d %d", &M, &N);

	dimenzije.M = M;
	dimenzije.N = N;

	matrica = (int**)malloc(sizeof(int*) * M);
	for(i=0;i<M;i++)
		matrica[i] = (int*)malloc(sizeof(int)*N);

	printf("\nUnesite elemente matrice:\n");

	for(i=0;i<M;i++)
		for(j=0;j<N;j++)
			scanf("%d",&matrica[i][j]);

	printf("\n");
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
			printf("%2d", matrica[i][j]);

		printf("\n");
	}

	pthread_create(&nitKolona,NULL,sortKolone,(void*)&dimenzije);
	pthread_create(&nitVrsta,NULL,sortVrste,(void*)&dimenzije);

	pthread_join(nitKolona,NULL);
	pthread_join(nitVrsta,NULL);

	printf("\n");
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
			printf("%2d", matrica[i][j]);

		printf("\n");
	}

	sem_destroy(&kolonaNaRedu);
	sem_destroy(&vrstaNaRedu);
	pthread_mutex_destroy(&mutexMatrice);

	for(i=0;i<M;i++)
		free(matrica[i]);
	free(matrica);

	return 0;



}

