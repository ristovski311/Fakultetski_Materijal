//sl7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int ctrC = 0;
int ctrZ = 0;

void obradiINT(int sig_num)
{
	char t[10];
	ctrZ = 0;
	signal(SIGINT, obradiINT);
	ctrC++;
	if(ctrC == 5)
	{
		printf("Sigurno zelite da zatvorite? [y/n]\n");
		scanf("%s",t);
		if(t[0] == 'y')
			exit(0);
		else
		{
			ctrC = 0;
			printf("Odustajem...\n");
		}
	}
}

void obradiTSTP(int sig_num)
{
	signal(SIGTSTP,obradiTSTP);
	ctrZ++;
	if(ctrZ == 2)
	{
		printf("Do sada je CTRL+C pritisnuto: %d puta!\n",ctrC);
		ctrZ =0 ;
	}


}

int main(int argc, char* argv[])
{
	signal(SIGINT, obradiINT);
	signal(SIGTSTP, obradiTSTP);

	while(1)
		pause();
	return 0;

}
