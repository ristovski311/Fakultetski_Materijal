#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int ctrCPressed = 0;

void ctrCRedefined(int sid)
{
	if(ctrCPressed == 0)
	{
		printf("Morate pritisnuti jos jednom ctrC!\n");
		fflush(stdout);
		ctrCPressed++;
	}
	else
	{
		printf("Prekidamo program\n");
		exit(0);
	}

}

int main(int argc, char* argv[])
{
	signal(SIGINT, ctrCRedefined);
	while(1)
	{
		pause();
	}

	return 0;

}
