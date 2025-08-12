#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>

#define MSGSIZE 500
#define QK 44444

struct message
{
	long mtype;
	char text[MSGSIZE];
};

int main(int argc, char* argv[])
{
	char input[MSGSIZE];
	char output[MSGSIZE];
	int msgid = msgget(QK, 0666|IPC_CREAT);
	struct message msg;
	FILE* f;
	if(fork() != 0)
	{
		while(1)
		{
			printf("Unesi poruku:\n");
			fgets(input, sizeof(input), stdin);
			input[strlen(input)-1] = 0;
			msg.mtype = 1;
			strcpy(msg.text, input);
			msgsnd(msgid, &msg, MSGSIZE, 0);
			if(strcmp(input,"KRAJ") == 0)
				break;
		}
		wait(NULL);
		msgctl(msgid, IPC_RMID, NULL);
	}
	else
	{
		f = fopen("izlaz.txt","w");
		output[0] = '\0';
		while(1)
		{
			msgrcv(msgid, &msg, MSGSIZE, 0,0);
			strcpy(output, msg.text);
			fprintf(f,"%s\n",output);
			if(strcmp(output, "KRAJ") == 0)
				break;
		}
		fclose(f);
	}


	return 0;
}
