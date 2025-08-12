#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define QID 10500

int pid;

struct message
{
	long mtype;
	time_t time;
};

void obradiALARM(int m)
{
	struct message msg;
	int msgid = msgget(QID, 0666|IPC_CREAT);

	msg.mtype = 20;
	msg.time = time(NULL);

	if(msgsnd(msgid, &msg, sizeof(time_t), 0) == -1)
	{
		printf("Greska pri slanju!\n");
		exit(-1);
	}
	printf("Poslato vreme!");
	kill(pid, SIGUSR1);
}

void obradiALARMDETE(int m)
{
	sleep(3);
        struct message msg;
        int msgid = msgget(QID, 0666);

        if(msgrcv(msgid, &msg, sizeof(time_t), 20, 0) == -1)
        {
                printf("Greska pri prijemu!\n");
                exit(-1);
        }
        printf("Vreme: %s\n", ctime(&msg.time));
}

void obradiINT(int m)
{
	int msgid = msgget(QID, 0666);
	if(msgid == -1)
	{
		printf("Nema takvog reda poruka!\n");
	}
	sleep(5);
	msgctl(msgid, IPC_RMID,NULL);
	kill(pid, SIGINT);
	exit(0);

}


int main(int argc, char* argv[])
{
	pid = fork();
	if(pid == 0)
	{
		signal(SIGUSR1, obradiALARMDETE);
		while(1)
			pause();
	}
	else
	{
		signal(SIGALRM, obradiALARM);
		signal(SIGINT, obradiINT);

		while(1)
		{
			alarm(1);
			pause();
		}
	}
}
