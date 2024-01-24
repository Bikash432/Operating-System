#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//Push the program to Git

#define number_of_threads 20

struct drand48_data randbuf;
pthread_mutex_t mutex;
int cir_points = 0;
int sq_points = 0;

void* calculate_the_estimate_using_mc(void* threadid) {
    double x, y;

    for (int i = 0; i < 10000 ; i++) {
        drand48_r(&randbuf, &x);
        drand48_r(&randbuf, &y);

        pthread_mutex_lock(&mutex);
        sq_points++;

        if ((x * x + y * y) <= 1.0) {
            cir_points++;
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[number_of_threads];
    long j;

    for (j = 0; j < number_of_threads; j++) {
        srand48_r(j, &randbuf);
    }


    for (j = 0; j < number_of_threads; j++) {
        int thread_mem_address = pthread_create(&threads[j], NULL, calculate_the_estimate_using_mc, (void*)j);
        if (thread_mem_address) {
            printf("Error: Unable to create thread %ld\n", j);
            exit(-1);
        }
    }
   /*
        There are 20 threads and we need to wait for each thread to complete pulling
        , so that we will complete the sequantialization of the order of the store
        Load --> Register and update.
    */
    for (j = 0; j < number_of_threads; j++) {
        pthread_join(threads[j], NULL);
    }
    /*
     As we know , the pi will be ratio of counts of points inside the circle and the square
     multiplied by 4
    */
    double pi = 4.0 * (double)cir_points / sq_points;

    printf("Estimated value of pi: %lf\n", pi);

    pthread_exit(NULL);
}

