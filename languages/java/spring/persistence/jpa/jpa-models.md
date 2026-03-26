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