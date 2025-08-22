#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define SHMKEY 40010
#define MUTKEY 40011
#define MAXKEY 40012

#define M 10
#define N 6

union semun
{
	int val;
	struct semid_ds* *buf;
	ushort* array;
	struct seminfo* __buf;
	void* __pad;
};

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(1);
}

int main(int argc, char* argv[])
{
	int mutid, maxsem, shmid;
	union semun semopts;
	struct sembuf sem_lock = {0, -1, 0};
	struct sembuf sem_unlock = {0, 1, 0};
	int* matrix;

	// MUTEX MI NE TREBA AL ME MRZI DA GA BRISEM SAD radim u nano >:(

	mutid = semget(MUTKEY, 1, IPC_CREAT | 0666);
	maxsem = semget(MAXKEY, 1, IPC_CREAT | 0666);

	if(mutid == -1)
		exer("Mutex roditelj");
	if(maxsem == -1)
		exer("Prvi roditelj");

	semopts.val = 1;
	semctl(mutid, 0, SETVAL, semopts);
	semopts.val = 0;
	semctl(maxsem, 0, SETVAL, semopts);

	shmid = shmget(SHMKEY, sizeof(int)*M*N, IPC_CREAT | 0666);
	if(shmid == -1)
		exer("Shmem roditelj!");


	matrix = shmat(shmid, NULL, 0);


	if(fork() == 0) //DETE
	{
		semop(maxsem, &sem_unlock, 1);
		int max = -1;

		for(int i = 0; i < M; i++)
		{
			max = -1;

			for(int j = 0; j < N; j++)
			{
				max = max < matrix[i*M+j] ? matrix[i*M+j] : max;
				printf("%4d", matrix[i*M+j]);
			}
			printf(" [%4d]\n",max);
		} //Ovde iznad trazi max u vrstama

		for(int j = 0; j < N; j++)
		{
			max = -1;

			for(int i = 0; i < M; i++)
			{
				if(max < matrix[i*M + j])
					max = matrix[i*M + j];
			}
			printf("{%4d} ", max);
		}
		printf("\n");

	}
	else //RODITELJ
	{
		srand(time(NULL));

		for(int i = 0; i < M; i++)
		{
			for(int j = 0; j < N; j++)
			{
				matrix[i*M + j] = rand()%100;
			}
		}

		semop(maxsem, &sem_lock, 1);

		wait(NULL);

		semctl(maxsem, 0, IPC_RMID, 0);
		shmctl(shmid, IPC_RMID, 0);

	}


	return 0;
}
