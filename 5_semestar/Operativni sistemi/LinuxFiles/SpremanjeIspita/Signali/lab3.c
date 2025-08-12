#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

char username[30];

void obradiAlarm(int sid)
{
	printf("\nVreme za unos je isteklo! Izlazim!\n");
	fflush(stdout);
	exit(0);
}


int main(int argc, char* argv[])
{
	signal(SIGALRM, obradiAlarm);

	printf("\nImate 30 sekundi da unesete username: ");
	fflush(stdout);

	alarm(30);

	gets(username);

	alarm(0);

	printf("\nUsername je: %s\n", username);

	return 0;
}
