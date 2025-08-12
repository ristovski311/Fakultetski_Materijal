#include "implicit.h"

#include <time.h>

int main(int argc, char* argv[])
{
	int i;
	int pd[2];
	int num;
	char buff[4];

	if(pipe(pd) == -1)
	{
		printf("pipe greska\n");
		return -1;
	}

	if(fork() !=0)
	{
		close(pd[0]);
		srand(time(NULL));

		for(i = 0; i < 50; i++)
		{
			num = random() % 100;
			printf("->P1: %d\n", num);
			sprintf(buff, "%d", num);
			write(pd[1], buff, sizeof(int));
		}
		close(pd[1]);
	}
	else
	{
		close(pd[1]);

		sprintf(buff,"%d", pd[0]);

		execl("./zad7B", "zad7B", buff, NULL);

		printf("Greska pri izvrsenju fajla!\n");
	}


	return 0;
}
