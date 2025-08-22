#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <memory.h>

#define SHMKEY 40004
#define SEM1KEY 40005
#define SEM2KEY 40006
#define MAXBUF 10

union semun
{
	int val;
	struct semid_ds* buf;
	ushort* array;
	struct seminfo* __buf;
	void* ___pad;
};

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(1);
}

int main(int argc, char* argv)
{
	int pid, shmid, sem1, sem2;
	int * shmptr;
	union semun semopts;
	struct sembuf sem_wait = {0,-1,0};
	struct sembuf sem_signal = {0,1,0};

	sem1 = semget(SEM1KEY, 1, IPC_CREAT | 0666);
	sem2 = semget(SEM2KEY, 1, IPC_CREAT | 0666);

	if(sem1 == -1) exer("Otvaranje sem1");
	if(sem2 == -1) exer("Otvaranje sem2");

	semopts.val = 1;
	semctl(sem1, 0, SETVAL, semopts);

	semopts.val = 0;
	semctl(sem2, 0, SETVAL, semopts);

	shmid = shmget(SHMKEY, sizeof(int) * (MAXBUF + 1), IPC_CREAT | 0666);
	if(shmid == -1) exer("Kreiranje shm");

	shmptr = (int*)shmat(shmid, NULL, 0);

	pid = fork();
	if(pid == -1) exer("greska pri kreiranju deteta procesa");

	if(pid == 0) //DETE
	{
		int buffer[MAXBUF];

		shmid = shmget(SHMKEY, sizeof(int) * (MAXBUF + 1), 0666);
		if(shmid == -1) exer("SHMID dete");
		shmptr = (int*)shmat(shmid, NULL, 0);

		int sum;
		int count;

		while(1)
		{
			semop(sem2, &sem_wait, 1);
			memcpy(buffer, shmptr, sizeof(int) * MAXBUF);
			semop(sem1, &sem_signal, 1);

			count = shmptr[MAXBUF];

			if(count == 0)
				break;

			sum = 0;
			for(int i = 0; i < MAXBUF; i++)
				sum+=buffer[i];

			printf("Zbir = %d\n", sum);
		}

		shmdt(shmptr);

	}
	else //RODITELJ
	{
		FILE* f = fopen("brojevi.txt", "r");
		int count;

		while(count != 10)
		{
			semop(sem1, &sem_wait, 1);

			count = 0;
			for(int i = 0; i < MAXBUF; i++)
			{
				if(fscanf(f, "%d", &shmptr[i]) != 1)
				{
					count++;
					shmptr[i] = 0;
				}
			}

			shmptr[MAXBUF] = MAXBUF - count;

			semop(sem2, &sem_signal, 1);

		}

		fclose(f);

		wait(NULL);

		semctl(sem1, 0, IPC_RMID, 0);
		semctl(sem2, 0, IPC_RMID, 0);
		shmctl(shmid, IPC_RMID, 0);
	}

	return 0;
}
