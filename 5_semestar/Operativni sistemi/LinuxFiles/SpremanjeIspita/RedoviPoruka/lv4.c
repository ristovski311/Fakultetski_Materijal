#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MQKEY 44444

struct mymsg
{
	long type;
	char line[256];
};

void errorExit(const char * msg)
{
	printf("Greska: %s\n", msg);
	exit(1);
}


int main(int argc, char* argv[])
{

	int mqID = msgget(MQKEY, IPC_CREAT | 0666);
	struct mymsg msg;

	if(argc < 2)
		errorExit("Greska malo parametara!");

	if(fork() == 0)
	{
		// DETE
		int count;
		int linenum = 0;


		while(1)
		{
			count = 0;
			linenum++;
			if(msgrcv(mqID, &msg, sizeof(msg.line), 1, 0) < 0)
				errorExit("Greska pri prijemu linije kod deteta!");

			if(strcmp(msg.line, "KRAJ!") == 0)
				break;

			int i = 0;
			while(msg.line[i] != '\0')
			{
				if(msg.line[i] >= 'A' && msg.line[i] <= 'Z')
					count++;
				i++;
			}

			sprintf(msg.line, "Linija %d ima %d velikih slova.", linenum, count);
			msg.type = 2;

			if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
				errorExit("Greska pri slanju broja velikih slova roditelju.");
		}

		return 0;
	}
	else
	{
		// RODITELJ

		FILE* fd = fopen(argv[1], "r");
		if(fd < 0)
			errorExit("Greska prilikom otvaranja fajla!");

		while(fgets(msg.line, sizeof(msg.line), fd) != NULL)
		{
			msg.type = 1;
			if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
				errorExit("Greska pri slanju linije");
			if(msgrcv(mqID, &msg, sizeof(msg.line), 2, 0) < 0)
				errorExit("Greska pri prijemu broja velikih slova");

			printf("Roditelj: %s\n", msg.line);
		}

		msg.type = 1;
		strcpy(msg.line, "KRAJ!");

		if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
			errorExit("Greska pri slanju poslednje poruke detetu!");

		wait(NULL);

		printf("KRAJ!\n");

		msgctl(mqID, IPC_RMID, 0);
	}

	return 0;
}


