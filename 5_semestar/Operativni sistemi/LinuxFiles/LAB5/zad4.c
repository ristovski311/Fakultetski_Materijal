#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define QK 14141
#define MAXSIZE 1024

struct message
{
	long mtype;
	char text[MAXSIZE];

};

int main(int argc, char* argv[])
{
	FILE* f;
	int msgid = msgget(QK, 0666|IPC_CREAT);
	struct message msg;
	char line[MAXSIZE];

	if(argc < 2)
	{
		printf("Malo arg\n");
		return -1;
	}

	if(fork() != 0)
	{
		f = fopen(argv[1],"r");
		if(!f)
		{
			printf("Greska file\n");
			return -1;
		}

		while(fgets(line,sizeof(line),f) != NULL)
		{
			msg.mtype = 1;
			strcpy(msg.text, line);
			msgsnd(msgid, &msg, sizeof(msg.text), 0);
			msgrcv(msgid, &msg, sizeof(msg.text), 2, 0);
			printf("Linija ima %s velikih slova!\n", msg.text);
		}
		msg.mtype = 1;
		strcpy(msg.text, "KRAJ");
		msgsnd(msgid, &msg, sizeof(msg.text), 0);
		fclose(f);
		msgctl(msgid, IPC_RMID, NULL);
		wait(NULL);

	}
	else
	{
		int i;
		int num;

		while(1)
		{
			num = 0;
			msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);
			if(strcmp(msg.text, "KRAJ") == 0)
				break;
			strcpy(line, msg.text);
			i = 0;
			while(line[i] != 0)
			{
				if(line[i] <= 'Z' && line[i] >= 'A')
					num++;
				i++;
			}

			sprintf(msg.text, "%d", num);
			msg.mtype = 2;
			msgsnd(msgid, &msg, sizeof(msg.text), 0);
		}
	}


}
