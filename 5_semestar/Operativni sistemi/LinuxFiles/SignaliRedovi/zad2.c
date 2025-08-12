#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

#define QID 12002

struct message
{
	long mtype;
	int broj;
};


int main()
{
	int broj;
	int msgid;
	struct message msg;

	printf("Za kraj programa uneti 787\n");

	msgid = msgget(QID, 0666|IPC_CREAT);

	if(fork() != 0)
	{
		while(1)
		{
			printf("Uneti prirodan broj\n");
			scanf("%d", &broj);
			if(broj <= 0)
			{
				printf("Broj nije prirodan broj!\n");
				continue;
			}

			msg.mtype = 3;
			msg.broj = broj;

			if(msgsnd(msgid, &msg, sizeof(msg), 0) == -1)
			{
				printf("Greska send!\n");
				return -1;
			}

			if(broj == 787)
				break;

		}
		wait(NULL);

	}
	else
	{
		while(1)
		{
			if(msgrcv(msgid, &msg, sizeof(msg), 3, 0) == -1)
			{
				printf("Greska recieve!\n");
				return -1;
			}

			if(msg.broj == 787)
				break;
			printf("Broj: %d\n", msg.broj);
		}

	}
	return 0;
}
