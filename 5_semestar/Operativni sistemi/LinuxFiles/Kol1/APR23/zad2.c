#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>



int main(int argc, char* argv[])
{
	int status;
	if(argc < 3)
	{
		printf("Nedovoljno argumenata!\n");
		return -1;
	}

	if(fork() != 0)
	{

		wait(&status);
		printf("Proces dete je izasao sa statusom: %d\n", status);
	}
	else
	{
		execl(argv[1], argv[1], argv[2], NULL);
		printf("Doslo je do greske!\n");
		exit(-1);
	}
	return 0;
}
