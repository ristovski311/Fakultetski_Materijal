#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <string.h>

#define MQKEY 44444

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n",msg);
	exit(1);
}

struct mymsg
{
	long type;
	int num;
};

int main(int argc, char* argv[])
{
	int sum = 0;
	int mqID = msgget(MQKEY, IPC_CREAT | 0666);
	struct mymsg msg;

	if(mqID < 0)
		exer("Neuspesno kreiranje msg Q u procesu 1!");

	while(sum <= 1000)
	{
		msg.type = 1;

		printf("Unesite broj: ");
		scanf("%d", &msg.num);

		sum+= msg.num;

		if(msgsnd(mqID, &msg, sizeof(msg.num), 0) < 0)
			exer("Neuspesno slanje poruke!");

		if(msgrcv(mqID, &msg, sizeof(msg.num), 2, 0) < 0)
			exer("Neuspesan ack!");

	}

	return 0;
}
