#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char* argumenti[3];

	argumenti[0] = (char*)malloc(sizeof(char) * 30);
	argumenti[1] = (char*)malloc(sizeof(char) * 30);

	if(argc < 2)
	{
		printf("Nije unet fajl");
		return -1;
	}


	strcpy(argumenti[0], "rm");
	strcpy(argumenti[1], argv[1]);
	argumenti[2] = NULL;

	execvp("rm", argumenti);


	return 0;
}
