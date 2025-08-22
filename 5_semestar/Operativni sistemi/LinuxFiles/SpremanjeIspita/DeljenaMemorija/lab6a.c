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
#include <signal.h>

#define SHMKEY 40030
#define KEY1 40031
#define KEY2 40032
#define MAXBUF 256

void exer(const char* msg)
{
	printf("\nGRESKA\n%s\n", msg);
	exit(-1);
}

int noMore = 0;

void obradiSIGUSR1(int sid)
{
	noMore = 1;
}

int main(int argc, char* argv[])
{
	int shmid, sem1, sem2;
	char* shmptr;
	char buffer[MAXBUF];

	printf("dete pokrenuto\n");
	fflush(stdout);
	if(argc < 2) exer("Niste uneli dovoljno argumenata proc 2");

	printf("dete: %s\n",argv[1]);

	signal(SIGUSR1, obradiSIGUSR1);

	struct sembuf sem_wait = {0,-1,0};
	struct sembuf sem_signal = {0,1,0};

	sem1 = semget(KEY1, 1, IPC_CREAT | 0666);
	sem2 = semget(KEY2, 1, IPC_CREAT | 0666);

	if(sem1 == -1) exer("Sem1 proc 2");
	if(sem2 == -1) exer("Sem2 proc 2");

	shmid = shmget(SHMKEY, sizeof(char) * MAXBUF, IPC_CREAT | 0666);
	if(shmid == -1) exer("Proc 2 shared mem");


	shmptr = shmat(shmid, NULL, 0);
	int f = open(argv[1], O_WRONLY | O_CREAT, 0777);
	printf("Drugi proc: %s\n", argv[1]);
	if(f == -1) exer("Proc 2 greska pri otvaranju druge datoteke!");

	while(1)
	{

		semop(sem2, &sem_wait, 1);

		memcpy(buffer, shmptr, MAXBUF);

		if(write(f, buffer, MAXBUF) == -1) exer("Greska upisa drugog procesa!");

		semop(sem1, &sem_signal, 1);

		if(noMore)
			break;
	}

	close(f);

	return 0;
}
