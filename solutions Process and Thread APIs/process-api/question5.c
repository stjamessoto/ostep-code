//
// Process API - Homework (Code), Question 5
//
// "Now write a program that uses wait() to wait for the child process
//  to finish in the parent. What does wait() return? What happens if
//  you use wait() in the child?"
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child: has no children of its own, so its call to wait()
        // cannot succeed
        printf("child  (pid:%d): calling wait(), but I have no children...\n", (int) getpid());
        int child_status;
        int child_wait_rc = wait(&child_status);
        printf("child  (pid:%d): wait() returned %d, errno = %d (%s)\n",
               (int) getpid(), child_wait_rc, errno, strerror(errno));
    } else {
        // parent: waits for the real child (rc == that child's pid)
        int status;
        int wait_rc = wait(&status);
        printf("parent (pid:%d): wait() returned %d (should match child pid %d)\n",
               (int) getpid(), wait_rc, rc);
        if (WIFEXITED(status))
            printf("parent (pid:%d): child exited normally with status %d\n",
                   (int) getpid(), WEXITSTATUS(status));
    }

    return 0;
}

//
// ANSWER
// ------
// In the parent, wait() blocks until (any) one of its children finishes,
// then returns the PID of that child -- here, that's the same value
// fork() returned to the parent. The int pointed to by wait()'s
// argument is filled in with status information about how the child
// exited; macros like WIFEXITED()/WEXITSTATUS() decode it.
//
// The child in this program has no children of its own (it never called
// fork() itself). Calling wait() there fails immediately: it returns -1,
// and errno is set to ECHILD ("No child processes"), because there is
// nothing for it to wait for. wait() only ever waits for processes that
// the CALLING process itself created.
//
