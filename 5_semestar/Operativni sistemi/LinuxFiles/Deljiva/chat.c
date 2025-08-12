#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_KEY 10003
#define SEM_PARENT 10001
#define SEM_CHILD  10002
#define SHM_SIZE 1024

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int main(int argc, char* argv[]) {
    int shmid, sem_parent, sem_child;
    char *shmem;
    FILE *file;
    union semun semopts;

    struct sembuf lock = {0, -1, 0};  // Wait operation
    struct sembuf unlock = {0, 1, 0}; // Signal operation

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create shared memory
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Create semaphores
    sem_parent = semget(SEM_PARENT, 1, 0666 | IPC_CREAT);
    sem_child = semget(SEM_CHILD, 1, 0666 | IPC_CREAT);
    if (sem_parent == -1 || sem_child == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores
    semopts.val = 1;  // Parent starts first
    semctl(sem_parent, 0, SETVAL, semopts);
    semopts.val = 0;  // Child waits
    semctl(sem_child, 0, SETVAL, semopts);

    if (fork() != 0) {
        // Parent Process
        file = fopen(argv[1], "r");
        if (!file) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        shmem = (char*)shmat(shmid, NULL, 0);
        if (shmem == (void*)-1) {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        while (fgets(shmem, SHM_SIZE, file)) {
            // Signal child to read
            semop(sem_child, &unlock, 1);
            // Wait for child to finish
            semop(sem_parent, &lock, 1);
        }

        // Send termination signal
        strcpy(shmem, "KRAJ");
        semop(sem_child, &unlock, 1);

        // Cleanup
        wait(NULL);
        fclose(file);
        shmdt(shmem);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(sem_parent, 0, IPC_RMID, 0);
        semctl(sem_child, 0, IPC_RMID, 0);
    } else {
        // Child Process
        shmem = (char*)shmat(shmid, NULL, 0);
        if (shmem == (void*)-1) {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        while (1) {
            // Wait for parent signal
            semop(sem_child, &lock, 1);
            if (strcmp(shmem, "KRAJ") == 0) {
                break;
            }
            printf("Child > %s", shmem);
            // Signal parent to continue
            semop(sem_parent, &unlock, 1);
        }

        shmdt(shmem);
    }
    return 0;
}
