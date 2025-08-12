#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void obradiUSR2(int a)
{
	printf("Stigao je USR2 programu 1!\n");
}

int main()
{
	int pid;
	signal(SIGUSR2, obradiUSR2);

	pid = fork();

	if(pid == 0)
	{
		int ppid = getppid();
		char ppidS[100];
		sprintf(ppidS, "%d", ppid);
		execl("./proba2", "proba2", ppidS, NULL);
		printf("Greska u pozivu drugog programa!\n");
	}
	else
	{
		sleep(1);
		kill(pid, SIGUSR1);
		pause();
		printf("Program 1 zavrsava!\n");
	}

	return 0;
}
