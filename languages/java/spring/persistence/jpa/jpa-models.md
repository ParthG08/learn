# Overview

## The JPA (Standard) Annotations

These are part of the **Java Persistence API (JPA) standard**. 
They tell the database how to map your Java class to a table.

- @Entity: Marks this class as a database table.
- @Table: Specifies the name of the table in the database (late_fee).
- @Id: Marks the primary key field.
- @GeneratedValue / @SequenceGenerator: Tells JPA how to auto-increment the ID.
- @Column: Maps a Java field to a specific database column name.
- @Enumerated: Tells JPA how to store an Enum (e.g., as a String like "APPLIED").
- @Temporal: Specifies how to handle Date and Time formats.
- @PrePersist / @PreUpdate: Allows you to run code (like setting a timestamp) just before saving or updating.


```java
@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@Table(name = "late_fee")
@TypeDef(name = "jsonb", typeClass = JsonBinaryType.class)
@Slf4j
public class LateFee {
    @Id
    @SequenceGenerator(
            name = "late_fee_id_seq",
            sequenceName = "late_fee_id_seq",
            allocationSize = 1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "late_fee_id_seq")
    @Column(name = "id", unique = true, nullable = false, updatable = false)
    public long id;

    @Column(name = "uid")
    public String uid;

    @Column(name = "loan_id")
    public long loanId;

    @Column(name = "amount_su")
    public long amountSu;

    @Column(name = "type")
    @Enumerated(EnumType.STRING)
    public LateFeeType type;

    @Type(type = "jsonb")
    @Column(name = "metadata", columnDefinition = "jsonb")
    public Map<String, String> metadata;

    @Column(name = "created_at")
    @Temporal(TemporalType.TIMESTAMP)
    public Date createdAt;

    @Column(name = "updated_at")
    @Temporal(TemporalType.TIMESTAMP)
    public Date updatedAt;

    @Column(name = "created_by")
    public String createdBy;

    @PrePersist
    @PreUpdate
    public void updateTimeStamp() {
        if (createdAt == null) {
            createdAt = new Date();
        }
        updatedAt = new Date();
    }

    public void addMetadata(String metadataKey, String value) {
        if (metadata == null) {
            metadata = new HashMap<>();
        }
        metadata.put(metadataKey, value);
    }
}
```


## Primary Key Generation & Mapping

Here is the reference code using which the below notes have been made

```java
    @Id
    @SequenceGenerator(name = "mandate_id_seq", sequenceName = "mandate_id_seq", allocationSize = 1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "mandate_id_seq")
    @Column(name = "id", unique = true, nullable = false, updatable = false)
    long id;
```

This code defines how the Primary Key (`id`) is automatically generated and mapped to the database:
WITH LATEST_LOANS AS (
SELECT
    LOC.LOAN_ID,
    LOC.CUSTOMER_ID,
    LOC.LOAN_DISBURSED_DATE,
    LOC.LOAN_STATUS,
    LOC.ACTUAL_LOAN_END_DATE,
    LOC.LENDERNAME
FROM MODEL.LOAN_ORIGINATION_CHARACTERISTICS LOC
QUALIFY ROW_NUMBER() OVER (PARTITION BY LOC.CUSTOMER_ID ORDER BY LOC.LOAN_DISBURSED_DATE DESC NULLS LAST) = 1
),

RAW AS (
SELECT
    A.*,
    B.ACTIVE_MANDATES,
    B.ACTIVE_MANDATES_REFERENCE_IDS,
    C.SUB_STATUS,
    LOSS.LOSS_LOAN_ID,
    B.LOAN_CLOSED_DATE,
FROM LATEST_LOANS A
LEFT JOIN ANALYTICS.MODEL.COLLECTIONS_UPI_AUTOPAY_LOAN_MANDATES_AGGREGATED B
    ON B.LOAN_ID = A.LOAN_ID
LEFT JOIN APP_BACKEND.LOAN_SERVICE_PROD.PUBLIC_LOANS_VW C
    ON C.ID = A.LOAN_ID
LEFT JOIN
(
SELECT DISTINCT LOAN_ID AS LOSS_LOAN_ID
FROM APP_BACKEND.LOAN_SERVICE_PROD.PUBLIC_REPAYMENTS_VW
WHERE METADATA:"remarks"::string = 'Settlement Loss accepted by KB'
   OR METADATA:"tag"::string = 'SETTLEMENT_LOSS_ACCEPTED_BY_KB'
) LOSS
ON LOSS.LOSS_LOAN_ID = A.LOAN_ID

WHERE
    A.LOAN_STATUS = 'SETTLED'
    AND B.ACTIVE_MANDATES > 0
),

MANDATE_AFTER_CLOSER AS
(
SELECT
    A.LOAN_ID,
    MAX(IFF(M.CREATED_AT >= L.CLOSED_AT,1,0)) AS MANDATE_CREATED_AFTER_CLOSER_FLAG
FROM RAW A

CROSS JOIN LATERAL FLATTEN(INPUT => A.ACTIVE_MANDATES_REFERENCE_IDS) F

LEFT JOIN APP_BACKEND.LOAN_SERVICE_PROD.PUBLIC_LOANS_VW L
    ON A.LOAN_ID = L.ID
LEFT JOIN APP_BACKEND.LOAN_SERVICE_PROD.PUBLIC_MANDATE_VW M
    ON M.REFERENCE_ID::STRING = F.VALUE::STRING
GROUP BY A.LOAN_ID
),

RAW_DETAILS AS 
(
SELECT
    A.*,
    B.MANDATE_CREATED_AFTER_CLOSER_FLAG,
    LAA.USER_ID
FROM RAW A
LEFT JOIN MANDATE_AFTER_CLOSER B
    ON B.LOAN_ID = A.LOAN_ID
LEFT JOIN APP_BACKEND.LOAN_SERVICE_PROD.PUBLIC_LOAN_APPLICATIONS_VW LAA
    ON LAA.USER_ID = A.CUSTOMER_ID AND LAA.LENDER = A.LENDERNAME AND LAA.STATUS = 'ACTIVE'
)

-- SELECT
--     DATE_TRUNC(MONTH,ACTUAL_LOAN_END_DATE) AS CLOSURE_MONTH,
--     COUNT(DISTINCT LOAN_ID) AS COUNT_LOAN_ID,
--     COUNT(DISTINCT LOSS_LOAN_ID) AS COUNT_LOAN_ID_SETTLEMENT_LOSS_ACCEPTED_BY_KB,
--     COUNT(DISTINCT USER_ID) AS COUNT_LOAN_ID_APPLICATION_ACTIVE,
--     COUNT(DISTINCT IFF(MANDATE_CREATED_AFTER_CLOSER_FLAG = 1, LOAN_ID, NULL)) AS COUNT_LOAN_ID_MANDATE_CREATED_AFTER_CLOSER,
-- FROM RAW_DETAILS
-- GROUP BY ROLLUP(1)
-- ORDER BY 1;

SELECT
    * EXCLUDE(ACTIVE_MANDATES_REFERENCE_IDS, LOSS_LOAN_ID, MANDATE_CREATED_AFTER_CLOSER_FLAG, USER_ID)
FROM RAW_DETAILS
WHERE 1=1
    AND LOSS_LOAN_ID IS NULL
    AND MANDATE_CREATED_AFTER_CLOSER_FLAG = 0
    AND USER_ID
- **@SequenceGenerator**: Creates a generator named `mandate_id_seq` that links to a sequence in your database (also named `mandate_id_seq`). The `allocationSize = 1` ensures the ID increments by 1 for every new record.
- **@GeneratedValue**: Tells the application to use that specific sequence generator to automatically assign a value to the `id` field whenever a new record is saved.
- **@Column**: Maps the field to the `id` column in the database and enforces rules: it must be unique, cannot be empty (`nullable = false`), and cannot be changed once created (`updatable = false`).

### What is a Sequence?
A **Sequence** is a database object used to generate a unique list of numbers, typically for Primary Keys.

- **What it's for**: It ensures every new record gets a unique, incremental ID (1, 2, 3...) even when multiple users are creating records simultaneously.
- **Implementation**:
    - **Database side**: A physical object (e.g., `CREATE SEQUENCE late_fee_id_seq`) exists in your SQL database.
    - **Code side**: Hibernate/JPA asks the database for the "next value" of that sequence before saving a new object, then uses that number as the `id`.

