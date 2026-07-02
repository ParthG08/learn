# Shortcuts Binding in Dbeaver.

# DBeaver Shortcut Configurations

To update these keyboard shortcuts, navigate to:  
`Windows` → `Preferences` → `User Interface` → `Keys`

---

| Action | Shortcut | Purpose / Notes |
| :--- | :--- | :--- |
| **Maximize / Restore Active View** | `Cmd + B` | Quickly toggles the active editor or view to full screen. |
| **Toggle Results Panel** | `Ctrl + \`` | Shows/hides the bottom results pane. |
| **Toggle Results Panels** | `Cmd + L` | Alternative toggle mapping for results visualization. |
| **DBeaver Quick Access** | `Cmd + K` | Overrides the default layout. Global fuzzy finder for commands, views, and settings. |
| **Open Resource** | `Cmd + P` | Remapped to match standard editor workflows. Used for finding files and scripts. |

---

## DBeaver Quick Access (`Cmd + K`)

The philosophy behind using `Cmd + K` matches the search pattern found in tools like **Bruno** (`Cmd + K` / `Cmd + P`). It acts as a global fuzzy finder for your entire IDE workspace.

### Key Use Cases & Searchable Items

* **SQL Script Names:** This is the primary use case. It behaves exactly like `Cmd + Shift + A` in Google Chrome (used to find open tabs), allowing you to search through and jump straight to your saved script files.
* **Open Editor Tabs:** Quickly swap between your currently active database tabs.
* **DBeaver Core Commands:** Execute commands directly without touching the mouse:
  * *Invalidate/Reconnect*
  * *Commit*
  * *Rollback*
* **Views & Panels:** Jump directly to specific UI windows:
  * *Database Navigator*
  * *Project Explorer*
  * **Query Manager:** Incredibly useful for reviewing the history and logs of every single query run across your sessions.
* **Connection Names:** Quickly switch context between different database environments.
* **Preferences & UI Actions:** Instantly access deeper settings pages, projects, or bookmarks.

## Open everything using the Quick Menu.

Can open:
- Views (e.g., Database Navigator, Project Explorer)
- Commands
- Preferences
- Recently opened editors

## Open Database Navigator
```text
⌘3 (or ⌘K) → Database Navigator
```

## View Saved SQL Scripts
```text
⌘3 (or ⌘K) → Project Explorer
```

Navigate to:

```text
General
└── Scripts
```

## Search for a Script by Filename
```text
⌘⇧R → Open Resource
```

Type the script name to open it.

> **Note:** `⌘K` (Quick Access) does **not** search all SQL script files by name. Use `⌘R` (**Open Resource**) instead.

These shortcuts give Dbeaver more like a VSCode like feel which is great.

The useful shortcuts that already exist are: 

1. Command + Enter -> Run the SQL query,.
2. Tab in the Results Panel to change the view from Multiple Results to a single Result.


Note: Keep in mind that Dbeaver doesnt have conditional shortcuts only normal ones so keybinding for each one has to be completely unique.
