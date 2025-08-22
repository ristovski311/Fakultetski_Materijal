#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define SHMKEY 40004
#define MUTKEY 40005
#define FULLKEY 40006
#define EMPTYKEY 40007

#define N 10

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(1);
}

union semun
{
	int val;
	struct semid_ds* buf;
	ushort* array;
	struct seminfo* __buf;
	void* __pad;
};

int main(int argc, char* argv)
{
	int mutexid, fullid, emptyid, shmid;
	union semun semopts;

	mutexid = semget(MUTKEY, 1, IPC_CREAT | 0666);
	fullid = semget(FULLKEY, 1, IPC_CREAT | 0666);
	emptyid = semget(EMPTYKEY, 1, IPC_CREAT | 0666);
	shmid = shmget(SHMKEY, sizeof(int) * N, IPC_CREAT | 0666);

	if(mutexid < 0)
		exer("Greska pri stvaranju mutexa!");
	if(fullid < 0)
		exer("Greska pri stvaranju full sema!");
	if(emptyid < 0)
		exer("Greska pri stvaranju empty sema!");
	if(shmid < 0)
		exer("Greska pri stvaranju shared mem id!");

	semopts.val = 1;
	semctl(mutexid, 0, SETVAL, semopts);
	semopts.val = N;
	semctl(emptyid, 0, SETVAL, semopts);
	semopts.val = 0;
	semctl(fullid, 0, SETVAL, semopts);

	if(fork() == 0) //PROIZVODJAC
	{
		execl("./lab1pr", "lab1pr", NULL);
		exer("Greska pri pokretanju proizvodjaca!");
	}
	else if(fork() == 0) //POTROSAC
	{
		execl("./lab1po", "lab1po", NULL);
		exer("Greska pri pokretanju potrosaca!");
	}
	else
	{
		wait(NULL);
		wait(NULL);

		semctl(mutexid, 0, IPC_RMID, 0);
		semctl(emptyid, 0, IPC_RMID, 0);
		semctl(fullid, 0, IPC_RMID, 0);
		semctl(shmid, IPC_RMID, 0);
	}

	return 0;
}
