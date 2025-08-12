#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PRVIS 10001
#define DRUGIS 10002
#define TRECIS 10003
#define SHMEM 10004
#define FLAGS 10005

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
	int memid;
	int flagsid;
	int prviId, drugiId, treciId;
	FILE* f;
	char* shmem;
	int* shflags;

	union semun semopts;
	struct sembuf lock = {0,-1,NULL};
	struct sembuf unlock = {0,1,NULL};

	flagsid = shmget(FLAGS, 2*sizeof(int), 0666|IPC_CREAT);
	memid = shmget(SHMEM, 1024, 0666|IPC_CREAT);
	prviId = semget(PRVIS, 1, 0666|IPC_CREAT);
        drugiId = semget(DRUGIS, 1, 0666|IPC_CREAT);
        treciId = semget(TRECIS, 1, 0666|IPC_CREAT);

	semopts.val = 1;
	semctl(prviId,0, SETVAL, semopts);
	semopts.val = 0;
	semctl(drugiId, 0, SETVAL, semopts);
	semctl(treciId,0, SETVAL, semopts);

	if(fork() == 0)
	{
		//DETE 1
		shmem = (char*)shmat(memid, NULL, 0);
		shflags = (int*)shmat(flagsid, NULL, 0);

		f = fopen("ulaz1.txt", "r");
		if(!f)
		{
			printf("Greska sa ulaz1\n");
			return -1;
		}

		while(1)
		{
			semop(prviId, &lock,1);

			if(fgets(shmem, 1024, f) == NULL)
			{

				shflags[0] = 1;
				semop(treciId, &unlock, 1);

				if(shflags[1] == 1)
				{
					semop(drugiId, &unlock, 1);
					break;
				}
				continue;
			}

			semop(drugiId, &unlock, 1);
		}
		fclose(f);
		return 0;

	}
	else
	{
		//Roditelj

		if(fork() == 0)
		{
			//DETE 2
			shmem = (char*)shmat(memid, NULL, 0);
			shflags = (int*)shmat(flagsid, NULL, 0);

			shflags[0] = 0;
			shflags[1] = 0;

        	        f = fopen("ulaz2.txt", "r");
               		if(!f)
	                {
        	                printf("Greska sa ulaz2\n");
                	        return -1;
                	}

                	while(1)
                	{
                        	semop(treciId, &lock,1);

                      	  	if(fgets(shmem, 1024, f) == NULL)
                        	{
					shflags[1] = 1;
                                	semop(prviId, &unlock, 1);
                                	if(shflags[0] == 1)
					{
						semop(drugiId, &unlock, 1);
						break;
					}
					continue;
                        	}

                        	semop(drugiId, &unlock, 1);
                	}
			fclose(f);
                	return 0;
		}
		else
		{
			//RODITELJ
			shmem = (char*)shmat(memid, NULL, 0);
			shflags = (int*)shmat(flagsid, NULL, 0);
                        f = fopen("izlaz.txt", "w");
                        if(!f)
                        {
                                printf("Greska sa izlaz\n");
                                return -1;
                        }

			int i = 0;
                        while(1)
                        {

				semop(drugiId, &lock, 1);

				if(shflags[0] == 1 && shflags[1] == 1)
				{
					break;
				}
				fprintf(f,"%d. %s\n", i+1, shmem);

				if(i % 2 == 0)
				{
					semop(treciId, &unlock,1);
				}
				else
				{
					semop(prviId, &unlock, 1);
				}
				i++;
			}
                        fclose(f);

			semctl(prviId, 0, IPC_RMID, 0);
			semctl(drugiId, 0, IPC_RMID, 0);
			semctl(treciId, 0, IPC_RMID, 0);
			shmctl(memid,IPC_RMID, 0);
			shmctl(flagsid, IPC_RMID, 0);

                        return 0;
		}

	}

	return 0;
}


