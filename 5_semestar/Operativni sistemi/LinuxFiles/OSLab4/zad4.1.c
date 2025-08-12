#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 100

int main(int argc, char* argv[])
{
    FILE* fi;
    FILE* fo;
    int pd[2];
    char buff[BUFSIZE];

    // Check for the correct number of arguments
    if (argc < 3)
    {
        fprintf(stderr, "Nedovoljno argumenata!\n");
        return -1;
    }

    // Open input and output files
    fi = fopen(argv[1], "r");
    if (fi == NULL)
    {
        fprintf(stderr, "Greska pri otvaranju ulazne datoteke!\n");
        return -1;
    }

    fo = fopen(argv[2], "w");
    if (fo == NULL)
    {
        fclose(fi);
        fprintf(stderr, "Greska pri otvaranju izlazne datoteke!\n");
        return -1;
    }

    // Prevent using the same file for input and output
    if (strcmp(argv[1], argv[2]) == 0)
    {
        fclose(fi);
        fclose(fo);
        fprintf(stderr, "Ne sme se koristiti izvorisna za odredisnu datoteku!\n");
        return -1;
    }

    // Create a pipe
    if (pipe(pd) < 0)
    {
        fclose(fi);
        fclose(fo);
        fprintf(stderr, "Greska pri otvaranju datavoda!\n");
        return -1;
    }

    if (fork() != 0)  // Parent process
    {
        close(pd[0]);  // Close unused read end of the pipe

        // Read lines from the input file and write to the pipe
        while (fgets(buff, BUFSIZE-1, fi) != NULL)
        {

	size_t len = strlen(buff);
	buff[len] = '\0';
	if (write(pd[1], buff, len+1) != len+1)  // Write the exact length of the string
            {
                fprintf(stderr, "Greska pri pisanju u datavod!\n");
                break;
            }
        }

        fclose(fi);
        close(pd[1]);  // Close write end of the pipe
        wait(NULL);    // Wait for the child to finish
    }
    else  // Child process
    {
        close(pd[1]);  // Close unused write end of the pipe

        // Read from the pipe and write lines to the output file
        ssize_t bytes_read;
        while ((bytes_read = read(pd[0], buff, BUFSIZE)) > 0)
        {
            //buff[bytes_read] = '\0';  // Ensure null termination
            fprintf(fo, "%s", buff);  // Write the data to the output file
        }

        fclose(fo);
        close(pd[0]);  // Close read end of the pipe
        exit(0);       // Exit child process
    }

    return 0;
}
