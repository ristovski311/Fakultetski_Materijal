#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MQKEY 44444

struct product
{
	long type;
	int num;
};

int main(int argc, char* argv[])
{
	struct product prod;
	int mqID;

	printf("Proces 2 je zapoceo!\n");

	mqID = msgget(MQKEY, IPC_CREAT | 0666);
	if(mqID < 0)
	{
		printf("Greska pri otvaranju msg Q u procesu 2!\n");
		return -1;
	}

	while(1)
	{
		if(msgrcv(mqID, &prod, sizeof(prod.num), 1, 0) < 0)
		{
			printf("Greska pri prijemu!\n");
			return -1;
		}

		if(prod.num == -1)
			break;

		printf("DETE: %d\n", prod.num);

	}

	return 0;
}
