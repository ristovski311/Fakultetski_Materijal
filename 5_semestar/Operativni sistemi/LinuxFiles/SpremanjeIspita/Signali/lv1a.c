#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define MAXBUF 1024

int timesRead = 0;
int ppid;

void obradiFajl();

void obradiSIGUSR1(int sid)
{
	//printf("Reader je primio sigusr1!\n");
	obradiFajl();
	if(timesRead < 1024)
	{
		kill(ppid, SIGUSR2);
		//printf("Reader je poslao sigusr2!\n");
	}
	signal(SIGUSR1, obradiSIGUSR1);
}

void obradiFajl()
{
	int brojevi[MAXBUF];
	int fd = open("podaci.dat", O_RDONLY);
	if(fd == -1)
	{
		printf("\nGreska prilikom otvaranja fajla za citanje iz procesa 2!\n");
		exit(1);
	}

	if(read(fd, brojevi, sizeof(brojevi)) < 0)
	{
		printf("\nGreska prilikom citatnja iz fajla!\n");
		exit(1);
	}

	timesRead++;

	printf("\nIteracija readera: %d\n", timesRead);

	for(int i = 0; i < MAXBUF; i++)
	{
		//printf("\n[It %d] B.%d > %d\n", timesRead, i, brojevi[i]);
	}

	close(fd);
}

int main(int argc, char* argv[])
{
	printf("Reader se otvorio\n");
	fflush(stdout);

	if(argc < 2)
	{
		printf("Greska, nedovoljno argumenata za proces 2!\n");
		return -1;
	}

	char arg[10];
	strcpy(arg, argv[1]);

	ppid = atoi(arg);

	printf("Roditelj ima pid: %d a ja reader imam pid: %d\n", ppid, getpid());

	signal(SIGUSR1, obradiSIGUSR1);

	//Obavesti parenta da sam spreman!

	kill(ppid, SIGUSR2);

	while(timesRead < 1024)
	{
		pause();
	}

	printf("\nPROCES 2 READER JE ZAVRSIO!\n");

	return 0;
}
