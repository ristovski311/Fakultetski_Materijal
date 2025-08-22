#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAXBUF 1024

void generisi();

int timesGenerated = 0;
int pid;

void obradiSIGUSR2(int sid)
{
	//printf("Roditelj obradjuje sigusr2\n!");
	generisi();
	timesGenerated++;
	printf("\nProces 1 GENERATOR je generisao po %d. put!\n", timesGenerated);
	kill(pid, SIGUSR1);
	//printf("roditelj je poslao sigusr1!\n");
	signal(SIGUSR2, obradiSIGUSR2);
}

void generisi()
{
	int brojevi[MAXBUF];
	//int randomNum;
	srand(time(NULL));

	int fd = open("podaci.dat", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if(fd == -1)
	{
		printf("\nGreska prilikom otvaranja fajla!\n");
		exit(1);
	}

	for(int i = 0; i < MAXBUF; i++)
	{
		brojevi[i] = rand();
	}

	if(write(fd, brojevi, sizeof(brojevi)) < 0)
	{
		printf("\nDoslo je do greske pri upisu u fajl!\n");
		exit(1);
	}

	close(fd);
}

int main(int argc, char* argv[])
{
	signal(SIGUSR2, obradiSIGUSR2);

	pid = fork();

	if(pid == 0)
	{
		char ppid[10];
		sprintf(ppid, "%d", getppid());
		if(execlp("./lv1a", "lv1a", ppid, NULL) < 0);
			printf("Greska pri izvrsavanju procesa deteta!");
		return -1;
	}

	printf("Proces generator id pid: %d, a dete: %d\n\n", getpid(), pid);

	while(timesGenerated < 1024)
	{
		pause();
	}

	printf("\nPROCES 1 GENERATOR JE ZAVRSIO!\n");

	return 0;
}
