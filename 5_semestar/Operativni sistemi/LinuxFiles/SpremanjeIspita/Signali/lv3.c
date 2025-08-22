#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/wait.h>


#define MQKEY 10500
int mqID;

struct mymsg
{
	long type;
	time_t time;
};

void obradiAlarm(int sid)
{
	struct mymsg msg;
	msg.type = 20;
	time(&msg.time);
	if(msgsnd(mqID, &msg, sizeof(msg.time), 0) < 0)
	{
		printf("Neuspesno slanje poruke!\n");
		exit(1);
	}
	printf("Uspesno poslata poruka!\n");
	signal(SIGALRM, obradiAlarm);
}

void obradiSIGINT(int sid)
{
	struct mymsg endmsg;
	sleep(5);
	endmsg.time = -1;
	endmsg.type = 20;
	if(msgsnd(mqID, &endmsg, sizeof(endmsg.time), 0) < 0)
	{
		printf("Greska pri slanju zatvarajuce poruke!\n");
		exit(1);
	}
	wait(NULL);
	msgctl(mqID, IPC_RMID, 0);
	printf("Zavrsavamo!\n");
	exit(1);
}

int main(int argc, char* argv[])
{
	mqID = msgget(MQKEY, IPC_CREAT | 0666);

	if(fork() == 0)
	{
		execl("./lv3a", "lv3", NULL);
		printf("Greska pri pokretanju novog procesa!\n");
		return -1;
	}

	if(mqID < 0)
	{
		printf("Greska pri kreiranju reda poruka!\n");
		return -1;
	}


	signal(SIGALRM, obradiAlarm);
	signal(SIGINT, obradiSIGINT);

	while(1)
	{
		alarm(2);
		pause();
	}


	return 0;
}
