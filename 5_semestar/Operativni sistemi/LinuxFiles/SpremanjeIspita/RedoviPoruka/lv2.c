#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define MQKEY 12002

struct mymsg
{
	long type;
	int num;
};


int main(int argc, char* argv[])
{
	int mqID = msgget(MQKEY, IPC_CREAT | 0666);
	int num;
	struct mymsg msg;

	if(argc < 2)
	{
		printf("Nedovoljno argumenata!\n");
		return -1;
	}

	int pid = fork();

	if(pid == -1)
	{
		printf("Greska fork!\n");
		return -1;
	}
	else if(pid == 0)
	{

		// DETE

		int f = open(argv[1], O_WRONLY | O_CREAT, 0777);

		if(f < 0)
		{
			printf("Greska prilikom otvaranja fajla!\n");
			return -1;
		}

		do
		{
			if(msgrcv(mqID, &msg, sizeof(msg.num), 3, 0) < 0)
			{
				printf("Greska prilikom primanja poruke!\n");
				exit(1);
			}

			num = msg.num;

			char toFile[32];

			sprintf(toFile, "Broj: %d\n", num);

			write(f, toFile, strlen(toFile));


		}while(num != 787);

		printf("Proces dete zavrsilo!");

		close(f);

	}
	else
	{
		// RODITELJ

		msg.type = 3;

		do
		{
			printf("Unesite broj: ");
			scanf("%d", &num);

			printf("Roditelj: %d\n", num);

			msg.num = num;

			if(msgsnd(mqID, &msg, sizeof(msg.num), 0) < 0)
			{
				printf("Greska pri slanju podatka!\n");
				return -1;
			}


		}while(num != 787);

		wait(NULL);

		msgctl(mqID, IPC_RMID, 0);
	}

	return 0;

}
