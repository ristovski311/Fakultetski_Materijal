#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define SHMKEY 40020
#define PROC1KEY 40021
#define PROC2KEY 40022
#define MAXBUF 256

union semun
{
	int val;
	struct semid_ds* buf;
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
	int shmid, proc1id, proc2id;
	char buf[MAXBUF];
	char* shmptr;

	union semun semopts;

	struct sembuf sem_wait = {0,-1,0};
	struct sembuf sem_signal = {0,1,0};

	proc1id = semget(PROC1KEY, 1, IPC_CREAT | 0666);
	proc2id = semget(PROC2KEY, 1, IPC_CREAT | 0666);

	if(proc1id == -1) exer("proc 1 sem!");
	if(proc2id == -2) exer("proc 2 sem!");

	semopts.val = 1;
	semctl(proc1id, 0, SETVAL, semopts);
	semopts.val = 0;
	semctl(proc2id, 0, SETVAL, semopts);

	if(fork() == 0) //DETE
	{
		shmid = shmget(SHMKEY, sizeof(char) * MAXBUF, IPC_CREAT | 0666);
		if(shmid == -1) exer("Dete shm!");
		shmptr = (char*)shmat(shmid, NULL, 0);

		FILE* f;

		while(1)
		{
			semop(proc2id, &sem_wait, 1);

			if(strcmp(shmptr, "KRAJ")==0)
				break;

			f = fopen("stringovi.txt", "a");

			if(f == 0) exer("Fajl");

			fprintf(f, "%s\n", shmptr);

			semop(proc1id, &sem_signal, 1);

			fclose(f);
		}

		shmdt(shmptr);

	}
	else //RODITELJ
	{
		shmid = shmget(SHMKEY, sizeof(char) * MAXBUF, IPC_CREAT | 0666);
		if(shmid == -1) exer("Roditelj shm!");
		shmptr = (char*)shmat(shmid, NULL, 0);

		while(strcmp(buf, "KRAJ") != 0)
		{
			printf("Unesite poruku: ");
			gets(buf);

			semop(proc1id,&sem_wait, 1);

			memcpy(shmptr, buf, strlen(buf)+1);

			semop(proc2id,&sem_signal, 1);
		}

		wait(NULL);
		shmdt(shmptr);
		semctl(proc1id,0, IPC_RMID, 0);
		semctl(proc2id,0, IPC_RMID, 0);
		shmctl(shmid, IPC_RMID, 0);
	}

	return 0;
}
