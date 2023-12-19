#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <ctime>
#include <sstream>

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if (pid > 0) {
        close(fd[0]);
        time_t now = time(0);
        char* dt = ctime(&now);
        std::ostringstream ss;
        ss << "PID: " << getpid() << ", Time: " << dt;
        std::string s = ss.str();
        write(fd[1], s.c_str(), s.size() + 1);
        close(fd[1]);
        wait(NULL);
    } else if (pid == 0) {
        close(fd[1]);
        sleep(5);
        char buffer[4096];
        read(fd[0], buffer, sizeof(buffer));
        time_t now = time(0);
        char* dt = ctime(&now);
        std::cout << "PID: " << getpid() << ", Time: " << dt;
        std::cout << "Received via pipe: " << buffer << std::endl;
        close(fd[0]);
    }
    return 0;
}
