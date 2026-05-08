# Intro about the wait() call

## Basic Understanding

Sometimes, as it turns out, it is quite useful for a
parent to wait for a child process to finish what it has been doing. This
task is accomplished with the wait() system call.

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else { // parent goes down this path (main)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
        rc, wc, (int) getpid());
    }
    return 0;
 }
```

```bash
prompt> ./p2
hello world (pid:29266)
hello, I am child (pid:29267)
hello, I am parent of 29267 (wc:29267) (pid:29266)
prompt>
```

With this code, we now know that the child will always print first.
Why do we know that? Well, it might simply run first, as before, and
thus print before the parent. However, if the parent does happen to run
first, it will immediately call wait(); this system call won’t return until
the child has run and exited2. Thus, even when the parent runs first, it
politely waits for the child to finish running, then wait() returns, and
then the parent prints its message.

