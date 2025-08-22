#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMKEY 40004
#define SEM1KEY 40005
#define SEM2KEY 40006

#define MAXBUF 5

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n",msg);
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

int main(int argc, char* argv[])
{
	int shmid, sem1, sem2;
	int* shmptr;
	union semun semopts;
	struct sembuf semWait = {0,-1,0};
	struct sembuf semSignal = {0,1,0};
	int sum;

	sem1 = semget(SEM1KEY, 1, IPC_CREAT | 0666);
	sem2 = semget(SEM2KEY, 1, IPC_CREAT | 0666);

	if(sem1 == -1) exer("Sem 1 roditelj");
	if(sem2 == -1) exer("Sem 2 roditelj");

	semopts.val = 1;
	semctl(sem1, 0, SETVAL, semopts);
	semopts.val = 0;
	semctl(sem2, 0, SETVAL, semopts);

	shmid = shmget(SHMKEY, sizeof(int) * MAXBUF, IPC_CREAT | 0666);
	if(shmid == -1) exer("Shmid roditelj");

	shmptr = (int*)shmat(shmid, NULL, 0);

	if(fork() == 0) //SEM2 DETE
	{
		shmid = shmget(SHMKEY, sizeof(int) * MAXBUF, IPC_CREAT | 0666);
		if(shmid == -1) exer("Shmid dete");

		shmptr = (int*)shmat(shmid, NULL ,0);

		while(1)
		{
			sum = 0;

			semop(sem2, &semWait, 1);

			for(int i = 0; i < MAXBUF; i++)
				sum += shmptr[i];

			shmptr[0] = sum;

			semop(sem1, &semSignal, 1);

			if(sum == 0)
				break;
		}

		shmdt(shmptr);

	}
	else //SEM1 RODITELJ
	{
		while(1)
		{
			semop(sem1, &semWait, 1);

			for(int i = 0; i < MAXBUF; i++)
			{
				printf("Unesite broj: ");
				scanf("%d", &shmptr[i]);
			}

			semop(sem2, &semSignal, 1);
			//--- cekamo da dete sabere
			semop(sem1, &semWait, 1);
			sum = shmptr[0];
			printf("\nSuma je: [%d]\n", sum);
			semop(sem1, &semSignal, 1);

			if(sum == 0)
				break;
		}

		wait(NULL);

		shmdt(shmptr);
		shmctl(shmid, IPC_RMID, 0);
		semctl(sem1, 0, IPC_RMID, 0);
		semctl(sem2, 0, IPC_RMID, 0);
	}

	return 0;
}
