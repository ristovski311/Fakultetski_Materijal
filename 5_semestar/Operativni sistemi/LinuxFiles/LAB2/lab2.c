#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("Niste uneli staro i novo ime fajla!");
		return -1;
	}


	if(fork() == 0)
	{
		if(execl("/usr/bin/mv", "mv", argv[1], argv[2], NULL) == -1)
		{
			printf("Greska pri pozivu execl!\n");
			exit(-1);
		}
	}
	else
		wait(NULL);

	return 0;
}
