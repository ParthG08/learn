#  Introduction

## Stack 

Once the code and static data are loaded into memory, there are a few
other things the OS needs to do before running the process. Some mem-
ory must be allocated for the program’s **run-time stack** (or just stack).
As you should likely already know, C programs use the stack for local
variables, function parameters, and return addresses; the OS allocates
this memory and gives it to the process. The OS will also likely initial-
ize the stack with arguments; specifically, it will fill in the parameters to
the main()function, i.e., argc and the argv array.


## Heap

The OS may also allocate some memory for the program’s heap. In C
programs, the heap is used for explicitly requested **dynamically-allocated**
data; programs request such space by calling malloc() and free it ex-
plicitly by calling free(). The heap is needed for data structures such as
linked lists, hash tables, trees, and other interesting data structures. The
heap will be small at first; as the program runs, and requests more mem-
ory via the malloc()library API, the OS may get involved and allocate
more memory to the process to help satisfy such calls.
