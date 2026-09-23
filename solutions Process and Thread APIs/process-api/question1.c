//
// Process API - Homework (Code), Question 1
//
// "Write a program that calls fork(). Before calling fork(), have the
//  main process access a variable (e.g., x) and set its value to
//  something (e.g., 100). What value is the variable in the child
//  process? What happens to the variable when both the child and
//  parent change the value of x?"
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;
    printf("parent (pid:%d): before fork, x = %d\n", (int) getpid(), x);

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child: gets its own COPY of x, inherited from the parent
        // at the moment of fork(). It starts out as 100.
        printf("child  (pid:%d): right after fork, x = %d\n", (int) getpid(), x);
        x = 200; // modifying x here only changes the CHILD's copy
        printf("child  (pid:%d): after x = 200, x = %d\n", (int) getpid(), x);
    } else {
        // parent
        x = 300; // modifying x here only changes the PARENT's copy
        printf("parent (pid:%d): after x = 300, x = %d\n", (int) getpid(), x);
        wait(NULL); // wait so parent/child output doesn't interleave randomly
    }

    return 0;
}

//
// ANSWER
// ------
// Right after fork() returns, the child sees x == 100: fork() gives the
// child an (almost) exact copy of the parent's address space as it stood
// at the moment fork() was called, so the child inherits whatever value x
// held at that point.
//
// After the fork, though, parent and child have completely separate
// address spaces (the OS uses copy-on-write, but logically each process
// now owns its own private copy of every variable). So when the child
// sets x = 200, only the child's copy changes; the parent's x is
// untouched. Likewise, when the parent sets x = 300, only the parent's
// copy changes. Each process ends up seeing its own value, and neither
// modification is visible to the other process -- there is no shared
// memory here, just two independent copies of the same variable.
//
