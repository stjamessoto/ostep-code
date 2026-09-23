//
// Process API - Homework (Code), Question 6
//
// "Write a slight modification of the previous program, this time using
//  waitpid() instead of wait(). When would waitpid() be useful?"
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // create THREE children, on purpose, to show off what wait() alone
    // cannot easily do: wait for one SPECIFIC child, by pid, out of order
    pid_t kids[3];
    for (int i = 0; i < 3; i++) {
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            printf("child #%d (pid:%d): running\n", i, (int) getpid());
            sleep(3 - i); // children finish in reverse order (2,1,0)
            printf("child #%d (pid:%d): done\n", i, (int) getpid());
            exit(100 + i); // distinct exit codes so we can tell them apart
        } else {
            kids[i] = rc; // parent remembers each child's pid
        }
    }

    // Instead of wait()-ing for "whichever child finishes next" (which
    // is all plain wait() can do), waitpid() lets the parent target a
    // SPECIFIC child by pid -- here, we deliberately wait for child #0
    // first, even though it will actually be the LAST to finish.
    for (int i = 0; i < 3; i++) {
        int status;
        int rc = waitpid(kids[i], &status, 0);
        if (WIFEXITED(status))
            printf("parent: waitpid() targeted child #%d (pid:%d), got pid %d back, exit status %d\n",
                   i, kids[i], rc, WEXITSTATUS(status));
    }

    return 0;
}

//
// ANSWER
// ------
// waitpid(pid, &status, options) is a more general version of wait():
//
//   - waitpid(-1, &status, 0) behaves just like wait(&status) -- wait
//     for ANY child.
//   - waitpid(pid, &status, 0), with pid > 0, waits for that ONE
//     specific child, no matter what order children actually finish in.
//     This program shows exactly that: the parent asks for child #0
//     first, even though (because of the sleep() amounts) child #0 is
//     really the last one to exit; waitpid() simply blocks until that
//     particular pid is available, skipping over the others.
//   - the 'options' argument also lets you do a non-blocking check via
//     WNOHANG: waitpid(pid, &status, WNOHANG) returns immediately with
//     0 if that child hasn't exited yet, instead of blocking. That's
//     essential for, e.g., a shell or server that needs to poll many
//     children (or do other work) without getting stuck waiting on any
//     single one of them.
//
// In short, waitpid() is useful whenever a process manages multiple
// children and needs to wait for a particular one, or needs to check on
// children without blocking -- plain wait() can only grab "whichever
// child happens to finish next."
//
