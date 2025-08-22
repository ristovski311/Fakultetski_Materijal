#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <unistd.h>

#define MQKEY 44444

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n",msg);
	exit(1);
}

struct mymsg
{
	long type;
	char line[256];
};

int main(int argc, char* argv[])
{
	printf("Proces 2 je pokrenut!\n");

	int mqID = msgget(MQKEY, IPC_CREAT | 0666);
	struct mymsg msg;
	if(mqID < 0)
		exer("Greska kreiranja msg q!");

	FILE* f = fopen("prva.txt", "r");
	if(f < 0)
		exer("Neuspeh otvaranja prva.txt");

	while(fgets(msg.line, sizeof(msg.line), f) != NULL)
	{
		msg.type = 2;
		if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
			exer("Greska pri slanju iz procesa 2");
		printf("Proces 2 poslao poruku\n");
	}

	strcpy(msg.line, "KRAJ");

	if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
		exer("Greska pri slanju iz procesa 2");

	fclose(f);

	return 0;
}
