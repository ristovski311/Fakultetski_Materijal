#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int i;
	double res;
	
	printf("pozvana sam");
	
	for(i = 0; i < argc - 1; i++)
	{
		res += atoi(argv[i+1]);
	}

	if(argc < 2)
	{
		printf("Morate uneti bar 1 broj!\n");
		return -1;
	}

	res = res / (argc - 1);

	printf("Aritmeticka sredina je %f\n", res);

	return 0;
}
