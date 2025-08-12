#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>

#define MAXMSG 10
#define MQKEY 44444

struct mymsg {
    long type;
    int nums[MAXMSG];
};

int main(int argc, char* argv[])
{
    int mqID;
    struct mymsg msg;

    mqID = msgget(MQKEY, 0666 | IPC_CREAT);
    if (mqID < 0) {
        perror("msgget consumer");
        return 1;
    }

    ssize_t r = msgrcv(mqID, &msg, sizeof(msg.nums), 1, 0);
    if (r < -1) {
        perror("msgrcv failed");
        return 1;
    }

    printf("Consumer: msgrcv OK (received %zd bytes)\n", r);

    int i = 0;
    while (i < MAXMSG) {
        if (msg.nums[i] == -1) {
            printf("Consumer: found sentinel -1 at index %d\n", i);
            break;
        }
        printf("Consumer: nums[%d] = %d\n", i, msg.nums[i]);
        i++;
    }
    if (i == MAXMSG) {
        printf("Consumer: reached MAXMSG without seeing -1; stopping to avoid overflow\n");
    }

    return 0;
}
