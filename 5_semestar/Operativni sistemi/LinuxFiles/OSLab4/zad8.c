#include "implicit.h"
#include <time.h>

int main(int agrc, char* argv[])
{
	int pd[2];
	int i;
	int rand;
	char buff[sizeof(int)+1];


	if(pipe(pd) == -1)
	{
		printf("greska pipe!\n");
		return -1;
	}

	if(fork() != 0)
	{
		close(pd[0]);
		srand(time(NULL));

		for(i= 0;i<20;i++)
		{
			rand = random()%191+10;

			sprintf(buff,"%d",rand);

			write(pd[1],buff,sizeof(int));
		}
		close(pd[1]);
		wait(NULL);
	}
	else
	{
		close(pd[1]);

		for(i = 0;i<20;i++)
		{
			read(pd[0],buff,sizeof(int));
			rand= atoi(buff);
			if(rand%2==0)
				printf("Paran broj: %d\n", rand);
			else
				printf("Neparan broj: -1\n");
		}
		close(pd[0]);
	}

	return 0;
}
