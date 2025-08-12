#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/file.h>

int main()
{
	int pd1[2];
	int pd2[2];
	int i;
	int num;
	char buff[64];
	int f = open("redirekcija.txt",O_CREAT | O_RDWR,0777);
	if(!f)
	{
		printf("Greska pri otvaranju fajla!");
	}
	dup2(f,1);
	close(f);


	if(pipe(pd1) == -1)
	{
		printf("Greska pri pravljenju datavoda 1!\n");
		return -1;
	}

	if(pipe(pd2) == -1)
	{
		printf("Greska pri pravljenju datavoda 2!\n");
		return -1;
	}


	if(fork() != 0)
	{
		// Roditelj

		if(fork() != 0)
		{
			// Roditelj
			close(pd2[1]);
			close(pd2[0]);
			close(pd1[0]);
			srand(time(NULL));
			for(i = 0; i < 10; i++)
			{
				num = random() % 100;
				sprintf(buff, "%d", num);
				write(pd1[1], buff, sizeof(int));
			}
			close(pd1[1]);
			wait(NULL);
			wait(NULL);
		}
		else
		{
			// Dete2

			close(pd1[1]);
			close(pd1[0]);
			close(pd2[1]);

			for(i = 0; i< 10; i++)
			{
				read(pd2[0], buff, sizeof(int));
				num = atoi(buff);
				if(num > 10)
					printf("%d\n", num);
			}
			close(pd2[0]);
		}

	}
	else
	{
		// Dete1

		close(pd1[1]);
		close(pd2[0]);

		for(i = 0; i < 10; i++)
		{
			read(pd1[0], buff, sizeof(int));
			num = atoi(buff);
			if(num % 2 == 0)
			{
				num /= 2;
				sprintf(buff,"%d",num);
			}
			write(pd2[1],buff,sizeof(int));
		}
		close(pd1[0]);
		close(pd2[1]);

	}

	return 0;
}
