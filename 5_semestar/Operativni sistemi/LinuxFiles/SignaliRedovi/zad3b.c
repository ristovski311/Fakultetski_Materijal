#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int ppid;
int counter = 0;

void obradiUSR1(int sig_num)
{
	int i;
	int num;
	counter++;

	printf("Proces 2 je primio signal SIGUSR1\n");

	if(counter <= 4096)
		signal(SIGUSR1, obradiUSR1);
	else
	{
		printf("Zavrsava se program 2!\n");
		exit(0);
	}

	FILE* f = fopen("prenos.dat", "r");

	if(!f)
	{
		printf("Greska pri otvaranju fajla u procesu 2!");
		exit(-1);
	}

	for(i = 0;i < 1024; i++)
	{
		fscanf(f,"%d", &num);
		printf("Serija %d broj %d\n", counter, num);
	}

	fclose(f);

	printf("Program 2 ce sada poslati sa ppid: %d signal SIGUSR2\n", ppid);
	kill(ppid, SIGUSR2);
	printf("Program2 je poslao signal a sad ceka...\n");
}


int main(int agrc, char* argv[])
{
	ppid = atoi(argv[1]);
	signal(SIGUSR1, obradiUSR1);
	printf("Proces 2 ima pid %d\n", getpid());
	while(1)
		pause();
	return 0;
}
