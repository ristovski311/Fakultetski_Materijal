#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

struct parametri
{
	int** matrix;
	int index;
	int rows;
	int cols;
};

void* nadjiMax(void* arg)
{
	struct parametri par = *(struct parametri*)arg;
	int i;
	int max = 0;

	for(i = 1; i < par.rows; i++)
		if(par.matrix[i][par.index] > par.matrix[max][par.index])
			max = i;

	printf("\nNasla sam max element %d kolone i on je %d\n", par.index, par.matrix[max][par.index]);

}

int main(int argc, char* argv[])
{
	int M, N;
	int** matrica;
	int i,j;
	pthread_t* niti;
	struct parametri* par;

	if(argc < 3)
	{
		printf("Unesite dimenzije matrice!\n");
		return -1;
	}

	M = atoi(argv[1]);
	N = atoi(argv[2]);

	matrica = (int**)malloc(sizeof(int*) * M);
	for(i = 0; i < M; i++)
		matrica[i] = (int*)malloc(sizeof(int) * N);

	par = (struct parametri*)malloc(sizeof(struct parametri) * N);

	for(i = 0; i < M; i++)
		for(j = 0; j < N; j++)
		{
			printf("Unesite element matrice:\n");
			scanf("%d", &matrica[i][j]);
		}

	printf("\nMatrica: \n");

	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
			printf("%d  ", matrica[i][j]);
		printf("\n");
	}


	niti = (pthread_t*)malloc(sizeof(pthread_t) * N);


	for(i = 0; i < N; i++)
	{
		par[i].matrix = matrica;
		par[i].index = i;
		par[i].rows = M;
		par[i].cols = N;
		pthread_create(&niti[i], NULL, nadjiMax, (void*)&par[i]);
	}

	for(i = 0; i < N; i++)
		pthread_join(niti[i], NULL);


	for(i = 0; i < M; i++)
		free(matrica[i]);
	free(matrica);
	free(niti);

	return 0;
}
