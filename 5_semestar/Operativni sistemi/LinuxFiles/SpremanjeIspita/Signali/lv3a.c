#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <time.h>
#include <unistd.h>

#define MQKEY 10500

struct mymsg {
	long type;
	time_t time;
};

int main(int argc, char* argv[])
{
	struct mymsg msg;
	char timeConv[64];
	struct tm *t;


	int mqID = msgget(MQKEY, IPC_CREAT | 0666);
	if(mqID < 0)
	{
		printf("Greska pri otvaranju msg Q u drugom procesu!\n");
		return -1;
	}

	while(1)
	{
		if(msgrcv(mqID, &msg, sizeof(msg.time), 20, 0) < 0)
		{
			printf("Greska prilikom citanja poruke!\n");
			return -1;
		}

		if(msg.time == (time_t)-1)
			break;


		t = localtime(&msg.time);
		strftime(timeConv, sizeof(timeConv), "%H:%M:%S",t);
		printf("Vreme: %s\n", timeConv);
	}

	printf("Proces 2 zavrsava!\n");

	return 0;
}
