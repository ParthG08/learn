# Intro about the wait() system call

## Basic Understanding
This system call is useful when you want to run a program
that is different from the calling program

Note: Just like the fork runs the same program, the exec() call is for running an 
entirely different program.

In this example, the child process calls execvp() in order to run the
program wc, which is the word counting program. In fact, it runs **wc** on
the source file p3.c, thus telling us how many lines, words, and bytes are
found in the file


```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: "wc" (word count)
        myargs[1] = strdup("p3.c"); // argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // runs word count
        printf("this shouldn’t print out");
    } else { // parent goes down this path (main)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
        rc, wc, (int) getpid());
    }

    return 0;
}
```


```bash
prompt> ./p3
hello world (pid:29383)
hello, I am child (pid:29384)
29 107 1030 p3.c
hello, I am parent of 29384 (wc:29384) (pid:29383)
prompt>
```


What it does: given the name of an executable (e.g., wc),
and some arguments (e.g., p3.c), it loads code (and static data) from that
executable and overwrites its current code segment (and current static
data) with it; the heap and stack and other parts of the memory space of
the program are re-initialized. Then the OS simply runs that program,
passing in any arguments as the argv of that process. Thus, it does not
create a new process; rather, it transforms the currently running program
(formerly p3) into a different running program (wc). After the exec()
in the child, it is almost as if p3.cnever ran; a successful call to exec()
never returns.
