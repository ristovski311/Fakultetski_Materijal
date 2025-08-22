#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void obradiAlarm(int sid)
{

	printf("Niste uneli lozinku na vreme!\n");
	exit(1);

}


int main(int argc, char* argv[])
{
	signal(SIGALRM, obradiAlarm);

	char username[100];
	char pass[100];

	printf("Username: ");
	gets(username);

	printf("[You have 10 seconds]\n");
	alarm(10);
	gets(pass);

	alarm(0);

	printf("\nUSERNAME: %s\nPASSWORD: %s\n", username, pass);
	return 0;
}
