#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char* argumenti[20];
	int N,i;

	printf("Unesi duzinu niza:");
	scanf("%d", &N);

	for(i = 0; i < N + 2; i++)
		argumenti[i] = (char*)malloc(sizeof(char) * 20);

	strcpy(argumenti[0], "zad6");

	for(i = 1; i <= N; i++)
	{
		printf("\nUnesi broj: ");
		scanf("%s", argumenti[i]);
	}

	argumenti[N + 1] = NULL;


	/*for(i = 0; i < N+1; i++)
		printf("%d %s\n", i, argumenti[i]);*/

	if(fork() == 0)
	{
		if(execv("./zad6", argumenti) == -1){
		perror("Greska!");
		exit(-1);}
	}
	else
		wait(NULL);

	return 0;
}
