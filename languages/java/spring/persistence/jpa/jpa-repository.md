# Overview

## JPA repository


The motive of the JPA Repository is to write a lot lesser boilerplate code in the repository section of each module.

**JpaRepository** and **JpaSpecificationExecutor** are core parts of Spring Data JPA, a framework that significantly reduces the amount of boilerplate code you need to write for database operations.

1. What is JpaRepository<LateFee, Long>?
    This is a **marker interface** that tells Spring to automatically generate a database access layer for your LateFee entity.

    *LateFee*: The entity class this repository handles.
    *Long*: The data type of the Primary Key (@Id) in the LateFee class.

    Why is it used everywhere? Because by simply extending it, you get all these methods for free without writing a single line of SQL or implementation code:

    save(entity): Insert or Update.
    findById(id): Fetch by primary key.
    findAll(): Fetch all records.
    delete(entity): Remove a record.
    count(): Get total records.

2. What is JpaSpecificationExecutor<Loan>?
    This interface allows you to execute dynamic queries using the JPA Criteria API (called "Specifications" in Spring).

    It is used when you have a search screen with many optional filters (e.g., "Find late fees where amount > X AND date < Y AND status = Z").
    Instead of writing 10 different @Query methods for every combination of filters, you can build a Specification object at runtime and pass it to a single findAll(specification) method.