#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

const char* SHM_NAME = "./my_shm";

int main() {
	open(SHM_NAME, O_CREAT | O_EXCL | 0);
	key_t key = ftok(SHM_NAME, 1);
    int shm_id = shmget(key, 4096, IPC_CREAT | IPC_EXCL | 0666);
    if (shm_id == -1 && errno == EEXIST) {
        perror("Error: Program can't run twice.\n");
        return 1;
    }
    char *shared_memory = shmat(shm_id, NULL, 0);

    while (1) {
        time_t now = time(0);
        char *dt = ctime(&now);
        sprintf(shared_memory, "PID: %d, Time: %s", getpid(), dt);
        sleep(1);
    }
    shmdt(shared_memory);
    shmctl(shm_id, IPC_RMID, NULL);
    return 0;
}
