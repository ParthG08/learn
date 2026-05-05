# VIRTUALIZATION OF MEMORY

Let’s take a look at a program. that allocates some mem-
ory by calling malloc()

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int
main(int argc, char *argv[])
{
    int *p = malloc(sizeof(int)); // a1
    assert(p != NULL); // a2
    printf("(%d) memory address of p: %08x\n", // a3
    getpid(), (unsigned) p); // a2
    *p = 0; // a4
    while (1) {
        Spin(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p); // a5
    }
    return 0;
}
```

Here we are running it.

```bash
prompt> ./mem
(2134) memory address of p: 00200000
(2134) p: 1
(2134) p: 2
(2134) p: 3
(2134) p: 4
(2134) p: 5
ˆC
```

When the process is run multiple times here is the output of the program

```bash
prompt> ./mem &; ./mem &
[1] 24113
[2] 24114
(24113) memory address of p: 00200000
(24114) memory address of p: 00200000
(24113) p: 1
(24114) p: 1
(24114) p: 2
(24113) p: 2
(24113) p: 3
(24114) p: 3
(24113) p: 4
(24114) p: 4
...
```

We see from the example that each running
program has allocated memory at the same address (00200000), and yet
each seems to be updating the value at 00200000independently. It is as
if each running program has its own private memory, instead of sharing
the same physical memory with other running programs


This is what is called as memory virtualization

Each process accesses its own **private virtual address** space
(sometimes just called its address space), which the OS somehow maps
onto the physical memory of the machine.

