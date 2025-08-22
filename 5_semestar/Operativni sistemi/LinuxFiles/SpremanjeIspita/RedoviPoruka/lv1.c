#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define MQKEY 44444
#define MAXBUF 15

struct product
{
	long type;
	int num;
};

int main(int argc, char* argv[])
{
	struct product prod;
	int mqID;
	int numLen;

	if(fork() == 0)
	{
		execl("./lv1a", "lv1a", NULL);
		printf("Greska prilikom pokretanja drugog procesa!\n");
		return -1;
	}

	mqID = msgget(MQKEY, IPC_CREAT | 0666);

	if(mqID < 0)
	{
		printf("Greska pri otvaranju mq!\n");
		return -1;
	}

	srand(time(NULL));

	numLen = rand() % MAXBUF;

	prod.type = 1;

	for(int i = 0; i < numLen; i++)
	{
		prod.num = rand() % 100;
		printf("RODITELJ: %d\n", prod.num);
		if(msgsnd(mqID, &prod, sizeof(prod.num), 0) < 0)
		{
			printf("Greska pri slanju!\n");
			return -1;
		}
	}

	prod.num = -1;
	if(msgsnd(mqID, &prod, sizeof(prod.num), 0) < 0)
	{
		printf("Greska prilikom slanja poslednje poruke!\n");
		return -1;
	}

	wait(NULL);
	msgctl(mqID, IPC_RMID, 0);

	return 0;
}
