# Use of data structures in process management

The OS is a program, and like any program, it has some key data struc-
tures that track various relevant pieces of information. To track the state
of each process, for example, the OS likely will keep some kind of *process*
*list* for all processes that are ready, as well as some additional informa-
tion to track which process is currently running. The OS must also track,
in some way, blocked processes; when an I/O event completes, the OS
should make sure to wake the correct process and ready it to run again.

Below is shown  what type of information an OS needs to track about
each process in the xv6 kernel [CK+08]. Similar process structures exist
in “real” operating systems such as Linux, Mac OS X, or Windows; look
them up and see how much more complex they are.


The **register context** will hold, for a
stopped process, the contents of its registers. When a process is stopped,
its registers will be saved to this memory location; by restoring these reg-
isters. This is doucmented in more detial further in the context switching documentation.

```c
// the registers xv6 will save and restore
// to stop and subsequently restart a process
struct context {
    int eip;
    int esp;
    int ebx;
    int ecx;
    int edx;
    int esi;
    int edi;
    int ebp;
};

// the different states a process can be in
enum proc_state { UNUSED, EMBRYO, SLEEPING,
RUNNABLE, RUNNING, ZOMBIE };
// the information xv6 tracks about each process
// including its register context and state

struct proc {
    char *mem; uint sz; char *kstack; // Start of process memory
    // Size of process memory
    // Bottom of kernel stack
    // for this process
    enum proc_state state; // Process state
    int pid; // Process ID
    struct proc *parent; // Parent process
    void *chan; // If non-zero, sleeping on chan
    int killed; // If non-zero, have been killed
    struct file *ofile[NOFILE]; // Open files
    struct inode *cwd; // Current directory
    struct context context; // Switch here to run process
    struct trapframe *tf; // Trap frame for the
    // current interrupt
};
```
