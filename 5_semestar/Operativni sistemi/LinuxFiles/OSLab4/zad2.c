#include "implicit.h"
#include <time.h>
int main(int argc, char* argv[])
{
	int pd[2];
	int i;
	char buff[128];
	int N;
	int rand;

	printf("\nUnesite broj N: ");
	scanf("%d", &N);

	if(pipe(pd) == -1)
	{
		printf("Problem pri otvaranju datavoda!\n");
		return -1;
	}

	if(fork() != 0)
	{
		close(pd[0]);
		srand(time(NULL));
		for(i = 0; i < N; i++)
		{
			rand = random() % 100 + 1;
			sprintf(buff, "%d", rand);
			write(pd[1], buff, 128);
		}
		sprintf(buff, "%d", -1);
		write(pd[1], buff, 128);
		wait(NULL);
		close(pd[1]);
	}
	else
	{
		close(pd[1]);
		FILE* f;
		f = fopen("tmp.txt", "w");
		if(!f)
		{
			printf("problem pri otvaranju datoteke!\n");
			return -1;
		}
		read(pd[0], buff, 128);
		rand = atoi(buff);
		while(rand > 0)
		{
			fprintf(f,"%d\n", rand);
			read(pd[0], buff, 128);
			rand = atoi(buff);
		}
		fclose(f);
		close(pd[0]);
	}

	return 0;
}
