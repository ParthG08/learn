# overview

## Virutalization


# What does that mean ??

How that is shown in the book?

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "common.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: cpu <string>\n"); // this is the line tha prints the error in case the code braks
        exit(1);
    }

    char *str = argv[1];

    while (1) {
        Spin(1); // waits for the code to run one second 
        printf("%s\n", str); // prints the input
    }
    
    return 0;
}
```

On running this 

```bash
gcc -o cpu cpu.c -Wall
```

Here the output will be something like this

```bash
prompt> gcc -o cpu cpu.c -Wall
prompt> ./cpu "A"
A
A
A
A
ˆC
prompt>
```

This cpu program that we have made  will be printing the argument giving to the function.
This would be happening after each one second is passed for the cpu.

Now this is a single function, imagine what would happen if there were two functions and 
both were run at the same time. 

How would the operating system decide as to which one to pick first to run, so the output 
of the program on the terminal would be acocordingly, if you run many programs at once
what would the response be like in the bash terminal, there is something something to think 
about.

```bash
prompt> ./cpu A & ; ./cpu B & ; ./cpu C & ; ./cpu D &
A
B
D
C
A
B
D
C
A
C
B
D
...
```


This is how the response looks if multiple  are run at once.

one processor -> multiple processes running at the same time. operating system along with the
hardware does something called virtualization.

Turning a single CPU (or small set of them) into a seemingly infinite number of CPUs and thus allowing many
programs to seemingly run at once. 

fun fact: the running and stopping and the virtualization of the processes that are happening in the OS are
happening with the help of some interfaces (APIs), that you can use to communicate your desires to the OS.

questions like 

1. which should run?
2. for how much time should the process run before we stop it?

etc are answered by the OS.

Here we learn about the **basic mechanisms** that operating systems implement
(such as the ability to run multiple programs at once). Hence the role of
the OS as a **resource manager**

