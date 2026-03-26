# Overview

# repositories

This is the Database Layer.

Role: Interfaces with the database (SQL/NoSQL). It contains methods like save(), findById(), or custom queries like findByLoanId().
Significance: It abstracts away the complexity of writing raw SQL. The Service layer calls the Repository to fetch or store data.