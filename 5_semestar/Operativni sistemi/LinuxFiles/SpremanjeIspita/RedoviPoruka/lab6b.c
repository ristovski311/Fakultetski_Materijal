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

	FILE *f = fopen("neparne.txt", "w");

	while(1)
	{
		msgrcv(mqID, &msg, sizeof(msg.line), 1, 0);
		if(strcmp(msg.line, "ENDOFFILE") == 0)
			break;
		//printf("\n--\n%s\n--\n",msg.line);
		fprintf(f, "%s", msg.line);
	}

	fclose(f);

	return 1;
}
