#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

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

int main(int argc, char* argv)
{
	int i = 0;

	int mutexid, fullid, emptyid, shmid;
	struct sembuf sem_lock = {0, -1, NULL};
	struct sembuf sem_unlock = {0, 1, NULL};
	int num;

	int* shmptr;

	srand(time(NULL));

	mutexid = semget(MUTKEY, 1, IPC_CREAT | 0666);
	fullid = semget(FULLKEY, 1, IPC_CREAT | 0666);
	emptyid = semget(EMPTYKEY, 1, IPC_CREAT | 0666);
	shmid = shmget(SHMKEY, sizeof(int) * N, IPC_CREAT | 0666);

	if(mutexid < 0)
		exer("Greska pri stvaranju mutexa! PO");
	if(fullid < 0)
		exer("Greska pri stvaranju full sema! PO");
	if(emptyid < 0)
		exer("Greska pri stvaranju empty sema! PO");
	if(shmid < 0)
		exer("Greska pri stvaranju shared mem id! PO");

	shmptr = (int*)shmat(shmid, NULL, 0);
	if(shmptr == 0)
		exer("Neuspesan attach kod potrosaca!");

	while(i < 2*N)
	{

		semop(fullid, &sem_lock, 1);
		semop(mutexid, &sem_lock, 1);

		num = shmptr[i%N];

		semop(mutexid, &sem_unlock, 1);
		semop(emptyid, &sem_unlock, 1);

		printf("[Iteracija %d] Broj | %d\n", i/10, num);
		i++;
	}

	return 0;
}
