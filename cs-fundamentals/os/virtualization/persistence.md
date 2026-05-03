# Persistence

Unlike the abstractions provided by the OS for the CPU and memory,
the OS does not create a private, virtualized disk for each application.

## The Core Queston

The file system is the part of the OS in charge of managing persistent data.
What techniques are needed to do so correctly? What mechanisms and
policies are required to do so with high performance? How is reliability
achieved, in the face of failures in hardware and software?


The OS provides a standard and simple way to access devices through its sys-
tem calls. Thus, the OS is sometimes seen as a standard library.