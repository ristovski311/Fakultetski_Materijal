#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int cCount = 0;

void ObradiC(int sid)
{
	if(cCount < 4)
	{
		printf("\nPotrebno je da pritisnete jos puta CTRL+C\nZa trenutni broj pritisaka unesite CTRL+Z\n");
		fflush(stdout);
		cCount++;
		signal(SIGINT, ObradiC);
	}
	else
	{
		printf("\nIzlazimo!\n");
		fflush(stdout);
		exit(0);
	}
}

void ObradiZ(int sid)
{
	printf("\nTrenutno je pritisnutu CTRL+Z %d puta!\n", cCount);
	fflush(stdout);
	signal(SIGTSTP, ObradiZ);
}


int main(int argc, char* argv[])
{
	signal(SIGINT, ObradiC);
	signal(SIGTSTP, ObradiZ);

	while(1)
	{
		pause();
	}

	return 0;
}
