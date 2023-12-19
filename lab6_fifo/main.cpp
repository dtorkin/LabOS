#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <ctime>
#include <sstream>

int main() {
    mkfifo("/tmp/my_fifo", 0666);
    pid_t pid = fork();
    if (pid > 0) {
        int fd = open("/tmp/my_fifo", O_WRONLY);
        time_t now = time(0);
        char* dt = ctime(&now);
        std::ostringstream ss;
        ss << "PID: " << getpid() << ", Time: " << dt;
        std::string s = ss.str();
        write(fd, s.c_str(), s.size() + 1);
        close(fd);
        wait(NULL);
    } else if (pid == 0) {
        int fd = open("/tmp/my_fifo", O_RDONLY);
        sleep(5);
        char buffer[4096];
        read(fd, buffer, sizeof(buffer));
        time_t now = time(0);
        char* dt = ctime(&now);
        std::cout << "PID: " << getpid() << ", Time: " << dt;
        std::cout << "Recieved via fifo: " << buffer << std::endl;
        close(fd);
    }
    return 0;
}
