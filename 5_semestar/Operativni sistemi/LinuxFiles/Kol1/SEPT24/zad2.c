#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define BUF 1000

int main(int argc, char* argv[])
{
	FILE* f;
	char buff[BUF];
	char kopija[BUF];
	int pd[2];
	int offset = 0;
	int i;
	int k;

	if(argc < 2)
	{
		printf("Nedovoljno parametara!\n");
		return -1;
	}

	if(pipe(pd) == -1)
	{
		printf("Greska pipe\n");
		return -1;
	}

	if(fork() != 0)
	{
		close(pd[0]);

		f = fopen(argv[1], "rb");
		if(!f)
		{
			printf("Datoteka losa\n");
			return -1;
		}

		while(fread(buff,sizeof(char),sizeof(buff),f) > 0)
		{
			write(pd[1], &offset, sizeof(int));
			write(pd[1], buff, BUF);
			offset += 1000;
		}
		close(pd[1]);
		fclose(f);
		wait(NULL);
	}
	else
	{
		close(pd[1]);
		f = fopen(argv[2],"wb");
		if(!f)
		{
			printf("datoteka deteta greska\n");
			return -1;
		}
		while(read(pd[0], &offset, sizeof(int)) > 0)
		{
			k = read(pd[0], buff, BUF);
			printf("of = %d | k = %d",offset,k);
			for(i = offset; i< offset+k; i++)
			{
				kopija[i] = buff[i] ^ i;
			}

			fwrite(kopija,sizeof(char),k,f);
			fwrite(buff,sizeof(char),k,f);

		}
		close(pd[0]);
		fclose(f);
	}


	return 0;
}
