#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct parametar
{
	int* niz;
	int duzinaNiza;
};


void* uradiNit(void* arg)
{

	struct parametar Par = *(struct parametar*)arg;
	int max = 0;
	int i;

	for(i = 1; i < Par.duzinaNiza; i++)
	{
		if(Par.niz[i] > Par.niz[max])
			max = i;
	}

	printf("Maksimalni element niza je: %d\n", Par.niz[max]);

}


int main(int argc, char* argv[])
{
	int duzina;
	int i;
	int* arr;
	pthread_t nit;
	struct parametar Param1;

	if(argc < 2)
	{
		printf("Niste uneli duzinu niza kao parametar!\n");
		return -1;
	}

	duzina = atoi(argv[1]);

	arr = (int*)malloc(sizeof(int) * duzina);

	for(i = 0; i < duzina; i++)
	{
		printf("\nUnesite element niza: ");
		scanf("%d", &arr[i]);
	}

	printf("\n");

	Param1.niz = arr;
	Param1.duzinaNiza = duzina;

	pthread_create(&nit, NULL, uradiNit, &Param1);

	pthread_join(nit, NULL);


	free(arr);

	return 0;
}
