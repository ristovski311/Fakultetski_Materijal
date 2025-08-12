#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};


int main(int argc, char* argv[])
{
	int i;
	FILE* f;

	int mutexid, parni, neparni;

	union semun semopts;

	struct sembuf sem_lock = {0,-1,NULL};
	struct sembuf sem_unlock = {0,1,NULL};

	mutexid = semget((key_t)1, 1, 0666|IPC_CREAT);
	parni = semget((key_t)2, 1, 0666|IPC_CREAT);
	neparni = semget((key_t)3, 1, 0666|IPC_CREAT);

	semopts.val = 1;
	semctl(mutexid, 0, SETVAL, semopts);
	semctl(neparni, 0, SETVAL, semopts);
	semopts.val = 0;
	semctl(parni, 0, SETVAL, semopts);

	if(argc < 2)
	{
		printf("Niste uneli naziv datoteke u koju se stampa!\n");
		return -1;
	}

	if(fork() == 0)
	{
		for(i = 2; i <= 20; i+=2)
		{
			semop(parni, &sem_lock, 1);
			semop(mutexid, &sem_lock, 1);
			f = fopen(argv[1], "a");
			fprintf(f,"%d\n", i);
			fclose(f);
			semop(mutexid, &sem_unlock, 1);
			semop(neparni, &sem_unlock, 1);
		}
	}
	else
	{
		for(i = 1; i < 20; i+=2)
		{
			semop(neparni, &sem_lock, 1);
			semop(mutexid, &sem_lock, 1);
			f = fopen(argv[1], "a");
			fprintf(f, "%d\n", i);
			fclose(f);
			semop(mutexid, &sem_unlock, 1);
			semop(parni, &sem_unlock, 1);
		}
	}

	wait(NULL);

	semctl(mutexid, 0, IPC_RMID, 0);
	semctl(parni, 0, IPC_RMID, 0);
	semctl(neparni, 0, IPC_RMID, 0);

	return 0;
}
