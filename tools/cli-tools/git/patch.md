## Patch

So apparently there is something called patches in git, which are a standardized text representation to show what changes have been applied to your repository in a particular commit.

A patch file is essentially a set of instructions that tells Git exactly which lines to add, remove, or modify to replicate those changes elsewhere.

# What it contains
When you select this, a "diff" formatted text is copied to your clipboard. It typically looks like this:

1. Metadata: Information about the file path and the commit hashes.

2. Markers: --- for the original version and +++ for the new version.

3. Hunks: Specific sections of code preceded by @@ (line numbers), where:

Lines starting with - are removed.

Lines starting with + are added.

Unmarked lines provide context.

To view this for instance, you can right click on the file in the compare menu in the git, and select the

```text
copy changes (patch)
```

and this will copy all the changes in patch format the patch file of the patch.md file that i am currently writing looks something like this


```text
diff --git a/tools/git/patch.md b/tools/git/patch.md
new file mode 100644
index 0000000..b989961
--- /dev/null
+++ b/tools/git/patch.md
@@ -0,0 +1,17 @@
+## Patch 
+
+
+
+So apparently there is something called patches in git, which are a text format based way to show what changes have 
+been applied to your repository in a particular commit, for 
+
+1. the whole commit
+2. particular file 
+
+To view this for instance, you can right click on the file in the compare menu in the git, and select the
+
+```text
+copy changes (patch)
+```
+
+and this will 
\ No newline at end of file
```

and this has various usecases.

# Why use it?

1. Sharing without Branches: You can send a patch via email or chat to a teammate so they can apply your exact changes to their local environment without you needing to push to a remote server.

2. Portability: It allows you to apply the same logic to a different branch or even a completely different repository if the file structures match.

3. Code Reviews: It provides a lightweight way to show someone exactly what was changed in a specific commit.


# How to use it
Once you have copied the patch, another person can apply it using the terminal command:
git apply (followed by pasting the content or pointing to a .patch file).



(Right now i am making notes on the KB laptop (3rd may 2026) and i am exploring ways to import all the changes that i am doing directly using the web, worth exploring solutions to be able to commit directly using the web UI.)