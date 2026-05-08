# Intro on process creation

## How are processes made in OS ?

how does the OS get a program up and running? How does process creation actually work?


The first thing that the OS must do to run a program is to load its code
and any static data (e.g., initialized variables) into memory, into the ad-
dress space of the process. Programs initially reside on disk (or, in some
modern systems, flash-based SSDs) in some kind of executable format;
thus, the process of loading a program and static data into memory re-
quires the OS to read those bytes from disk and place them in memory
somewhere (as shown in Figure 4.1).

# Difference between old and new OS.

In early (or simple) operating systems, the loading process is done ea-
gerly, i.e., all at once before running the program; modern OSes perform
the process lazily, i.e., by loading pieces of code or data only as they are
needed during program execution. To truly understand how lazy loading
of pieces of code and data works, you’ll have to understand more about
the machinery of paging and swapping, topics we’ll cover in the future
when we discuss the virtualization of memory.
