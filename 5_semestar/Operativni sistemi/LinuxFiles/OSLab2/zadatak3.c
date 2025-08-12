#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* nit2Fja(void* arg);

int main()
{
	char* unos;
	pthread_t nit2;

	printf("Uneti broj ili KRAJ: ");
	scanf("%s", unos);

	while(strcmp(unos, "KRAJ") != 0)
	{
		pthread_create(&nit2, NULL, nit2Fja, (void*)unos);
		pthread_join(nit2, NULL);
		printf("Uneti sledeci broj ili KRAJ: ");
		scanf("%s", unos);
	}

	return 0;
}

void* nit2Fja(void* arg)
{
	int N = atoi((char*)arg);
	while(N >= 0)
	{
		printf("N = %d\n", N);
		N--;
		sleep(3);
	}
}
