#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define QID 4444

struct message1
{
	long mtype;
	char buf[1024];
};

struct message2
{
	long mtype;
	int brojLinije;
	int brojPojava;
};

int main(int argc, char* argv[])
{
	if(argc < 2)
		return -1;
	struct message1 msgSend;
	struct message2 msgRcv;

	int msgid = msgget(QID, 0666|IPC_CREAT);


	if(fork() != 0)
	{
		FILE* f = fopen(argv[1], "r");
		if(!f)
		{
			printf("Greska file!\n");
			return -1;
		}
		while(1)
		{
			if(fgets(msgSend.buf, sizeof(msgSend.buf), f) == NULL)
				break;

			msgSend.mtype = 1;

			if(msgsnd(msgid, &msgSend, sizeof(msgSend.buf), 0) == -1)
			{
				printf("Greska ssend!\n");
				return -1;
			}

			if(msgrcv(msgid, &msgRcv, sizeof(int) * 2, 2, 0) == -1)
			{
				printf("Greska rrecieve!\n");
				return -1;
			}

			printf("Linija : %d | broj pojava : %d\n", msgRcv.brojLinije, msgRcv.brojPojava);

		}
		strcpy(msgSend.buf, "GOTOVO");
		if(msgsnd(msgid, &msgSend, sizeof(msgSend.buf),0) == -1)
		{
			printf("Greska pri slanju signala za kraj!\n");
			return -1;
		}
		wait(NULL);
		msgctl(msgid, IPC_RMID, NULL);
		fclose(f);
	}
	else
	{
		int linija = 1;
		while(1)
		{
			if(msgrcv(msgid, &msgSend, sizeof(msgSend.buf),1, 0) == -1)
			{
				printf("Greska primanja poruke u detetu!\n");
				return -1;
			}

			if(strcmp(msgSend.buf, "GOTOVO") == 0)
				break;

			int i = 0;
			int br = 0;
			while(msgSend.buf[i] != '\0')
			{
				if(msgSend.buf[i] <= 'Z' && msgSend.buf[i] >= 'A')
					br++;
				i++;
			}

			msgRcv.mtype = 2;
			msgRcv.brojLinije = linija;
			msgRcv.brojPojava = br;

			if(msgsnd(msgid, &msgRcv, 2 * sizeof(int), 0) == -1)
			{
				printf("Greska pri slanju poruke iz deteta!\n");
				return -1;
			}


			linija++;
		}
	}

	return 0;
}
