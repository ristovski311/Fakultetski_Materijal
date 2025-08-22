#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <unistd.h>

#define MSGQKEY 44444

struct mymsg
{
	long type;
	int broj;
};

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(-1);
}

int main(int argc, char* argv)
{
	int msgid;
	struct mymsg msg;
	FILE* f;
	int sum = 0;

	msgid = msgget(MSGQKEY, IPC_CREAT | 0666);

	if(msgid == -1) exer("Nije uspesno napravljen msgq");

	if(fork() == 0) //DETE
	{
		msgid = msgget(MSGQKEY, 0666);
		if(msgid == -1) exer("Nije uspesno dobijen msgq");

		f = fopen("zbirovi.txt", "w");
		if(f == NULL) exer("Neuspesno otvaranje fajla!");

		while(1)
		{
			sum = 0;

			if(msgrcv(msgid, &msg, sizeof(msg.broj), 1, 0) < 0)
				exer("Greska pri dobijanju broja!");

			if(msg.broj == 0)
				break;

			fprintf(f, "Broj: %d", msg.broj);

			while(msg.broj > 0)
			{
				sum += (msg.broj % 10);
				msg.broj /= 10;
			}

			fprintf(f, " | [%d]\n", sum);
		}

		fclose(f);

	}
	else //RODITELJ
	{
		msg.type = 1;

		while(msg.broj != 0)
		{
			printf("Unesite broj: ");
			scanf("%d", &msg.broj);

			if(msg.broj == 0 || (msg.broj < 1000 && msg.broj > 99))
			{
				if(msgsnd(msgid, &msg, sizeof(msg.broj), 0) < 0)
					exer("Greska pri slanju poruke");
			}
			else
				printf("Samo trocifrene brojeve saljem detetu!");
		}

		wait(NULL);
		msgctl(msgid, IPC_RMID, 0);
	}

	return 0;
}
