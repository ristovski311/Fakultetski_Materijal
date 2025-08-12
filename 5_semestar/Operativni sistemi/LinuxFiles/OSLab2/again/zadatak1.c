#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>




int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Uneti fajl!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		return -1;
	}

	if(fork() == 0)
	{
		if(execlp("gcc", "gcc", "-o", "program", argv[1], "-g", NULL) == -1)
		{
			printf("Greska!");
			exit(-1);
		}
	}
	else
	{
		wait(NULL);
	}

	return 0;
}
