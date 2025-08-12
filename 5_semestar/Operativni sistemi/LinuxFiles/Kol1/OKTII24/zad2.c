#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pd1[2];
	int pd2[2];
	char putanja[2000];
	char kljucna[100];
	int i;
	int len;
	char line[2000];
	FILE* f;

	if(pipe(pd1) == -1 || pipe(pd2) == -1)
	{
		printf("Greska pri otvaranju");
	}

	if(fork() != 0)
	{
		close(pd1[0]);
		close(pd2[1]);

		printf("Unesite putanju: ");
		scanf("%s", putanja);
		printf("Unesite kljucnu rec: ");
		scanf("%s", kljucna);

		len = strlen(putanja);
		write(pd1[1],&len, sizeof(int));
		write(pd1[1],putanja, len);
		len = strlen(kljucna);
		write(pd1[1], &len, sizeof(int));
		write(pd1[1], kljucna, len);

		printf("Kljucne reci u datoj putanji ima u sledecim linijama: \n");
		while(read(pd2[0], &i, sizeof(i)) > 0)
		{
			printf("%d.\n", i);
		}
		close(pd1[1]);
		close(pd2[0]);
		wait(NULL);
	}
	else
	{

		//DETE

		close(pd1[1]);
		close(pd2[0]);

		read(pd1[0], &len, sizeof(int));
		read(pd1[0], putanja, len);
		putanja[len] = '\0';

		read(pd1[0], &len, sizeof(int));
		read(pd1[0], kljucna, len);
		kljucna[len] = '\0';

		f = fopen(putanja, "r");
		i = 0;
		while(fgets(line, sizeof(line), f) != NULL)
		{
			if(strstr(line, kljucna))
			{
				write(pd2[1], &i, sizeof(int));
			}
			i++;
		}
		fclose(f);
		close(pd1[0]);
		close(pd1[1]);
	}

	return 0;
}
