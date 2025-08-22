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
#define RODKEY 4008

union semun
{
	int val;
	struct semid_ds* buf;
	unsigned short* array;
	struct seminfo* __buf;
};

void exer(const char* msg)
{
	printf("\nGreska!\n%s\n", msg);
	exit(1);
}

int main(int agrc, char* argv[])
{
	int shmid;
	int mutid, prviid, drugiid, rodid;
	char* shmptr;
	char* chars;
	int* ints;

	union semun semopts;
	struct sembuf sem_lock = {0,-1,NULL};
	struct sembuf sem_unlock = {0,1,NULL};

	mutid = semget(MUTKEY, 1, IPC_CREAT | 0666);
	prviid = semget(PRVIKEY,1, IPC_CREAT | 0666);
	drugiid = semget(DRUGIKEY, 1, IPC_CREAT | 0666);
	rodid = semget(RODKEY,1, IPC_CREAT | 0666);

	if(mutid == -1)
		exer("Mutex nije ispravno napravljen!");
	if(prviid == -1)
		exer("Prvi sem nije ispravno napravljen!");
	if(drugiid == -1)
		exer("Drugi sem nije ispravno napravljen!");

	if(rodid == -1)
		exer("Roditeljski sem nije ispravno napravljen!");

	shmid = shmget(SHMKEY, sizeof(char) * N, IPC_CREAT | 0666);
	if(shmid==-1)
		exer("Greska pri stvaranju deljive memorije!");

	semopts.val = 1;
	semctl(mutid, 0, SETVAL,semopts);
	semctl(prviid, 0, SETVAL,semopts);
	semopts.val = 0;
	semctl(drugiid, 0, SETVAL,semopts);
	semctl(rodid, 0, SETVAL,semopts);

	shmptr = (char*) shmat(shmid, NULL, 0);

	if(fork() == 0) //DETE1
	{
		execl("./lab2d1", "lab2d1", NULL);
		exer("Greska pri startovanju procesa  deteta 1");
	}
	else if(fork() == 0) //DETE 2
	{
		execl("./lab2d2", "lab2d2", NULL);
		exer("Greska pri startovanju procesa  deteta 2");
	}
	else //RODITELJ
	{

		FILE* f;
		int it = 1;

		int maxit = 4;

		while(it < maxit)
		{
			f = fopen("izlaz.txt", "a");

			fprintf(f, "\n===\nIteracija %d\n===\n\n", it);

			semop(rodid, &sem_lock, 1);
			semop(mutid, &sem_lock, 1);

			for(int i = 0; i < N; i++)
			{
				if(i % 16 == 0)
					fprintf(f, "\n");
				fprintf(f, "%c  ", shmptr[i]);
			}

			semop(mutid, &sem_unlock, 1);
			printf("Cekamo 15s!\n");
			fflush(stdout);
			sleep(15);
			printf("Protekle 15s!\n");
			fflush(stdout);

			semop(prviid, &sem_unlock, 1);

			fclose(f);

			it++;
		}

		wait(NULL);
		wait(NULL);

		shmdt(shmptr);

		shmctl(shmid, IPC_RMID, 0);
		semctl(prviid, 0, IPC_RMID, 0);
		semctl(drugiid, 0, IPC_RMID, 0);
		semctl(rodid, 0, IPC_RMID, 0);
	}

	return 0;
}
