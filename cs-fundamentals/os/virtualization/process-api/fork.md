# Intro to fork()


## Basic Understanding

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else { // parent goes down this path (main)
        printf("hello, I am parent of %d (pid:%d)\n",
        rc, (int) getpid());
    }
    return 0;
}
```


```bash
prompt> ./p1
hello world (pid:29146)
hello, I am parent of 29147 (pid:29146)
hello, I am child (pid:29147)
prompt>
```

The process calls the fork() system 
call, which the OS provides as a way to create a new process. The odd
part: the process that is created is an (almost) exact copy of the calling pro-
cess. That means that to the OS, it now looks like there are two copies of
the program p1running, and both are about to return from the fork()
system call. The newly-created process (called the child, in contrast to the
creating parent) doesn’t start running at main(), like you might expect
(note, the “hello, world” message only got printed out once); rather, it
just comes into life as if it had called fork()itself.

Note:   This means that when a process is replicated using the fork() essentially
        there is another same process that is triggered from the line 
        which has the code fork().

You might have noticed: the child isn’t an exact copy. Specifically, al-
though it now has its own copy of the address space (i.e., its own private
memory), its own registers, its own PC, and so forth, the value it returns
to the caller of fork() is different. Specifically, while the parent receives
the PID of the newly-created child, the child is simply returned a 0. This
differentiation is useful, because it is simple then to write the code that
handles the two different cases.
