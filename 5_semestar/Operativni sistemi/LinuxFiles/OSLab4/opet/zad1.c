#include "imp.h"


int main()
{
	int pd1[2];
	int pd2[2];
	int niz[15];
	int i;
	FILE* f;

	if(pipe(pd1) == -1 || pipe(pd2) == -1)
	{
		printf("Greska pri otvaranju pipe-ova!");
		return -1;
	}

	if(fork() != 0)
	{
		//Roditelj

		if(fork() != 0)
		{
			//Roditelj

			close(pd1[0]);
			close(pd2[0]);

			srand(time(NULL));
			for(i = 0; i < 15; i++)
			{
				niz[i] = random()%100;
			}

			if(niz[0] % 2 == 0)
			{
				close(pd2[1]);
				write(pd1[1], &niz, sizeof(int) * 15);
				close(pd1[1]);
			}
			else
			{
				close(pd1[1]);
				write(pd2[1], &niz, sizeof(int) * 15);
				close(pd2[1]);
			}
			wait(NULL);
			wait(NULL);

		}
		else
		{
			//Dete 2

			close(pd1[0]);
			close(pd1[1]);
			close(pd2[1]);

			if((read(pd2[0],&niz,15*sizeof(int))) > 0)
			{
				for(i=0;i<15;i++)
				{
					printf("%d. => %d\n", i, niz[i]);
				}
			}
			close(pd2[0]);
		}

	}
	else
	{
		//Dete 1
		close(pd1[1]);
		close(pd2[1]);
		close(pd2[0]);
		if((read(pd1[0], &niz, sizeof(int)*15)) > 0)
		{
			f = fopen("PARNI.txt","w");
			for(i = 0; i < 15; i++)
			{
				fprintf(f,"%d. => %d\n", i, niz[i]);
			}
			fclose(f);

		}
		close(pd1[0]);
	}


	return 0;

}
