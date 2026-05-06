Though we defer discussion of a real process API until a subsequent
chapter, here we first give some idea of what must be included in any
interface of an operating system. These APIs, in some form, are available
on any modern operating system.


- Create: An operating system must include some method to cre-
ate new processes. When you type a command into the shell, or
double-click on an application icon, the OS is invoked to create a
new process to run the program you have indicated.

- Destroy: As there is an interface for process creation, systems also
provide an interface to destroy processes forcefully. Of course, many
processes will run and just exit by themselves when complete; when
they don’t, however, the user may wish to kill them, and thus an in-
terface to halt a runaway process is quite useful.

- Wait: Sometimes it is useful to wait for a process to stop running;
thus some kind of waiting interface is often provided.

- Miscellaneous Control: Other than killing or waiting for a process,
there are sometimes other controls that are possible. For example,
most operating systems provide some kind of method to suspend a
process (stop it from running for a while) and then resume it (con-
tinue it running).

- Status: There are usually interfaces to get some status information
about a process as well, such as how long it has run for, or what
state it is in


# Process Creation (A little more detail) 

The first thing that the OS must do to run a program is to load its code
and any static data (e.g., initialized variables) into memory, into the ad-
dress space of the process. Programs initially reside on disk (or, in some
modern systems, flash-based SSDs) in some kind of executable format;
thus, the process of loading a program and static data into memory re-
quires the OS to read those bytes from disk and place them in memory
somewhere 
