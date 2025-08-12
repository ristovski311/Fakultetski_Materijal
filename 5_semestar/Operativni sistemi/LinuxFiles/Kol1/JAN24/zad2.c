#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
	char sentence[500];
	int i;
	char* word;
	char childWord[200];
	int pd1[2];
	int pd2[2];
	int wlen;
	int sum;

	if(pipe(pd1) == -1 || pipe(pd2) == -1)
	{
		printf("Greska prilikom kreiranja pipe-ova\n");
		return -1;
	}

	printf("Unesite recenicu: ");
	fgets(sentence,sizeof(sentence),stdin);


	if(fork() != 0)
	{
		//RODITELJ

		close(pd1[0]);
		close(pd2[1]);

		word = strtok(sentence, " ");
		while(word!=NULL)
		{
			wlen = strlen(word);
			write(pd1[1], &wlen, sizeof(int));
			write(pd1[1], word, wlen);
			read(pd2[0], &sum, sizeof(int));
			printf("Suma cifara u reci %s je %d\n", word, sum);
			word = strtok(NULL," ");
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

		while(read(pd1[0],&wlen,sizeof(int)) > 0)
		{
			read(pd1[0], childWord, wlen);
			childWord[wlen] = '\0';
			sum = 0;
			i=0;
			while(childWord[i] != '\0')
			{
				if(childWord[i] <= '9' && childWord[i] >= '0')
					sum += (childWord[i] - '0');
				i++;
			}
			write(pd2[1], &sum, sizeof(int));

		}
		close(pd1[0]);
		close(pd2[1]);

	}




	return 0;
}
