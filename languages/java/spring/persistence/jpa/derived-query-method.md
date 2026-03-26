# Overview

## Derived Query Method

```java
public interface LateFeeRepository
        extends JpaRepository<LateFee, Long>, JpaSpecificationExecutor<Loan> {

    LateFee getLateFeeById(long id);
```

The method LateFee getLateFeeById(long id); in your LateFeeRepository is what's known as a Derived Query Method in Spring Data JPA.


The "Magic" of Method Naming

Spring Data JPA looks at the name of the method and automatically generates the SQL query for you at runtime. You don't have to write any SQL because of how you named it:

1. get...By: This tells Spring to generate a SELECT query. (You could also use find...By, read...By, or query...By—they all do the same thing).
   
2. LateFee: This is just a hint for readability; Spring actually looks at the **return type** to know what object to build.
   
3. Id: This matches the field name in your LateFee entity class. Since your entity has an @Id field named id, Spring knows to add WHERE id = ? to the query.


# Query keyword

```java
@Query(value = "SELECT * FROM late_fee ORDER by id ASC limit ?1 offset ?2", nativeQuery = true)
    List<LateFee> getWithFilters(int limit, int offset);
```

1. Why use @Query?
Sometimes, a query is too complex for Spring’s "**magic**" naming convention (like getLateFeeById). For example, if you need to perform:

- Complex joins between tables.
- Use specific database features (like LIMIT and OFFSET for pagination).
- Run very optimized, raw SQL.
- In this case, the developer wanted precise control over the sorting and pagination.

2. What does nativeQuery = true mean?
This is a very important part of the annotation:

When true: You are writing Raw SQL (the exact language your database, like PostgreSQL or MySQL, understands). You must use the actual table names (late_fee) and column names as they exist in your database.

When false (default): You are writing JPQL (Java Persistence Query Language). JPQL uses your Java Class names (LateFee) and field names instead of the database names.

**How do the parameters work? (?1, ?2)**
The ?1 and ?2 are positional placeholders for your method's arguments:

?1: Refers to the first parameter of the method (int limit).
?2: Refers to the second parameter of the method (int offset).


So, when you call getWithFilters(10, 20), the actual SQL executed will be: 

```sql
SELECT * FROM late_fee ORDER by id ASC limit 10 offset 20
```

1. What does the SQL do?
SELECT * FROM late_fee: Fetch all columns from the late_fee table.
ORDER by id ASC: Sort the results by the ID in ascending order (lowest ID first).
limit ?1: Only return a specific number of records (e.g., 10 per page).
offset ?2: Skip a certain number of records before starting to return them (e.g., skip the first 20 records to show page 3).
