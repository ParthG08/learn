# Gmail Search Operators Cheat Sheet

## Time & Age Filters
* `before:YYYY/MM/DD`: Finds emails sent before a specific date.
* `after:YYYY/MM/DD`: Finds emails sent after a specific date.
* `older_than:3m`: Finds emails older than 3 months (also supports `d` for days, `y` for years).
* `newer_than:7d`: Finds emails received in the last week.

## Sender & Recipient Filters
* `from:name@email.com`: Filters all emails from a specific sender.
* `to:name@email.com`: Filters all emails sent to a specific person.
* `cc:name@email.com` / `bcc:name@email.com`: Finds emails where a specific person was cc'd or bcc'd.

## Content & Attachment Filters
* `has:attachment`: Shows only emails that include files.
* `has:drive` / `has:document` / `has:spreadsheet` / `has:pdf`: Narrows down attachments to specific file types.
* `filename:pdf`: Finds emails with specific file extensions.
* `subject:keyword`: Searches only the subject line for a specific topic.
* `list:mailinglist@email.com`: Filters emails from a specific mailing list.

## Status & Organization Filters
* `is:unread`: Shows only unread messages.
* `is:starred`: Shows only starred emails.
* `is:important`: Shows only emails marked as important.
* `has:userlabels`: Shows only emails you have manually labeled.
* `is:trash` / `is:spam`: Searches specifically within trash or spam folders.

## Advanced Techniques
* **Combining Operators:** You can mix filters to refine searches, e.g., `from:bank.com has:attachment is:unread`.
* **Exclusion:** Use the minus sign (`-`) to exclude terms, e.g., `from:groww.in -subject:statement` to filter out specific topics.
