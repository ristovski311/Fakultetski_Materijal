#include <stdio.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SHMKEY 40004
#define SEM1KEY 40005
#define SEM2KEY 40006
#define SEMPRODUCEKEY 40007
#define SEMCONSUMEKEY 40008
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
	int shmid, sem1, sem2, semconsume, semproduce;
	union semun semopts;
	char* shmptr;
	FILE* f;

	struct sembuf sem_wait = {0,-1,0};
	struct sembuf sem_signal = {0,1,0};

	sem1 = semget(SEM1KEY, 1, IPC_CREAT | 0666);
	sem2 = semget(SEM2KEY, 1, IPC_CREAT | 0666);
	semconsume = semget(SEMCONSUMEKEY, 1, IPC_CREAT | 0666);
	semproduce = semget(SEMPRODUCEKEY, 1, IPC_CREAT | 0666);

	if(sem1 == -1) exer("Greska kod kreiranja sem1");
	if(sem2 == -1) exer("Greska kod kreiranja sem2");
	if(semconsume == -1) exer("Greska kod kreiranja consume");
	if(semproduce == -1) exer("Greska kod kreiranja sem produce");

	semopts.val = 1;
	semctl(sem1,0, SETVAL, semopts);
	semctl(semproduce,0, SETVAL, semopts);
	semopts.val = 0;
	semctl(sem2,0, SETVAL, semopts);
	semctl(semconsume,0, SETVAL, semopts);

	shmid = shmget(SHMKEY, sizeof(char) * MAXBUF, IPC_CREAT | 0666);
	if(shmid == -1) exer("Greska pri kreiranju deljive memorije!");

	if(fork() == 0) //DETE 1
	{


		shmid = shmget(SHMKEY, sizeof(char) * MAXBUF, IPC_CREAT | 0666);
		if(shmid == -1) exer("Dete 1 - Greska pri kreiranju deljive memorije!");

		shmptr = (char*)shmat(shmid, NULL, 0);

		char buffer[MAXBUF];

		f = fopen("ulaz1.txt", "r");

		while(fgets(buffer, sizeof(buffer), f) != NULL)
		{
			semop(sem1, &sem_wait, 1);
			semop(semproduce, &sem_wait, 1);

			strcpy(shmptr, buffer);

			semop(semconsume, &sem_signal, 1);
			semop(sem2, &sem_signal, 1);
		}

		semop(sem1, &sem_wait, 1);
		semop(semproduce, &sem_wait, 1);

		strcpy(shmptr, "KRAJ1");

		semop(semconsume, &sem_signal, 1);
		semop(sem2, &sem_signal, 1);


		shmdt(shmptr);


	}
	else if(fork() == 0) //DETE 2
	{

		shmid = shmget(SHMKEY, sizeof(char) * MAXBUF, IPC_CREAT | 0666);
		if(shmid == -1) exer("Dete 2 - Greska pri kreiranju deljive memorije!");

		shmptr = (char*)shmat(shmid, NULL, 0);

		char buffer[MAXBUF];

		f = fopen("ulaz2.txt", "r");

		while(fgets(buffer, sizeof(buffer), f) != NULL)
		{
			semop(sem2, &sem_wait, 1);
			semop(semproduce, &sem_wait, 1);

			strcpy(shmptr, buffer);

			semop(semconsume, &sem_signal, 1);
			semop(sem1, &sem_signal, 1);
		}

		semop(sem2, &sem_wait, 1);
		semop(semproduce, &sem_wait, 1);

		strcpy(shmptr, "KRAJ2");

		semop(semconsume, &sem_signal, 1);
		semop(sem1, &sem_signal, 1);


		shmdt(shmptr);

	}
	else //RODITELJ
	{

		shmptr = (char*)shmat(shmid, NULL, 0);

		int prviGotov = 0;
		int drugiGotov = 0;

		char buffer[MAXBUF];

		while(!prviGotov || !drugiGotov)
		{
			f = fopen("izlaz.txt", "a");

			semop(semconsume, &sem_wait, 1);

			strcpy(buffer, shmptr);

			if(strcmp(buffer, "KRAJ1") == 0)
			{
				prviGotov = 1;
				semop(semproduce, &sem_signal, 1);
				continue;
			}
			else if(strcmp(buffer, "KRAJ2") == 0)
			{
				drugiGotov = 1;
				semop(semproduce, &sem_signal, 1);
				continue;
			}

			fprintf(f, "%s", buffer);

			if(prviGotov == 1)
				semop(sem2, &sem_signal, 1);

			if(drugiGotov == 1)
				semop(sem1, &sem_signal, 1);

			semop(semproduce, &sem_signal, 1);

			fclose(f);

		}

		shmdt(shmptr);

		shmctl(shmid, IPC_RMID, NULL);
		semctl(sem1, 0, IPC_RMID, NULL);
		semctl(sem2, 0, IPC_RMID, NULL);
		semctl(semproduce, 0, IPC_RMID, NULL);
		semctl(semconsume, 0, IPC_RMID, NULL);

	}


	return 0;
}
