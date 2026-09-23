//
// Thread API - Homework (Code), Question 2 (part 1 of 2)
//
// Modified version of main-race.c: a lock is added around ONLY ONE of
// the two updates to the shared variable `balance` (the one in the
// worker thread), leaving the update in main() unprotected. This is
// deliberately still buggy -- see ANSWERS.md for what helgrind reports.
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
    balance++; // still UNPROTECTED -- same race as before
    Pthread_join(p, NULL);
    return 0;
}
