# DBeaver Database Tasks

## What are Database Tasks?

Database Tasks are automated jobs that DBeaver can execute either:

* On demand
* At a later time
* On a recurring schedule

They are useful for automating common database operations without requiring manual intervention each time.

---

## Common Database Tasks

### Data Export

Export database data into external files.

Examples:

* Export table to CSV
* Export query results to Excel
* Export database dump

---

### Data Import

Import external data into database tables.

Examples:

* Import CSV into a table
* Import Excel data

---

### SQL Script Execution

Execute SQL scripts automatically.

Examples:

* Run a SQL file automatically
* Run maintenance scripts
* Execute cleanup jobs

---

### Backup

Create database backups.

Examples:

* PostgreSQL `pg_dump`
* MySQL `mysqldump`

---

### Restore

Restore databases from backup files.

Examples:

* Restore PostgreSQL backups
* Restore MySQL dumps

---

### Data Transfer

Move data between databases.

Examples:

* Copy data between databases
* Migrate tables from one server to another
* Synchronize data across environments

---

## Can Tasks Run in the Background?

Yes.

Unlike dashboards, database tasks can be configured to run automatically.

Supported execution modes:

* Run once
* Run later
* Run repeatedly on a schedule

Examples:

* Every day at 2:00 AM
* Every hour
* Every Sunday

---

## Important Difference: Dashboard vs Task

### Dashboard

* Runs monitoring queries only while the dashboard is open.
* Stops when the dashboard tab is closed.
* Used for observing database metrics.

### Database Task

* Can execute real database operations.
* Can be scheduled.
* May continue running automatically whenever its schedule triggers (provided DBeaver is running).

---

## How to Check Existing Tasks

Open:

```text
Window
  → Show View
      → Tasks
```

or

```text
Database
  → Tasks
```

Review the task list for:

* Export Tasks
* Import Tasks
* SQL Script Tasks
* Backup Tasks
* Restore Tasks
* Data Transfer Tasks

If the list is empty, no automated database jobs are configured.

---

## Key Takeaway

A dashboard is a temporary monitoring tool.

A database task is an automation mechanism capable of executing imports, exports, backups, restores, SQL scripts, and data transfers on a schedule or on demand.
