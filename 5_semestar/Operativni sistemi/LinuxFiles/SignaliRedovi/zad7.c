#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int counterC = 0;
int counterZ = 0;

void obradiZ(int a)
{
	signal(SIGTSTP, obradiZ);
	counterZ ++;

	if(counterZ == 2)
	{
		printf("Trenutno je %d puta pritisnuto CTRL+C!\n", counterC);
		counterZ = 0;
	}

}

void obradiC(int a)
{
	counterC++;
	signal(SIGINT, obradiC);

	if(counterC == 5)
	{
		printf("Da li ste sigurni? [Y/N]: ");
		char input[100];
		fgets(input, 100, stdin);
		if(input[0] == 'y' || input[0] == 'Y')
			exit(-1);
		else
			counterC = 0;
	}
}

int main()
{

	signal(SIGINT, obradiC);
	signal(SIGTSTP, obradiZ);

	printf("Kombinacijom 5 tastera CTRL+C se prekida program!\nCTRL+Z dvaput prikazuje trenutni broj pritisnutih tastera CTRL+C!\n");

	while(1)
		pause();

	return 0;
}
