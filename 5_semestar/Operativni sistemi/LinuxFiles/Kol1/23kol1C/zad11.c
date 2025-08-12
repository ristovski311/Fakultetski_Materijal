#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>

char buff[2048];

sem_t glavna;
sem_t nit1;
sem_t nit2;

void* nit1Fja(void* arg) {
    int len;

    while (1) {
        sem_wait(&nit1); // Wait for main thread to signal
        //printf("[Thread 1] Received input: %s\n", buff);

        if (strcmp(buff, "KRAJ") == 0) {
            sem_post(&nit2); // Signal nit2 to terminate
            break;
        }

        len = strlen(buff);
        if (buff[len - 1] != '.') {
            buff[len] = '.';
            buff[len + 1] = '\0';
        }

        buff[0] = toupper(buff[0]);
        //printf("[Thread 1] Modified input: %s\n", buff);

        sem_post(&nit2); // Signal nit2
    }

    pthread_exit(0);
}

void* nit2Fja(void* arg) {
    char* ch;

    while (1) {
        sem_wait(&nit2); // Wait for Thread 1 to signal
        //printf("[Thread 2] Received input: %s\n", buff);

        if (strcmp(buff, "KRAJ") == 0) {
            sem_post(&glavna); // Signal main thread to terminate
            break;
        }

        // Replace spaces with underscores
        while ((ch = strchr(buff, ' ')) != NULL) {
            *ch = '_';
        }

        printf("[Thread 2] Modified input: %s\n", buff);

        sem_post(&glavna); // Signal main thread
    }

    pthread_exit(0);
}

int main() {
    pthread_t nit1n;
    pthread_t nit2n;

    // Create threads
    pthread_create(&nit1n, NULL, nit1Fja, NULL);
    pthread_create(&nit2n, NULL, nit2Fja, NULL);

    // Initialize semaphores
    sem_init(&glavna, 0, 1);
    sem_init(&nit1, 0, 0);
    sem_init(&nit2, 0, 0);

    while (1) {
        sem_wait(&glavna); // Wait for Thread 2 to signal

        printf("[Main] Enter a sentence (or 'KRAJ' to quit): ");
        fgets(buff, sizeof(buff) - 1, stdin);
        buff[strcspn(buff, "\n")] = '\0'; // Remove newline character

        sem_post(&nit1); // Signal Thread 1

        if (strcmp(buff, "KRAJ") == 0) {
            break;
        }
    }

    pthread_join(nit1n, NULL);
    pthread_join(nit2n, NULL);

    sem_destroy(&glavna);
    sem_destroy(&nit1);
    sem_destroy(&nit2);

    return 0;
}
