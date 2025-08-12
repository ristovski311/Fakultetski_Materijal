#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

void obradiALARM(int a)
{
	printf("Vreme je isteklo...!\n");
	exit(-1);

}

int main(int argc, char argv[])
{
	char username[100];
	char pass[100];
	signal(SIGALRM, obradiALARM);

	printf("Unesite korisnicko ime: ");
	fgets(username, sizeof(username), stdin);

	printf("Imate 60 sekundi da unesete lozinku: ");

	alarm(60);

	fgets(pass, sizeof(pass), stdin);

	alarm(0);

	printf("Uspesno logovanje!\n");

	return 0;
}
