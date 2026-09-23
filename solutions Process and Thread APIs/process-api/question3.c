//
// Process API - Homework (Code), Question 3
//
// "Write another program using fork(). The child process should print
//  'hello'; the parent process should print 'goodbye'. You should try
//  to ensure that the child process always prints first; can you do
//  this without calling wait() in the parent?"
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
    // A plain global/local variable would NOT work here: after fork(),
    // parent and child have separate address spaces, so each would get
    // its own private copy and neither could see the other's writes
    // (see question1.c). To signal across the fork without wait(), we
    // need memory that is actually SHARED, which we get with mmap()
    // using MAP_SHARED | MAP_ANONYMOUS, set up before the fork.
    int *child_done = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (child_done == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    *child_done = 0;

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child
        printf("hello\n");
        fflush(stdout);
        *child_done = 1; // signal the parent, no wait() involved
    } else {
        // parent: busy-wait (spin) on the shared flag instead of wait()
        while (*child_done == 0)
            ; // spin until child sets the flag
        printf("goodbye\n");
    }

    return 0;
}

//
// ANSWER
// ------
// Yes, it's possible without wait(), but it does require some form of
// communication between the two processes, since fork() gives them
// separate address spaces. Here we set up a small region of memory with
// mmap(MAP_SHARED | MAP_ANONYMOUS) BEFORE calling fork(); because it was
// mapped MAP_SHARED before the fork, both parent and child end up with
// a mapping to the very same physical page, so writes by one are
// visible to the other (unlike ordinary heap/stack/global variables).
//
// The child prints "hello" and then sets the shared flag to 1. The
// parent spins in a tight loop reading the shared flag until it becomes
// nonzero, then prints "goodbye". This guarantees the ordering without
// ever calling wait() -- though it does "waste" CPU while the parent
// spins, which is exactly the kind of problem condition variables (a
// later chapter) exist to solve more efficiently.
//
