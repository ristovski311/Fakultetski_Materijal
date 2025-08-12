#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int pd1[2];
	int pd2[2];
	char rec[30];
	int len;
	char res[10];
	char line[1024];
	FILE* f;


	if(pipe(pd1) == -1 || pipe(pd2) == -1)
	{
		printf("Problemi s pipe-om!\n");
		return -1;
	}

	if(fork() != 0)
	{
		//Roditelj
		close(pd1[0]);
		close(pd2[1]);

		while(1)
		{
			printf("Unesite rec: (END za kraj): ");
			scanf("%s", rec);
			len = strlen(rec);
			write(pd1[1], &len, sizeof(int));
			write(pd1[1],rec,strlen(rec));
			if(strcmp(rec, "END") == 0)
				break;
			read(pd2[0], &len, sizeof(int));
			read(pd2[0], res, len);
			res[len] = '\0';
			printf("Rezultat: %s\n", res);

		}

		close(pd1[1]);
		close(pd2[0]);
		wait(NULL);

	}
	else
	{
		//Dete
		close(pd1[1]);
		close(pd2[0]);

		int found;

		while(1)
		{
			found = 0;

			f = fopen("reci.txt", "r");

			if(!f)
			{
				printf("Greska file\n");
				close(pd1[0]);
				close(pd2[1]);
				return -1;
			}

			read(pd1[0], &len, sizeof(int));
			read(pd1[0], rec, len);
			rec[len] = '\0';

			if(strcmp(rec, "END") == 0)
				break;

			while(fgets(line, sizeof(line), f) != NULL && !found)
			{
				if(strstr(line, rec))
					found = 1;
			}

			if(found)
			{
				strcpy(res, "FOUND");
				len = 5;
				write(pd2[1], &len, sizeof(int));
				write(pd2[1], res, len);
			}
			else
			{
				strcpy(res, "NOT FOUND");
				len = 9;
				write(pd2[1], &len, sizeof(int));
				write(pd2[1], res, len);
			}
		}
		close(pd1[0]);
		close(pd2[1]);

	}



	return 0;
}
