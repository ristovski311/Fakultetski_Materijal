#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>

#define MQKEY 44444

void erex(const char* errmsg) //error exit => erex
{
	printf("======\nGreska\n%s\n======\n", errmsg);
	exit(1);
}


struct mymsg
{
	long type;
	char line[256];
};


int main(int argc,char* argv[])
{
	int mqID = msgget(MQKEY, IPC_CREAT | 0666);

	struct mymsg msg;

	if(argc < 2)
	{
		erex("Nedovoljno argumenata!");
	}

	if(fork() == 0) //DETE1
	{
		FILE* f = fopen("prva.txt", "w");
		if(f < 0)
			erex("Neuspesno otvaranje fajla prva.txt.");

		while(1)
		{
			if(msgrcv(mqID, &msg, sizeof(msg.line), 1, 0) < 0)
				erex("Neuspesno primanje poruke u detetu 1.");

			if(strcmp(msg.line, "KRAJ") == 0)
				break;

			fprintf(f,"%s",msg.line);
		}

	}
	else if(fork() == 0) //DETE 2
	{
		FILE* f = fopen("druga.txt", "w");
		if(f < 0)
			erex("Neuspesno otvaranje fajla druga.txt.");

		while(1)
		{
			if(msgrcv(mqID, &msg, sizeof(msg.line), 2, 0) < 0)
				erex("Neuspesno primanje poruke u detetu 2.");

			if(strcmp(msg.line, "KRAJ") == 0)
				break;

			fprintf(f,"%s",msg.line);
		}
	}
	else //RODITELJ
	{
		FILE* f = fopen(argv[1], "r");

		if(f < 0)
			erex("Otvaranje fajla neupsesno!");

		while(fgets(msg.line, sizeof(msg.line), f) != NULL)
		{
			if(msg.line[0] == 'Z' || msg.line[0] == 'z')
				msg.type = 1;
			else
				msg.type = 2;

			if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
				erex("Neuspesno slanje!");
		}

		strcpy(msg.line, "KRAJ");
		msg.type = 1;
		if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
			erex("Neuspesno slanje!");
		msg.type = 2;
		if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
			erex("Neuspesno slanje!");

		fclose(f);

		wait(NULL);
		msgctl(mqID, IPC_RMID, 0);
	}


	return 0;
}
