#include "imp.h"

int main(int argc,char* argv[])
{
	char buff[101];
	int i;
	FILE* f;
	int pd[2];

	if(pipe(pd) == -1)
	{
		printf("Pipe greska!\n"); return -1;
	}

	if(argc < 3)
	{
		printf("Niste uneli dovoljno argumenata!\n"); return -1;
	}

	if(fork() != 0)
	{
		// Roditelj

		close(pd[0]);
		f = fopen(argv[1],"r");
		if(f == 0)
		{
			printf("Greska pri otvaranju datoteke\n"); return -1;
		}

		while((fgets(buff, sizeof(buff), f)) != NULL)
		{
			printf("->  %s\n\n", buff);
			write(pd[1], buff, strlen(buff));
		}
		close(pd[1]);
		wait(NULL);
	}
	else
	{
		// Dete

		close(pd[1]);
		f = fopen(argv[2],"w");
		if(!f)
		{
			printf("Greska pri otvaranju fajla za ispis!\n"); return -1;
		}
		int count;
		while((count = read(pd[0], buff, sizeof(buff) - 1)) > 0)
		{
			buff[count] = '\0';
			printf("Dete -> %s\n\n",buff);
			fprintf(f,"%s",buff);
		}
		close(pd[0]);

	}


	return 0;
}
