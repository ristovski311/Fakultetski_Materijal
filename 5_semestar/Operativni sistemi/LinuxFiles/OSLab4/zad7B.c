#include "implicit.h"

int main(int argc, char* argv[])
{
	int i;
	int pd;
	int num;
	char buff[4];

	if(argc < 2)
	{
		printf("Greska malo arg!\n");
		return -1;
	}
	pd = atoi(argv[1]);

	for(i = 0;i<50;i++)
	{
		read(pd, buff, 4);
		num = atoi(buff);
		printf("Broj: %d\n", num);

	}
	close(pd);

	sleep(2);
	return 0;
}
