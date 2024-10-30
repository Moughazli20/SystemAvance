#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

#define SIZE (int)1e8
int tab[SIZE];

int global_min;
int global_max;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int start;
    int end;
} ThreadData;

void initialize_array() {
    for (int i = 0; i < SIZE; i++) {
        tab[i] = rand();
    }
}

void* thread_find_min_max(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int local_min = INT_MAX;
    int local_max = INT_MIN;

    for (int i = data->start; i < data->end; i++) {
        if (tab[i] < local_min) local_min = tab[i];
        if (tab[i] > local_max) local_max = tab[i];
    }

    pthread_mutex_lock(&mutex);
    if (local_min < global_min) global_min = local_min;
    if (local_max > global_max) global_max = local_max;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    initialize_array();

    global_min = INT_MAX;
    global_max = INT_MIN;

    int num_threads = 4;
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int segment_size = SIZE / num_threads;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start = i * segment_size;
        thread_data[i].end = (i + 1) * segment_size;
        if (i == num_threads - 1) thread_data[i].end = SIZE;
        pthread_create(&threads[i], NULL, thread_find_min_max, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);

    printf("Valeur minimale : %d\n", global_min);
    printf("Valeur maximale : %d\n", global_max);
    printf("Temps écoulé avec %d threads : %ld microsecondes\n", num_threads,
           ((end.tv_sec - start.tv_sec) * 1000000L + end.tv_usec) - start.tv_usec);

    pthread_mutex_destroy(&mutex);

    return 0;
}

