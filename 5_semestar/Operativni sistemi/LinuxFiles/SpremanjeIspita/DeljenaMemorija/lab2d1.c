#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>

#define SHMKEY 40009
#define N 1024
#define MUTKEY 40005
#define PRVIKEY 40006
#define DRUGIKEY 40007

void exer(const char* msg)
{
	printf("\nGreska!\n%s\n", msg);
	exit(1);
}

int main(int agrc, char* argv[])
{
	int shmid;
	int mutid, prviid, drugiid;
	char* shmptr;

	struct sembuf sem_lock = {0,-1,NULL};
	struct sembuf sem_unlock = {0,1,NULL};

	mutid = semget(MUTKEY, 1, IPC_CREAT | 0666);
	prviid = semget(PRVIKEY,1, IPC_CREAT | 0666);
	drugiid = semget(DRUGIKEY, 1, IPC_CREAT | 0666);

	if(mutid == -1)
		exer("D1 Mutex nije ispravno napravljen!");
	if(prviid == -1)
		exer("D1 Prvi sem nije ispravno napravljen!");
	if(drugiid == -1)
		exer("D1 Drugi sem nije ispravno napravljen!");

	shmid = shmget(SHMKEY, sizeof(char) * N, IPC_CREAT | 0666);
	if(shmid==-1)
		exer("D1 Greska pri stvaranju deljive memorije!");

	shmptr =(char*) shmat(shmid, NULL, 0);
	srand(time(NULL));

	int it = 1;
	int maxit = 4;

	while(it < maxit)
	{
		semop(prviid, &sem_lock, 1);
		semop(mutid, &sem_lock, 1);

		for(int i = 0 ; i < 512; i++)
		{
			shmptr[i] = (rand() % 26 + 'a');
		}

		semop(mutid, &sem_unlock, 1);
		semop(drugiid, &sem_unlock, 1);
		it++;
	}

	return 0;
}
