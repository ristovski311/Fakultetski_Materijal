#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <math.h>

#define MQKEY 44444

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n",msg);
	exit(1);
}

struct mymsg
{
	long type;
	char line[256];
};

int main(int argc, char* argv[])
{
	int mqID = msgget(MQKEY, IPC_CREAT | 0666);
	struct mymsg msg;
	if(mqID < 0)
		exer("Greska kreiranja msg q!");

	if(fork() == 0) //PROCES 2
	{
		execl("./zad3a", "zad3a", NULL);
		exer("Neuspesno pokretanje procesa 2");
	}
	else if(fork() == 0) //PROCES 3
	{
		execl("./zad3b", "zad3b", NULL);
		exer("Neuspesno pokretanje procesa 3");
	}
	else //PROCES 1
	{
		FILE* f1;
		FILE* f2;

		int p2Gotov = 0;
		int p3Gotov = 0;

		while(!p2Gotov || !p3Gotov)
		{
			if(!p2Gotov)
			{
				if(msgrcv(mqID, &msg, sizeof(msg.line), 2, 0) < 0)
					exer("Greska primanja poruke iz p2");

				printf("Stigla poruka iz p2\n");

				if(strcmp("KRAJ", msg.line) == 0)
					p2Gotov = 1;
				else
				{
					int i = 0;
					while(msg.line[i] != '\0')
					{
						if(msg.line[i] >= 'a' && msg.line[i] <= 'z')
							msg.line[i] -= ('a' - 'A');
						i++;
					}

					f1 = fopen("prva_mod.txt", "a");
					if(f1 == NULL)
						exer("Neuspesno otvaranje fajla prva_mod.txt");
					fprintf(f1,"%s", msg.line);
					fclose(f1);
				}
			}

			if(!p3Gotov)
			{
				if(msgrcv(mqID, &msg, sizeof(msg.line), 3, 0) < 0)
					exer("Greska primanja poruke iz p3");

				printf("Stigla poruka iz p3\n");

				if(strcmp("KRAJ", msg.line) == 0)
					p3Gotov = 1;
				else
				{
					int i = 0;
					while(msg.line[i] != '\0')
					{
						if(msg.line[i] >= 'A' && msg.line[i] <= 'Z')
							msg.line[i] += ('a' - 'A');
						i++;
					}

					f2 = fopen("druga_mod.txt", "a");
					if(f2 == NULL)
						exer("Neuspesno otvaranje fajla druga_mod.txt");
					fprintf(f2,"%s", msg.line);
					fclose(f2);
				}
			}

		}

		msgctl(mqID, IPC_RMID, 0);
	}

	return 0;
}
