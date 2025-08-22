#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <string.h>

#define MQKEY 44444

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n",msg);
	exit(1);
}

struct mymsg
{
	long type;
	int num;
};

int main(int argc, char* argv[])
{
	int mqID = msgget(MQKEY, IPC_CREAT | 0666);
	if(mqID < 0)
		exer("Neuspesno kreiranje msg Q!");

	if(fork() == 0) //Prvi proces
	{
		execl("./zad3b", "zad3b", NULL);
		exer("Neuspesno pokretanje prvog procesa!");
	}
	else if(fork() == 0) //Drugi proces
	{
		execl("./zad3c", "zad3c", NULL);
		exer("Neuspesno pokretanje drugog procesa!");
	}
	else //Treci
	{
		wait(NULL);
		wait(NULL);
		msgctl(mqID, IPC_RMID, 0);
	}
	return 0;
}
