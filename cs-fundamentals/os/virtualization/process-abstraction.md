# Introduction

The abstraction provided by the OS of a running program is something
we will call a process. (basically a running program is called a process)

To understand what constitutes a process, we thus have to understand
its machine state: what a program can read or update when it is running.
At any given time, what parts of the machine are important to the execu-
tion of this program?

One obvious component of machine state that comprises a process is
its memory. Instructions lie in memory; the data that the running pro-
gram reads and writes sits in memory as well. Thus the memory that the
process can address (called its address space) is part of the process.
