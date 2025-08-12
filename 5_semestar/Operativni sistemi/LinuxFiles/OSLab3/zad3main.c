#include "zad3.h"

int main(int argc, char* argv[])
{
	int mutexid, pozid, negid;
	int i, j, rand;

	union semun semopts;

	struct sembuf sem_lock = { 0, -1, NULL};
	struct sembuf sem_unlock = { 0, 1, NULL};

	mutexid = semget((key_t)MUTEXID,1,0666|IPC_CREAT);
	pozid = semget((key_t)POZID, 1, 0666|IPC_CREAT);
	negid = semget((key_t)NEGID, 1, 0666|IPC_CREAT);

	semopts.val = 1;
	semctl(mutexid, 0, SETVAL, semopts);

	semctl(pozid, 0, SETVAL, semopts);

	semopts.val = 0;
	semctl(negid, 0, SETVAL, semopts);

	if(fork() == 0)
	{
		//POZITIVNA GENERACIJA
		for(i = 0; i < 20; i++)
		{
			FILE* f = fopen("brojevi.dat", "a");
			semop(pozid, &sem_lock, 1);
			semop(mutexid, &sem_lock, 1);

			for(j = 0; j < 3; j++)
			{
				rand = random() % 100;
				fprintf(f, "%d\n", rand);
			}
			fclose(f);
			semop(mutexid, &sem_unlock, 1);
			semop(negid, &sem_unlock, 1);
		}
	}
	else
	{

		if(fork() == 0)
		{
			//NEGATIVNA GENERACIJA
			for(i = 0; i < 20; i++)
			{
				FILE* f = fopen("brojevi.dat", "a");
				semop(negid, &sem_lock, 1);
				semop(mutexid, &sem_lock, 1);

				for(j = 0; j < 2; j++)
				{
					rand = random() % 100;
					rand *= -1;
					fprintf(f, "%d\n", rand);
				}
				fclose(f);
				semop(mutexid, &sem_unlock, 1);
				semop(pozid, &sem_unlock, 1);
			}
		}
		else
		{
			//PARENT PROCES

			wait(NULL);
			wait(NULL);

			semctl(mutexid, 0, IPC_RMID, 0);
			semctl(pozid, 0, IPC_RMID, 0);
			semctl(negid, 0, IPC_RMID, 0);
		}
	}

	return 0;
}
