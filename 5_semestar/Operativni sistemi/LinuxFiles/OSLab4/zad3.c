#include "implicit.h"
#include <time.h>

int main(int argc, char* argv[])
{
	int pd[2];
	int rand;
	char buff[128];
	int i;

	if(pipe(pd) == -1)
	{
		printf("Greska pri kreiranju datavoda!\n");
		return -1;
	}

	if(fork() != 0)
	{
		close(pd[0]);
		srand(time(NULL));

		for(i = 0; i < 20; i++)
		{
			rand = random() % 100 + 100;
			sprintf(buff, "%d", rand);
			write(pd[1], buff, 128);
		}
		wait(NULL);
		close(pd[1]);
	}
	else
	{
		close(pd[1]);

		for(i = 0; i < 20; i++)
		{
			read(pd[0], buff, 128);
			rand = atoi(buff);
			if(rand % 3 == 0)
				printf("\bBroj: %d\n", rand);
		}
		close(pd[0]);
	}

	return 0;
}
