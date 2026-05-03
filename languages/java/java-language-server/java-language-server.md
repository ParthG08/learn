# Overview

## Java Language Server

Java Language Server is the **background engine** that gives Java intelligence in Visual Studio Code. ⚙️

It handles:

- Autocomplete
- Go to definition
- Cmd + T symbol search
- Error checking
- Refactoring
- Method/class indexing


“Open Java Language Server Log” means

It opens the debug log of that engine 📜 — useful to see why indexing or symbol search isn't working.

You’ll see things like:

- Project import failures
- Maven/Gradle errors
- Missing JDK
- Indexing stopped
- File parsing errors
- How to open

Cmd + Shift + P → Java: Open Java Language Server Log

What you’re looking for

Search for keywords:

- ERROR
- Failed
- Build
- Import
- Index

If you paste the first few error lines here, I’ll tell you exactly what's wrong.