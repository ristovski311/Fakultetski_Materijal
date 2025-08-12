#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/types.h>

union semun
{
	int val;
	struct semid_ds* buf;
	ushort* array;
	struct seminfo* __buf;
	void* __pad;
};

int mutexid, parniid, neparniid;

int main(int argc, char* argv[])
{
	FILE* f;
	int i;
	union semun semopts;

	struct sembuf sem_lock = { 0, -1 , NULL};
	struct sembuf sem_unlock = {0, 1, NULL};

	if(argc < 2)
	{
		printf("niste uneli naziv fajla!\n");
		return -1;
	}

	mutexid = semget((key_t)1, 1, 0666|IPC_CREAT);
	parniid = semget((key_t)2, 1, 0666|IPC_CREAT);
	neparniid = semget((key_t)3, 1, 0666|IPC_CREAT);

	semopts.val = 1;

	semctl(mutexid, 0, SETVAL, semopts);
	semctl(neparniid, 0, SETVAL, semopts);

	semopts.val = 0;

	semctl(parniid, 0, SETVAL, semopts);

	if(fork() == 0)
	{
		for(i = 2; i <= 20; i+=2)
		{
			semop(parniid, &sem_lock, 1);
			semop(mutexid, &sem_lock, 1);

			f = fopen(argv[1], "a");
			fprintf(f,"%d\n",i);
			fclose(f);

			semop(mutexid, &sem_unlock, 1);
			semop(neparniid, &sem_unlock,1);
		}
	}
	else
	{
		for(i = 1; i < 20; i+=2)
		{
			semop(neparniid, &sem_lock, 1);
			semop(mutexid, &sem_lock, 1);

			f = fopen(argv[1], "a");
			fprintf(f, "%d\n", i);
			fclose(f);

			semop(mutexid, &sem_unlock, 1);
			semop(parniid, &sem_unlock, 1);
		}

		semctl(mutexid, 0, IPC_RMID, 0);
		semctl(neparniid, 0, IPC_RMID, 0);
		semctl(parniid, 0, IPC_RMID, 0);
	}

	return 0;
}
