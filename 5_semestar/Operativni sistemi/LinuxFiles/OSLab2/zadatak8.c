#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("Unesite sve argumente!\n");
		return -1;
	}

	char broj[40];
	char imeFajla[100];

	strcpy(imeFajla, argv[1]);
	strcpy(broj, argv[2]);

	if(execl("/usr/bin/head", "head", "-n", broj, imeFajla, NULL) == -1)
	{
		printf("Neuspeh\n");
		return -1;
	}

	return 0;

}
