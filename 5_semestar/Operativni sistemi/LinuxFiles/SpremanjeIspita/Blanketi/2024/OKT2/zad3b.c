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
	printf("Proces 3 je pokrenut\n");

	int mqID = msgget(MQKEY, IPC_CREAT | 0666);
	struct mymsg msg;
	if(mqID < 0)
		exer("Greska kreiranja msg q!");

	FILE* f = fopen("druga.txt", "r");

	if(!f)
		printf("Neuspeh otvaranja druga.txt");

	while(fgets(msg.line, sizeof(msg.line), f) != NULL)
	{
		msg.type = 3;
		if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
			exer("Greska pri slanju iz procesa 3");
		printf("Proces 3 je poslao poruku\n");
	}

	strcpy(msg.line, "KRAJ");

	if(msgsnd(mqID, &msg, sizeof(msg.line), 0) < 0)
		exer("Greska pri slanju iz procesa 3");
	fclose(f);


	return 0;
}
