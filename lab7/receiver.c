#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

const char* SHM_NAME = "./my_shm";

int main() {
    open(SHM_NAME, O_CREAT | O_EXCL | 0);
    key_t key = ftok(SHM_NAME, 1);
    int shm_id = shmget(key, 4096, 0666);
    if (shm_id == -1) {
        perror("Error: Shared memory cannot be opened.\n");
        return 1;
    }
    char *shared_memory = shmat(shm_id, NULL, 0);

    while (1) {
        time_t now = time(0);
        char *dt = ctime(&now);
        printf("PID: %d, Time: %s", getpid(), dt);
        printf("Received via shared memory: %s\n", shared_memory);
        sleep(1);
    }

    return 0;
}
