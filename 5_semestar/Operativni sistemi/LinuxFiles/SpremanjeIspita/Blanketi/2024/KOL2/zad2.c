#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHMKEY 40004
#define SEMDKEY 40005
#define SEMRKEY 40006

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(1);
};

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
	int pid;
	int shmid;
	int* shmptr;

	shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0666);
	if(shmid == -1) exer("Greska shmid -1");

	shmptr = (int*)shmat(shmid, NULL, 0);

	for(int i = 0; i < 10; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			shmid = shmget(SHMKEY, sizeof(int), 0666);
			if(shmid == -1) exer("Greska shmid -1 dete");

			shmptr = (int*)shmat(shmid, NULL, 0);

			*shmptr = getpid();

			shmdt(shmptr);

			return 0;
		}
		else
		{
			wait(NULL);

			printf("MOJ [%d] | DETETOV [%d]\n", getpid(), *shmptr);

			if(*shmptr != getpid() + 1)
			{
				printf("Nije veci za 1!\n");
			}
			else
			{
				printf("JESTE veci za 1!\n");
			}

		}

	}

	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, 0);

	return 0;
}
