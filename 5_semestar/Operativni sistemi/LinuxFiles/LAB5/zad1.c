#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <time.h>

#define MSGLEN 50
#define QKEY 10500

struct message
{
	long mtype;
	time_t time;
};

void obradiALRM(int sig_num)
{
	signal(SIGALRM,obradiALRM);
	alarm(10);
        int msgid;
        struct message msg;
        msg.mtype=20;
	msgid = msgget(QKEY,0666|IPC_CREAT);
	if(msgid == -1)
	{
		printf("Greska msg q!\n");
		exit(-1);
	}
	msg.time = time(NULL);
	if(msgsnd(msgid, &msg, sizeof(time_t), 0) == -1)
	{
		printf("Greska pri slanju poruke!\n");
		exit(-1);
	}
	else
		printf("Uspesno poslata poruka!\n");

}

void obradiINT(int sig_num)
{
	signal(SIGINT, obradiINT);
	printf("Suspendujemo!\n");
	sleep(5);
	printf("Vracamo se nazad!\n");
	int msgid = msgget(QKEY, 0666);
	if(msgctl(msgid, IPC_RMID,NULL) == 0)
		printf("Brisemo red poruka!\n");

}

void obradiTSTP(int sig_num)
{
	signal(SIGTSTP,obradiTSTP);
	struct message msg;
	char msgTime[1000];
	int msgid = msgget(QKEY, 0666);
	msgrcv(msgid,&msg,sizeof(time_t),0,0);
	struct tm* localTime = localtime(&msg.time);
	if(strftime(msgTime,sizeof(msgTime),"%Y-%m-%d %H:%M:%S", localTime) == 0)
		printf("Greska vreme!\n");
	else
		printf("Vreme slanja poruke: %s\n", msgTime);

}

int main(int argc, char* argv[])
{
	signal(SIGALRM, obradiALRM);
	signal(SIGINT, obradiINT);
	signal(SIGTSTP, obradiTSTP);

	alarm(10);

	while(1)
		pause();

	return 0;
}
