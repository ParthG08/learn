# Abstraction

1. One of the most basic goals in this book is to build up some **abstractions** in order
to make the system convenient and easy to use. Abstractions are fun-
damental to everything we do in computer science. Abstraction makes
it possible to write a large program by dividing it into small and under-
standable pieces, to write such a program in a high-level language like
C9 without thinking about assembly, to write code in assembly without
thinking about logic gates, and to build a processor out of gates without
thinking too much about transistors. Abstraction is so fundamental that
sometimes we forget its importance, but we won’t here; thus, in each sec-
tion, we’ll discuss some of the major abstractions that have developed
over time, giving you a way to think about pieces of the OS.


2. One goal in designing and implementing an operating system is to
provide **high performance**; another way to say this is our goal is to 
**mini-mize the overheads** of the OS.

3. Protection is at the heart of one of the main principles underlying an operating system,
which is that of isolation; isolating processes from one another is the key
to protection and thus underlies much of what an OS must do.
The operating system must also run non-stop; when it fails, 