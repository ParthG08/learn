# Hardware Protection from system calls

## Ideation

When operating systems took on a more central role in managing machines. One
important aspect of this was the realization that code run on behalf of the
OS was **special**; it had control of devices and thus should be treated dif
ferently than normal application code.

Thus, the idea of a **system call** was invented. Instead of providing OS routines as a library
(where you just make a procedure call to access them), the idea here
was to add a special pair of hardware instructions and hardware state to
make the transition into the OS a more formal, controlled process.

The key difference between a system call and a procedure call is that
a system call transfers control (i.e., jumps) into the OS while simultaneously
raising the **hardware privilege level**

User applications run in what is referred to as **user mode** which means the
hardware restricts what applications can do; for example, an application 
running in user mode can’t typically initiate an I/O request to the disk,
access any physical memory page, or send a packet on the network.
When a **system call** is initiated (usually through a special hardware instruction
called a **trap**), the hardware transfers control to a pre-specified trap handler 
(that the OS set up previously) and simultaneously raises the privilege 
level to kernel mode. In **kernel mode**, the OS has full access to the 
hardware of the system and thus can do things like initiate an I/O 
request or make more memory available to a program. When the OS is 
done servicing the request, it passes control back to the user via a 
special return-from-trap instruction, which reverts to user mode while 
simultaneously passing control back to where the application left off.

The "Gatekeeper" Model

- The core design remains a Gatekeeper system. Think of it like a secure building:

- User Mode (The Lobby): You can walk around freely, but you can't access the vault.

- The Trap (The Security Gate): The only way to get to the vault is through a specific door with a guard.

Kernel Mode (The Vault): Only the guard (the OS) can open the door and perform actions inside.
