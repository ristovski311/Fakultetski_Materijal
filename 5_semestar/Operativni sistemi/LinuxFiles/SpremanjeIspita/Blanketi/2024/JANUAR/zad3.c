#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MQKEY 44444
#define MAXBUF 256

void exer(const char * msg) // EXIT ERROR = EXER
{
	printf("\n======\nGreska\n%s\n======\n", msg);
	exit(1);
}


struct mymsg
{
	long type;
	char ime[MAXBUF];
	char prezime[MAXBUF];
	int brojIndeksa;
};

int main(int argc, char* argv[])
{
	int mqID = msgget(MQKEY, IPC_CREAT | 0666);
	struct mymsg msg;
	if(mqID < 0)
		exer("Nije se uspesno otvorio msg q!");


	if(fork() == 0) //DETE 1
	{
		int min = 99999999;
		int max = 0;

		FILE* a1 = fopen("a1.txt", "w");
		fprintf(a1,"AMFITEATAR A1\n\n");

		while(1)
		{
			if(msgrcv(mqID, &msg, sizeof(msg.ime) + sizeof(msg.prezime) + sizeof(msg.brojIndeksa), 1, 0) < 0)
				exer("Greska pri citanju u 1");
			if(msg.brojIndeksa == -1)
				break;

			fprintf(a1, "%s %s %d\n", msg.ime, msg.prezime, msg.brojIndeksa);

			if(msg.brojIndeksa < min)
				min = msg.brojIndeksa;
			if(msg.brojIndeksa > max)
				max = msg.brojIndeksa;
		}

		printf("\n[DETE 1]\nMIN: %d\nMAX: %d\n", min, max);

	}
	else if(fork() == 0) //DETE 2
	{
		int min = 99999999;
		int max = 0;

		FILE* a2 = fopen("a2.txt", "w");
		fprintf(a2,"AMFITEATAR A2\n\n");

		while(1)
		{
			if(msgrcv(mqID, &msg, sizeof(msg.ime) + sizeof(msg.prezime) + sizeof(msg.brojIndeksa), 2, 0) < 0)
				exer("Greska pri citanju u 2");
			if(msg.brojIndeksa == -1)
				break;

			fprintf(a2, "%s %s %d\n", msg.ime, msg.prezime, msg.brojIndeksa);

			if(msg.brojIndeksa < min)
				min = msg.brojIndeksa;
			if(msg.brojIndeksa > max)
				max = msg.brojIndeksa;
		}

		printf("\n[DETE 2]\nMIN: %d\nMAX: %d\n", min, max);

	}
	else //RODITELJ
	{

		FILE* f = fopen("prijava.txt", "r");

		while(fscanf(f, "%s %s %d", msg.ime, msg.prezime, &msg.brojIndeksa) == 3)
		{
			if(msg.brojIndeksa < 18000)
				msg.type = 1;
			else
				msg.type = 2;

			if(msgsnd(mqID, &msg, sizeof(msg.ime) + sizeof(msg.prezime) + sizeof(msg.brojIndeksa),0) < 0)
				exer("Neuspesno slanje!");
		}

		msg.type = 1;
		msg.brojIndeksa = -1;
		if(msgsnd(mqID, &msg, sizeof(msg.ime) + sizeof(msg.prezime) + sizeof(msg.brojIndeksa),0) < 0)
			exer("Neuspesno slanje kraja 1!");
		msg.type = 2;
		if(msgsnd(mqID, &msg, sizeof(msg.ime) + sizeof(msg.prezime) + sizeof(msg.brojIndeksa),0) < 0)
			exer("Neuspesno slanje kraja 2!");

		wait(NULL);
		msgctl(mqID, IPC_RMID, 0);

	}


	return 0;
}
