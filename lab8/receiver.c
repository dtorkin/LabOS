#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>

const char* SEM_NAME = "./my_sem";

int main() {
    key_t key = ftok(SEM_NAME, 1);
    int sem_id = semget(key, 1, 0666);
    if (sem_id == -1) {
        perror("Error: Semaphore cannot be opened.\n");
        return 1;
    }

    while (1) {
        time_t now = time(0);
        char *dt = ctime(&now);
        printf("PID: %d, Time: %s", getpid(), dt);
        sleep(1);
    }

    return 0;
}
