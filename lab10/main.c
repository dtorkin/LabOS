#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 10
#define NUM_WRITERS 1

pthread_mutex_t mutex;
pthread_cond_t cond;
char buffer[256];
int counter = 0;
int data_ready = 0;

void *reader(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (!data_ready) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Reader %ld: %s\n", pthread_self(), buffer);
        data_ready = 0;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void *writer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        sprintf(buffer, "Write number: %d", counter++);
        data_ready = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
