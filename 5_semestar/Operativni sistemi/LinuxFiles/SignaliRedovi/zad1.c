#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#include <time.h>

#define QID 4444

struct message
{
	long msg_type;
	int broj;
};

int N;

int main()
{
	int i;
	struct message msg;
	int msgqid = msgget(QID, 0666|IPC_CREAT);

	srand(time(NULL));

	if(fork() == 0)
	{
		i = 0;
		while(1)
		{
			i++;
			if(msgrcv(msgqid, &msg, sizeof(msg), 1, 0) == -1)
			{
				printf("Greska pri recieve!\n");
				return -1;
			}

			if(msg.broj == -1)
			{
				printf("Dete zavrsava!\n");
				return 0;
			}

			printf("i = %d | Broj: %d\n", i, msg.broj);
		}
	}
	else
	{
		N = random()%100;

		printf("N=%d\n",N);

		for(i = 0; i <= N; i++)
		{
			msg.msg_type = 1;

			if(i == N)
			{
				msg.broj = -1;
			}
			else
			{
				msg.broj = random()%1000;
			}

			if(msgsnd(msgqid, &msg, sizeof(msg),0) == -1)
			{
				printf("Greska pri slanju!\n");
				return -1;
			}
		}
		printf("Roditelj je zavrsio!\n");
		wait(NULL);

	}

	return 0;
}
