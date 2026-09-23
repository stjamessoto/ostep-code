//
// Thread API - Homework (Code), Question 2 (the "remove one line" part)
//
// Modified version of main-race.c: instead of adding a lock, we simply
// remove ONE of the two unprotected updates to `balance` (the one in
// the worker thread). Only main() touches `balance` now.
//
#include <stdio.h>

#include "mythreads.h"

int balance = 0;

void* worker(void* arg) {
    // balance++;  <-- removed: worker no longer touches the shared var
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    balance++; // only remaining access to the shared variable
    Pthread_join(p, NULL);
    return 0;
}
