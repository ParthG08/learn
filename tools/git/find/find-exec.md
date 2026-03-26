Run a command on every file matched by find

General pattern

find <path> -type f -name "*.pdf" -exec <command> {} \;

{} --> replaced with each file
\; --> ends the command

Example:

find . -type f -name "*.pdf" -exec echo {} \;
Delete all .pdf files (safe methods)
1. Recommended (shows what will be deleted first)
find . -type f -name "*.pdf"

If output looks correct, run:

find . -type f -name "*.pdf" -delete
2. Using -exec rm
find . -type f -name "*.pdf" -exec rm {} \;
3. Faster for many files (batch delete)
find . -type f -name "*.pdf" -exec rm {} +

+ --> passes many files at once --> faster

4. Delete multiple extensions
find . -type f \( -name "*.pdf" -o -name "*.epub" -o -name "*.mobi" \) -delete
5. Delete only in current folder (not subfolders)
find . -maxdepth 1 -type f -name "*.pdf" -delete
Safest workflow
find . -type f -name "*.pdf"   # preview
find . -type f -name "*.pdf" -delete
# Find and Execute Commands on Files

## General Pattern

```bash
find <path> -type f -name "*.pdf" -exec <command> {} \;
```

- `{}` — replaced with each file
- `\;` — ends the command

## Example

```bash
find . -type f -name "*.pdf" -exec echo {} \;
```

## Delete All PDF Files

### 1. Recommended (Preview First)

```bash
find . -type f -name "*.pdf"
```

If output looks correct, run:

```bash
find . -type f -name "*.pdf" -delete
```

### 2. Using `-exec rm`

```bash
find . -type f -name "*.pdf" -exec rm {} \;
```

### 3. Faster for Many Files (Batch Delete)

```bash
find . -type f -name "*.pdf" -exec rm {} +
```

`+` passes many files at once for better performance.

### 4. Delete Multiple Extensions

```bash
find . -type f \( -name "*.pdf" -o -name "*.epub" -o -name "*.mobi" \) -delete
```

### 5. Delete Only in Current Folder (Not Subfolders)

```bash
find . -maxdepth 1 -type f -name "*.pdf" -delete
```

## Safest Workflow

```bash
find . -type f -name "*.pdf"   # preview
find . -type f -name "*.pdf" -delete
```