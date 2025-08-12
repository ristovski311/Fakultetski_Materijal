#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

struct param
{
	int* niz;
	int duzina;

};


void* fjaNiti(void* arg)
{
	struct param Par = *(struct param*)arg;
	float res = 0;
	int i;

	for(i = 0; i < Par.duzina; i++)
	{
		res += Par.niz[i];
	}

	if(Par.duzina == 0)
	{
		printf("Uneto je 0 podataka!\n");
		return -1;
	}

	res = res / Par.duzina;

	printf("Aritmeticka sredina niza unetih brojeva je %f\n", res);

}


int main(int argc, char* argv[])
{

	struct param param1;
	int i;
	pthread_t nit;

	param1.niz = (int*)malloc(sizeof(int) * (argc - 1));
	param1.duzina = argc - 1;

	for(i = 0; i < argc - 1; i++)
		param1.niz[i] = atoi(argv[i+1]);

	pthread_create(&nit, NULL, fjaNiti, (void*)&param1);

	pthread_join(nit, NULL);

	free(param1.niz);
	return 0;
}
