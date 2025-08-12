#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ppid;

void obradiUSR1(int a)
{
	printf("Program 2 je primio USR1!\n");
	kill(ppid, SIGUSR2);
}

int main(int argc, char* argv[])
{
	signal(SIGUSR1,obradiUSR1);
	ppid = atoi(argv[1]);
	printf("Drugi proces kaze da je ppid: %d\n", ppid);
	pause();
	printf("Drugi se program zavrsava!\n");
	return 0;
}


