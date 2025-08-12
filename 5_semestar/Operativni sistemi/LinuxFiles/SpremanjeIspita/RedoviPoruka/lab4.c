#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

#define MSGQKEY 44444
#define msgLEN 50

struct mymsg
{
	long type;
	char buf[msgLEN+1];
};

int main(int argc, char* argv[])
{
	int mqID;
	struct mymsg message;
	mqID = msgget(MSGQKEY, 0666 | IPC_CREAT);

	if(fork() != 0)
	{
		//RODITELJ
		do
		{
			printf("\nRoditelj: Unesite poruku: \n");
			gets(message.buf);
			message.type = 1;
			msgsnd(mqID, &message, msgLEN+1, 0);
		}
		while(strcmp(message.buf, "QUIT") != 0);

		wait(NULL);
		msgctl(mqID, IPC_RMID, 0);
	}
	else
	{
		//DETE
		do
		{
			msgrcv(mqID, &message, msgLEN+1, 1, 0);
			printf("\nDETE: Poruka je: %s\n", message.buf);
		}
		while(strcmp(message.buf, "QUIT") != 0);
		exit(0);
	}

	return 1;
}
