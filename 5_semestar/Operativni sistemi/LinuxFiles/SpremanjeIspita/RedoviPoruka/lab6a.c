#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define MQKEY 44444
#define MAXLEN 256

struct linemsg
{
	long type;
	char line[MAXLEN];
};


int main(int argc, char* argv[])
{
	FILE* f;
	int mqID;
	int neparna = 1;
	struct linemsg msg;

	if(fork() == 0)
	{
		if(execlp("./lab6b", "lab6b", NULL) < 0)
		{
			printf("Greska pri pokretanju programa B\n");
			exit(-1);
		}
	}
	else
	{
		if(fork() == 0)
		{
			if(execlp("./lab6c", "lab6c", NULL) < 0)
			{
				printf("Greska pri otvaranju programa C\n");
				exit(-1);
			}
		}
		else
		{
			mqID = msgget(MQKEY, 0666 | IPC_CREAT);

			f = fopen("./cela.txt", "r");
			while(fgets(msg.line, MAXLEN, f) != NULL)
			{
				if(neparna)
					msg.type = 1;
				else
					msg.type = 2;
				if(msgsnd(mqID, &msg, sizeof(msg.line), 0) == -1)
				{
					printf("Greska pri slanju!\n");
					exit(-1);
				}
				neparna = (neparna+1)%2;
			}
			fclose(f);
			strcpy(msg.line, "ENDOFFILE");
			msg.type = 1;
			if(msgsnd(mqID, &msg, sizeof(msg.line), 0) == -1)
			{
				printf("Greska pri poslednjem slanju 1!\n");
			}
			msg.type = 2;
			if(msgsnd(mqID, &msg, sizeof(msg.line), 0) == -1)
			{
				printf("Greska pri poslednjem slanju 2!\n");
			}

			printf("Cekam dete 1\n");
			wait(NULL);
			printf("Cekam dete 2\n");
			wait(NULL);

			msgctl(mqID, IPC_RMID, 0);
		}
	}

	return 0;
}
