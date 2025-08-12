#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

int pid;
int counter = 0;

void obradiUSR2(int sig_num)
{

	printf("Procesu 1 je primio signal SIGUSR2\n");
	int i;
	counter++;

	if(counter <= 4095)
		signal(SIGUSR2, obradiUSR2);
	else
	{
		kill(pid, SIGUSR1);
		printf("Program 1 je gotov!\n");
		exit(-1);
	}

	FILE* f = fopen("prenos.dat", "w");

        if(!f)
        {
                printf("File nije uspesno otvoren!");
                exit(-1);
        }

        srand(time(NULL));

        for(i = 0; i < 1024; i++)
        {
                int rand = random()%100;
                fprintf(f,"%d\n",rand);

        }

	fprintf(f,"Serija: %d\n", counter);

        fclose(f);

	printf("Proces 1 salje signal SIGUSR1 procesu sa pid: %d\n", pid);

        kill(pid, SIGUSR1);

}


int main(int argc, char* argv[])
{
	pid = fork();
	if(pid == 0)
	{
		char input[100];
		sprintf(input, "%d", getppid());
		execl("./zad3b", "zad3b", input ,NULL);
		printf("Greska pri pokretanju procesa 2!");
		return -1;
	}
	else
	{
		int i;
		signal(SIGUSR2, obradiUSR2);
		FILE* f = fopen("prenos.dat", "w");

		if(!f)
		{
			printf("File nije uspesno otvoren!");
			return -1;
		}

		srand(time(NULL));

		for(i = 0; i < 1024; i++)
		{
			int rand = random()%100;
			fprintf(f,"%d\n",rand);

		}

		fclose(f);

		sleep(3);
		printf("Saljem signal SIGUSR1 iz programa1\n");
		kill(pid,SIGUSR1);

		printf("Pid procesa 1 je %d\n", getpid());

		while(1)
			pause();

	}

	return 0;
}
