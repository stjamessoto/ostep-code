//
// Process API - Homework (Code), Question 2
//
// "Write a program that opens a file (with the open() system call) and
//  then calls fork() to create a new process. Can both the child and
//  parent access the file descriptor returned by open()? What happens
//  when they are writing to the file concurrently, i.e., at the same
//  time?"
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define NUM_WRITES 5

int main(int argc, char *argv[]) {
    int fd = open("question2.output", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child: writes using the SAME fd (and thus same underlying
        // open file description) that the parent opened
        for (int i = 0; i < NUM_WRITES; i++) {
            char buf[64];
            int len = snprintf(buf, sizeof(buf), "child  write #%d (pid:%d)\n", i, (int) getpid());
            write(fd, buf, len);
        }
    } else {
        // parent: writes using the same fd, concurrently with the child
        for (int i = 0; i < NUM_WRITES; i++) {
            char buf[64];
            int len = snprintf(buf, sizeof(buf), "parent write #%d (pid:%d)\n", i, (int) getpid());
            write(fd, buf, len);
        }
        wait(NULL);
        close(fd);
        printf("done; see question2.output for the interleaved result\n");
    }

    return 0;
}

//
// ANSWER
// ------
// Yes: file descriptors are among the things fork() duplicates into the
// child, and the child's copy of the fd refers to the exact same
// underlying "open file description" in the kernel as the parent's copy
// (not just the same file on disk). That means the parent and child
// share the same file offset -- every write() from either process,
// no matter which one does it, advances the SAME offset.
//
// When both processes write concurrently, write() on Linux is atomic
// with respect to that shared offset for reasonably small writes (it
// uses the offset, does the write, and updates the offset as a single
// kernel operation), so lines from the parent and child never get
// garbled together character by character. What you DO see, if you cat
// question2.output afterward, is that the lines from each process are
// interleaved in essentially random order -- whichever process's write()
// call the OS scheduler let run next -- but each individual write (each
// line here) is intact. If the parent and child had instead each called
// open() independently (two separate fds/offsets), they'd both start
// writing at offset 0 and could overwrite each other's data.
//
