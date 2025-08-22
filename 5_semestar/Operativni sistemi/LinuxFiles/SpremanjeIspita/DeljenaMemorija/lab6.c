#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define SHMKEY 40030
#define KEY1 40031
#define KEY2 40032
#define MAXBUF 256

union semun
{
	int val;
	struct semid_ds* buf;
	ushort* array;
	struct seminfo* __buf;
	void* __paid;
};

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(-1);
}

int main(int argc, char* argv[])
{
	int shmid, sem1, sem2;
	union semun semopts;
	char* shmptr;
	int pid;

	if(argc < 3) exer("Niste uneli dovoljno argumenata!\nPrvi je file koji se kopira, drugi onaj u koji se kopira!\n");

	struct sembuf sem_wait = {0,-1,0};
	struct sembuf sem_signal = {0,1,0};

	sem1 = semget(KEY1, 1, IPC_CREAT | 0666);
	sem2 = semget(KEY2, 1, IPC_CREAT | 0666);

	if(sem1 == -1) exer("Sem1 proc 1");
	if(sem2 == -1) exer("Sem2 proc 1");

	semopts.val = 1;
	semctl(sem1, 0, SETVAL, semopts.val);
	semopts.val = 0;
	semctl(sem2, 0, SETVAL, semopts.val);

	shmid = shmget(SHMKEY, sizeof(char) * MAXBUF, IPC_CREAT | 0666);
	if(shmid == -1) exer("Proc 1 shared mem");


	printf("roditelj: %s\n", argv[2]);

	pid = fork();

	if(pid == -1)
		exer("fork ne radi");

	printf("MOJ PID = %d\n", pid);

	if(pid == 0) //PROCES 2
	{
		printf("pokusacu da kreiram proces a");
		fflush(stdout);
		execl("./lab6a", "lab6a", argv[2] ,NULL);
		exer("Greska pri pokretanju procesa 2");
	}
	else
	{
		printf("a ovo je l radi");
		shmptr = shmat(shmid, NULL, 0);
		char buffer[MAXBUF];
		int f = open(argv[1], O_RDONLY, 0777);
		if(f == -1) exer("Proc 1 greska pri otvaranju prve datoteke!");

		int bread;

		while((bread = read(f, buffer, sizeof(char) * MAXBUF))> 0)
		{
			semop(sem1, &sem_wait, 1);

			memcpy(shmptr, buffer, bread);

			semop(sem2, &sem_signal, 1);
		}

		kill(pid, SIGUSR1);

		close(f);

		shmdt(shmptr);
		wait(NULL);
		shmctl(shmid, IPC_RMID, 0);
		semctl(sem1, 0, IPC_RMID, 0);
		semctl(sem2, 0, IPC_RMID, 0);
	}

	return 0;
}
