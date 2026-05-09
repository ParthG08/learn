# Intro about the pipe() system call

## Basic Understanding
The pipe system call is used club multiple series or programs where the output of one program is required 
as the input of the next.

Note: Now the functioning of the pipe() command is pretty interesting as it has to decide as to which functions of the 
program that is written in the upstream part of the code, is acutally to be implemented.

Here is an example, (seperation of exec() and fork())

```bash
prompt> wc p3.c > newfile.txt
```

In the example above, the output of the program wc is redirected into
the output file newfile.txt (the greater-than sign is how said redirec-
tion is indicated). The way the shell accomplishes this task is quite sim-
ple: when the child is created, before calling exec(), the shell closes
standard output and opens the file newfile.txt. By doing so, any out-
put from the soon-to-be-running program wc are sent to the file instead
of the screen.

```c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child: redirect standard output to a file
        close(STDOUT_FILENO);
        open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

        // now exec "wc"...
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: "wc" (word count)
        myargs[1] = strdup("p4.c"); // argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // runs word count
    } else { // parent goes down this path (main)
        int wc = wait(NULL);
    }
    return 0;
}
```



the shell just prints is immediately ready for your next command.
However, that is not the case that the program call fork; the program p4 did indeed call fork()
to create a new child, and then run the wc program via a call to execvp().
You don’t see any output printed to the screen because it has been redi-
rected to the file p4.output. Second, you can see that when we cat the
output file, all the expected output from running wc is found. 


UNIX pipes are implemented in a similar way, but with the pipe()
system call. In this case, the output of one process is connected to an in-
kernel pipe (i.e., queue), and the input of another process is connected
to that same pipe; thus, the output of one process seamlessly is used as
input to the next, and long and useful chains of commands can be strung
together. As a simple example, consider looking for a word in a file, and
then counting how many times said word occurs; with pipes and the util-
ities grepand wc, it is easy — just type grep -o f.