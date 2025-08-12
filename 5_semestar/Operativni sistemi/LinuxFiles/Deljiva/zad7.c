#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define DETE 10101
#define RODITELJ 10102
#define SHMEM 10103

union semun
{
 int val;
 struct semid_ds *buf;
 ushort *array;
 struct seminfo * __buf;
 void * __pad;
};

int main()
{
	int deteId, roditeljId, shmemid;
	int* shmem;
	char* input;

	union semun semopts;
	struct sembuf lock = {0, -1, 0};
	struct sembuf unlock = {0, 1, 0};

	deteId= semget(DETE, 1, IPC_CREAT|0666);
	roditeljId = semget(RODITELJ, 1, 0666|IPC_CREAT);

	semopts.val = 1;
	semctl(roditeljId, 0, SETVAL, semopts);
	semopts.val = 0;
	semctl(deteId, 0, SETVAL, semopts);

	shmemid = shmget(SHMEM, 2*sizeof(int), 0666|IPC_CREAT);

	if(fork() != 0)
	{
		//RODITELJ
		shmem = shmat(shmemid, NULL, 0);
		while(1)
		{
			semop(roditeljId, &lock, 1);

			printf("Unesite broj [KRAJ za prekid programa] > ");
			scanf("%s", input);

			if(strcmp(input, "KRAJ") == 0)
			{
				//Ako se unesu u shared memory dva broja -1, onda je kraj i na taj
				//nacin signaliziramo detetu da je kraj!

				shmem[0] = -1;
				shmem[1] = -1;

				semop(deteId, &unlock, 1);

				break;

			}

			shmem[0] = atoi(input);
			shmem[1] = shmem[0] * 3;

			printf("Roditelj je upisao: %d | %d\n", shmem[0], shmem[1]);

			semop(deteId, &unlock, 1);

		}
		wait(NULL);
		shmdt(shmem);
		semctl(roditeljId, 0, IPC_RMID, 0);
		semctl(deteId, 0, IPC_RMID, 0);
		shmctl(shmemid, IPC_RMID, 0);
	}
	else
	{
		//DETE
		shmem = shmat(shmemid, NULL, 0);

		while(1)
		{
			semop(deteId, &lock, 1);

			if(shmem[0] == -1 && shmem[1] == -1)
			{
				shmdt(shmem);
				break;
			}

			printf("Dete stampa > %d | %d\n", shmem[0], shmem[1]);


			semop(roditeljId, &unlock, 1);

		}


	}

	return 0;
}
