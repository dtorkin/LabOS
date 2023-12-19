#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

const char* SEM_NAME = "./my_sem";

int main() {
    key_t key = ftok(SEM_NAME, 1);
    int sem_id = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (sem_id == -1 && errno == EEXIST) {
        perror("Error: Program can't run twice.\n");
        return 1;
    }

    while (1) {
        time_t now = time(0);
        char *dt = ctime(&now);
        printf("PID: %d, Time: %s", getpid(), dt);
        sleep(1);
    }

    semctl(sem_id, 0, IPC_RMID);
    return 0;
}
