#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void atexit_handler(void) {
	printf("Обработчик atexit() вызван\n");
}

void signal_handler(int sig) {
	printf("Обработчик SIGINT вызван. Получен сигнал: %d\n", sig);
}

void sigaction_handler(int sig, siginfo_t *si, void *unused) {
	printf("Обработчик SIGTERM вызван. Получен сигнал: %d\n", sig);
}

int main() {
	pid_t pid;
	struct sigaction sa;

	// Установка обработчика atexit()
	atexit(atexit_handler);

	// Установка обработчика SIGINT
	signal(SIGINT, signal_handler);

	// Установка обработчика SIGTERM
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sigaction_handler;
	sigaction(SIGTERM, &sa, NULL);

	pid = fork();

	if (pid < 0) {
		printf("Ошибка fork()\n");
		exit(1);
	} else if (pid == 0) {
		printf("Это процесс-потомок\n");
	} else {
		printf("Это процесс-родитель\n");
	}

	return 0;
}
