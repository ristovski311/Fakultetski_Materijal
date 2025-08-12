#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	char buff[1024];
	int pd[2];
	FILE* f;
	int brLinije = 1;
	int i;
	int k;

	if(argc < 2)
	{
		printf("Nedovoljan broj argumenata!\n"); return -1;
	}

	if(pipe(pd) == -1)
	{
		printf("Greska pri otvaranju datavoda!\n"); return -1;
	}

	if(fork() != 0)
	{
		//Roditelj
		close(pd[0]);
		f = fopen(argv[1],"r");
		while(fgets(buff, sizeof(buff), f) != NULL)
		{
			//printf("Roditelj: %s\n", buff);
			if(strlen(buff) > 80)
			{
				write(pd[1], &brLinije, sizeof(int));
				k = strlen(buff);
				write(pd[1], &k, sizeof(int));
				write(pd[1], buff, k);
			}
			brLinije++;
		}

		close(pd[1]);
		wait(NULL);

	}
	else
	{
		close(pd[1]);
		while((read(pd[0], &brLinije, sizeof(int))) > 0)
		{
			//printf("Dete: %d\n", brLinije);
			read(pd[0], &k, sizeof(int));
			i = read(pd[0],buff,k);
			//printf("Dete: i = %d, k = %d\n", i, k);
			buff[i] = '\0';
			if(brLinije % 2 == 0)
				printf("\n%d. %s\n", brLinije, buff);
		}

		close(pd[0]);
	}

	return 0;
}
