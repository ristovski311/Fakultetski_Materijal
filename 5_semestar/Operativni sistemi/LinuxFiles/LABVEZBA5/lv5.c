#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define QKEY 12002

struct message
{
	long mtype;
	int num;
};


int main(int argc, char* argv[])
{
	FILE* f;
	int input;
	struct message msg;
	int msgid = msgget(QKEY, 0666|IPC_CREAT);

	if(fork() != 0)
	{
		//RODITELJ

		do
		{
			printf("Uneti PRIRODAN broj: ");
			scanf("%d", &input);
			if(input < 1)
				printf("Niste uneli prirodan broj!\n");
			else
			{
				msg.mtype = 3;
				msg.num = input;
				msgsnd(msgid, &msg, sizeof(msg.num), 0);
			}
		}while(input != 787);
		wait(NULL);
		msgctl(msgid, IPC_RMID, NULL);


	}
	else
	{
		//DETE

		f = fopen("izlaz.txt", "w");
		if(!f)
		{
			printf("File za izlaz nije otvoren!\n");
			return -1;
		}

		do
		{
			msgrcv(msgid, &msg, sizeof(msg.num), 3, 0);
			input = msg.num;
			fprintf(f,"Broj: %d\n", input);

		}while(input != 787);

		fclose(f);

	}



}

