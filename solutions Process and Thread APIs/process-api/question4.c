//
// Process API - Homework (Code), Question 4
//
// "Write a program that calls fork() and then calls some form of exec()
//  to run the program /bin/ls. See if you can try all of the variants
//  of exec(), including (on Linux) execl(), execle(), execlp(),
//  execv(), execvp(), and execvpe(). Why do you think there are so
//  many variants of the same basic call?"
//
#define _GNU_SOURCE // needed for execvpe()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

// runs /bin/ls -l in a child using one particular exec() variant,
// then waits for that child before returning, so the demos run in order
static void run_variant(const char *label, void (*do_exec)(void)) {
    printf("\n--- %s ---\n", label);
    fflush(stdout); // flush BEFORE fork(), else stdio's buffer (which
                     // fork() copies as-is) gets flushed again inside
                     // the child, duplicating/reordering this line
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        do_exec(); // never returns on success
        fprintf(stderr, "%s: exec failed\n", label);
        exit(1);
    } else {
        wait(NULL);
    }
}

static void do_execl(void) {
    // fixed, explicit argument list; must give a full/relative path
    execl("/bin/ls", "ls", "-l", "question4.c", (char *) NULL);
}

static void do_execle(void) {
    // like execl, but we supply the environment explicitly ourselves
    char *myenv[] = { "MY_VAR=hello", NULL };
    execle("/bin/ls", "ls", "-l", "question4.c", (char *) NULL, myenv);
}

static void do_execlp(void) {
    // like execl, but searches $PATH for the program name -- no need
    // for a full path
    execlp("ls", "ls", "-l", "question4.c", (char *) NULL);
}

static void do_execv(void) {
    // arguments passed as an array instead of a variadic list; full path
    char *myargs[] = { "ls", "-l", "question4.c", NULL };
    execv("/bin/ls", myargs);
}

static void do_execvp(void) {
    // array-style args, but searches $PATH like execlp
    char *myargs[] = { "ls", "-l", "question4.c", NULL };
    execvp("ls", myargs);
}

static void do_execvpe(void) {
    // array-style args, searches $PATH, AND lets us pass an explicit
    // environment (a GNU/Linux extension, hence _GNU_SOURCE above)
    char *myargs[] = { "ls", "-l", "question4.c", NULL };
    char *myenv[] = { "MY_VAR=hello", NULL };
    execvpe("ls", myargs, myenv);
}

int main(int argc, char *argv[]) {
    run_variant("execl",   do_execl);
    run_variant("execle",  do_execle);
    run_variant("execlp",  do_execlp);
    run_variant("execv",   do_execv);
    run_variant("execvp",  do_execvp);
    run_variant("execvpe", do_execvpe);
    return 0;
}

//
// ANSWER
// ------
// All six calls do the same fundamental thing: replace the calling
// process's code/data with a new program image and start running it
// (loading /bin/ls in every case here). They differ along two
// independent axes, and the six names are just the 2x3 combinations:
//
//   1) How arguments are passed:
//        'l' (list) variants take a fixed, NULL-terminated variadic
//        argument list -- convenient when you know the exact,
//        fixed set of arguments at compile time (execl, execle, execlp).
//        'v' (vector) variants take a char *argv[] array -- necessary
//        when the argument list is built at runtime, e.g. from user
//        input or a loop (execv, execvp, execvpe).
//
//   2) How the program is found / what environment it runs with:
//        no suffix: you must give a full or relative path to the
//        executable, and the new program inherits the CALLER's
//        current environment (execl, execv).
//        'p' suffix: searches the directories in $PATH for the
//        program name, like a shell does, so you can just say "ls"
//        instead of "/bin/ls" (execlp, execvp, execvpe).
//        'e' suffix: lets the caller supply an explicit environment
//        array instead of inheriting the current one -- useful for a
//        shell implementing something like "FOO=bar ls", or for
//        sandboxing what the child program can see (execle, execvpe).
//
// So there aren't six unrelated calls -- there's really one operation
// (exec) with independent choices along "how are args given" and
// "how is the program found / what environment does it get", and the
// library provides a convenience wrapper for each useful combination
// rather than forcing every caller to build the argv[]/envp[] arrays
// and do the PATH search by hand every time.
//
