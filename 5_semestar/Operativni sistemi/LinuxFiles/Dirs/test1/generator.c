#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int i;
	char toCopy[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

	if(argc < 3)
	{printf("Nedovoljno parametara!"); return -1;}

	FILE* f = fopen(argv[1], "w");

	for(i = 0; i < atoi(argv[2]); i++)
	{
		fprintf(f,"%s\n",toCopy);

	}
	fclose(f);

	return 0;
}
