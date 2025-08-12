#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

void* uradiNit(void *arg)
{
    char putanja[300] = "https://infosys1.elfak.ni.ac.rs/svn/studenti/informacioni sistemi/studentski radovi 2024 - laboratorijske vezbe/";
    char dir[100];
    strcpy(dir, (char *)arg);
    //printf("Ispisujem %s\n", dir);
    // Remove newline from dir if present
    dir[strcspn(dir, "\n")] = 0;
    strcat(putanja, dir);

    if (fork() == 0)
    {
	//printf("Ispisujem %s\n",dir);
        execlp("./scriptList.sh", "scriptList.sh", putanja, dir, NULL);
        perror("Error executing scriptList.sh");
        exit(-1);
    }
    else
    {
        wait(NULL);
    }
}

int main(int argc, char* argv[])
{
    pthread_t niti[200];
    FILE* f;
    int i = 0;
    char dir[200];

    f = fopen("./direktorijumi.txt", "r");
    if (f == NULL) {
        perror("Error opening file");
        return -1;
    }

    while (fgets(dir, sizeof(dir), f) != NULL)
    {
        pthread_create(&niti[i++], NULL, uradiNit, strdup(dir));
	pthread_join(niti[i-1], NULL);
    }

    fclose(f);
    return 0;
}
