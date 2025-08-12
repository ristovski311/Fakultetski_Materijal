#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>

#define MQKEY 44444
#define MAXMSG 10

struct mymsg {
    long type;
    int nums[MAXMSG];
};

int main(int argc, char* argv[])
{
    int mqID;
    struct mymsg msg;
    int numSize;

    if(fork() == 0)
    {
        // child -> exec consumer
        if (execl("./lab5consumer", "lab5consumer", NULL) < 0) {
            perror("execl ./lab5consumer failed");
        }
        _exit(1);
    }
    else
    {
        // parent -> producer
        mqID = msgget(MQKEY, 0666 | IPC_CREAT);
        if (mqID < 0) {
            perror("msgget producer");
            return 1;
        }
        srand((unsigned)time(NULL) ^ getpid());

        numSize = rand() % MAXMSG;   // number of random numbers (0..MAXMSG-1)
        if (numSize < 0) numSize = 0;

        printf("Producer: numSize=%d\n", numSize);

        for (int i = 0; i < numSize; ++i) {
            msg.nums[i] = rand() % 10;
            printf("Producer: nums[%d]=%d\n", i, msg.nums[i]);
        }
        // sentinel
        if (numSize < MAXMSG)
            msg.nums[numSize] = -1;
        else
            msg.nums[MAXMSG-1] = -1; // safety (shouldn't happen with current numSize)

        msg.type = 1;

        if (msgsnd(mqID, &msg, sizeof(msg.nums), 0) == -1) {
            perror("msgsnd failed");
        } else {
            printf("Producer: msgsnd OK (sent %zu bytes)\n", sizeof(msg.nums));
        }

        wait(NULL); // wait for child
        if (msgctl(mqID, IPC_RMID, NULL) == -1)
            perror("msgctl IPC_RMID");
    }
    return 0;
}
