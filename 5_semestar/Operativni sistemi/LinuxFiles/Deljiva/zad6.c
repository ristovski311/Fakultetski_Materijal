#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define DETE 10101
#define RODITELJ 10102
#define SHMEM 10104

union semun
{
 int val;
 struct semid_ds *buf;
 ushort *array;
 struct seminfo * __buf;
 void * __pad;
};

int main(int argc, char* argv[])
{
	int deteId, roditeljId;
	int shmemid;
	char* shmem;
	FILE* f;

	union semun semopts;

	struct sembuf lock = {0, -1, 0};
	struct sembuf unlock = {0, 1, 0};

	if(argc < 2)
	{
		printf("Greska > Nedovoljno argumenata!\n");
		return -1;
	}

	deteId = semget(DETE, 1, 0666|IPC_CREAT);
	roditeljId = semget(RODITELJ, 1, 0666|IPC_CREAT);

	semopts.val = 1;
	semctl(roditeljId, 0, SETVAL, semopts);
	semopts.val = 0;
	semctl(deteId, 0, SETVAL, semopts);

	shmemid = shmget(SHMEM, 1024*sizeof(char), 0666|IPC_CREAT);

	if(fork() != 0)
	{
		//RODITELJ
		f = fopen(argv[1], "r");
		if(!f)
		{
			printf("Greska > Los file!");
			return -1;
		}

		shmem = (char*)shmat(shmemid, NULL, 0);

		while(1)
		{
			semop(roditeljId, &lock, 1);

			if(fgets(shmem, 1024*sizeof(char), f) == NULL)
			{
				strcpy(shmem, "KRAJ");
				semop(deteId, &unlock, 1);
				break;
			}
			semop(deteId, &unlock, 1);

		}
		fclose(f);
		wait(NULL);
		shmdt(shmem);
		semctl(roditeljId,0, IPC_RMID, 0);
		semctl(deteId,0, IPC_RMID, 0);
		shmctl(shmemid, IPC_RMID, 0);
	}
	else
	{
		//DETE
		shmemid = shmget(SHMEM, 1024*sizeof(char), 0666);

		shmem = (char*)shmat(shmemid, NULL ,0);

		while(1)
		{
			semop(deteId, &lock, 1);

			if(strcmp(shmem, "KRAJ") == 0)
			{
				shmdt(shmem);
				break;
			}

			printf("Dete > %s\n", shmem);

			semop(roditeljId, &unlock, 1);

		}

	}
	return 0;
}

