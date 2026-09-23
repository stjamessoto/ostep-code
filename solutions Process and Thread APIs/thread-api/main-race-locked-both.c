//
// Thread API - Homework (Code), Question 2 (part 2 of 2)
//
// Modified version of main-race.c: a lock is added around BOTH updates
// to the shared variable `balance` (in the worker thread AND in main).
// This is the correct fix -- see ANSWERS.md for what helgrind reports.
//
#include <stdio.h>

#include "mythreads.h"

int balance = 0;
pthread_mutex_t lock;

void* worker(void* arg) {
    Pthread_mutex_lock(&lock);
    balance++; // protected
    Pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    Pthread_mutex_init(&lock, NULL);

    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    Pthread_mutex_lock(&lock);
    balance++; // now protected too
    Pthread_mutex_unlock(&lock);
    Pthread_join(p, NULL);
    return 0;
}
