#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define MQKEY 44444
#define MAXLEN 256

struct linemsg
{
	long type;
	char line[256];
};

int main(int argc, char* argv[])
{
	int mqID = msgget(MQKEY, 0666|IPC_CREAT);
	struct linemsg msg;

	FILE *f = fopen("parne.txt", "w");

	while(1)
	{
		msgrcv(mqID, &msg, sizeof(msg.line), 2, 0);
		if(!strcmp(msg.line, "ENDOFFILE"))
			break;
		fprintf(f, "%s", msg.line);
	}

	fclose(f);

	return 1;
}
