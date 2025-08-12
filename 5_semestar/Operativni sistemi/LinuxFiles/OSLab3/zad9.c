#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct dim{
	int M;
	int N;
};

int** matrica;

pthread_mutex_t mutexMatrice;
pthread_cond_t redNaVrstu;

int rednavrstu = FALSE;

void* sortVrste(void* arg)
{
	int i,j,k;
	int m;
	struct dim d = *(struct dim*)arg;
	for(i=0;i<d.M;i++)
	{
		pthread_mutex_lock(&mutexMatrice);

		while(!rednavrstu)
			pthread_cond_wait(&redNaVrstu, &mutexMatrice);

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

		rednavrstu = FALSE;

		printf("\n");
		for(k=0;k<d.M;k++)
		{
		for(j=0;j<d.N;j++)
			printf("%2d", matrica[k][j]);

		printf("\n");
		}

		pthread_cond_signal(&redNaVrstu);

		pthread_mutex_unlock(&mutexMatrice);
	}
}

void* sortKolone(void* arg)
{
	int i,j,k;
	int m;
	struct dim d = *(struct dim*)arg;
	for(i=0;i<d.N;i++)
	{
		pthread_mutex_lock(&mutexMatrice);

		while(rednavrstu)
			pthread_cond_wait(&redNaVrstu, &mutexMatrice);

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

		rednavrstu = TRUE;

		printf("\n");
	for(k=0;k<d.M;k++)
	{
		for(j=0;j<d.N;j++)
			printf("%2d", matrica[k][j]);

		printf("\n");
	}

		pthread_cond_signal(&redNaVrstu);

		pthread_mutex_unlock(&mutexMatrice);
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
	pthread_cond_init(&redNaVrstu, NULL);

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

	pthread_cond_destroy(&redNaVrstu);
	pthread_mutex_destroy(&mutexMatrice);

	for(i=0;i<M;i++)
		free(matrica[i]);
	free(matrica);

	return 0;



}

