#include "implicit.h"
#include <time.h>

int main(int argc, char* argv[])
{
	int pd[2];
	char ch;
	int i;
	char buff[100];

	if(pipe(pd) == -1)
	{
		printf("Greska pri otvaranju pipe-a!\n");
		return -1;
	}

	if(fork() != 0)
	{
		close(pd[0]);
		srand(time(NULL));
		for(i = 0; i < 25; i++)
		{
			ch = (char)(random() % 27 + (int)'a');
			write(pd[1], &ch, 1);
		}
		close(pd[1]);
	}
	else
	{
		close(pd[1]);
		sprintf(buff, "%d", pd[0]);
		execl("./zad6B", "zad6B", buff , NULL);
		printf("Doslo je do greske pri izvrsenju drugog procesa!\n");
	}
	return 0;
}
