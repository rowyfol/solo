# Rewriting Linux Core Utils — A Practical Guide

## Why Do This?

Rewriting classic Unix/Linux tools is one of the best ways to deeply understand:
- How operating systems work under the hood
- Systems programming (file I/O, processes, signals, permissions)
- The POSIX standard and C standard library
- How simple-looking commands hide real complexity

---

## Before You Write a Single Line of Code

### 1. Set Up Your Environment

- **Language:** Start with **C**. The original coreutils are written in C, and reimplementing them in C gives you the closest experience to the real thing. Use Python for quick prototyping if you want to test logic first, and C++ later if you want to explore modern alternatives.
- **Compiler:** Make sure you have `gcc` or `clang` installed (`gcc --version` to check).
- **Build tool:** Learn basic `Makefile` usage — you'll want one per tool.
- **Version control:** Initialize a git repo in this folder (`git init`) and commit after every working milestone.
- **Man pages:** Your best friend. Before rewriting any tool, read its man page thoroughly:
  ```bash
  man ls
  man cat
  man wc
  ```

### 2. Read Before You Code

- Skim the [GNU Coreutils source](https://github.com/coreutils/coreutils) to see how the originals are structured. Don't try to understand everything — just get a feel.
- Bookmark the POSIX spec for the tool you're building: https://pubs.opengroup.org/onlinepubs/9699919799/
- Key C headers you'll use constantly: `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<dirent.h>`, `<sys/stat.h>`, `<unistd.h>`, `<errno.h>`.

### 3. Suggested Project Structure

```
solo/
├── instruct.MD          ← you are here
├── Makefile             ← top-level build (optional)
├── cat/
│   ├── mycat.c
│   └── Makefile
├── echo/
│   ├── myecho.c
│   └── Makefile
├── wc/
│   ├── mywc.c
│   └── Makefile
├── ls/
│   ├── myls.c
│   └── Makefile
└── ...
```

Each tool gets its own directory. Keep things isolated and simple.

---

## The Roadmap — What to Build and In What Order

The tools below are ordered from **easiest to hardest**. Each tier builds on skills from the previous one.

---

### Tier 1 — Warm-Up (The First Week)

These teach you basic file I/O, command-line argument parsing, and string handling.

| # | Tool     | What It Does                        | Key Concepts You'll Learn                    |
|---|----------|-------------------------------------|----------------------------------------------|
| 1 | `echo`   | Print arguments to stdout           | `argc/argv`, stdout, newline handling        |
| 2 | `yes`    | Repeatedly print a string           | Infinite loops, signal handling (`Ctrl+C`)   |
| 3 | `cat`    | Concatenate and print files         | `fopen/fread/fclose`, reading from stdin     |
| 4 | `head`   | Print first N lines of a file       | Line-by-line reading, `-n` flag parsing      |
| 5 | `tail`   | Print last N lines of a file        | Buffering, seeking, circular buffers         |
| 6 | `wc`     | Count lines, words, chars           | Character classification, multiple counters  |

**Start with `echo`.** It's 15–20 lines of C. You'll have it done in one session and feel the momentum.

---

### Tier 2 — File System Basics (Week 2–3)

These introduce directory traversal, file metadata, and permissions.

| # | Tool     | What It Does                        | Key Concepts You'll Learn                     |
|---|----------|-------------------------------------|-----------------------------------------------|
| 7 | `ls`     | List directory contents             | `opendir/readdir`, `stat()`, formatting output|
| 8 | `mkdir`  | Create directories                  | `mkdir()` syscall, permission modes           |
| 9 | `rm`     | Remove files/directories            | `unlink()`, `rmdir()`, recursive traversal    |
|10 | `cp`     | Copy files                          | Byte-level file copying, preserving metadata  |
|11 | `mv`     | Move/rename files                   | `rename()`, cross-device fallback (cp + rm)   |
|12 | `touch`  | Create file / update timestamps     | `utime()`, file creation                      |

**`ls` is the big one here.** Start with a bare `ls` (just list names), then add `-l`, `-a`, `-h` one flag at a time.

---

### Tier 3 — Text Processing (Week 3–5)

These are where things get genuinely interesting and challenging.

| # | Tool     | What It Does                        | Key Concepts You'll Learn                     |
|---|----------|-------------------------------------|-----------------------------------------------|
|13 | `grep`   | Search for patterns in files        | String matching, basic regex, line buffering  |
|14 | `sort`   | Sort lines of text                  | Sorting algorithms, comparators, temp files   |
|15 | `uniq`   | Remove duplicate adjacent lines     | Stateful line processing                      |
|16 | `cut`    | Extract columns from text           | Delimiter parsing, field selection             |
|17 | `tr`     | Translate/delete characters         | Character mapping, set operations             |
|18 | `tee`    | Read stdin, write to stdout + file  | Duplicating streams, `fork`-like thinking     |

---

### Tier 4 — Advanced / Boss Level (Week 5+)

Only attempt these after you're comfortable with everything above.

| # | Tool     | What It Does                        | Key Concepts You'll Learn                     |
|---|----------|-------------------------------------|-----------------------------------------------|
|19 | `less`   | Interactive file pager              | Terminal raw mode, `termios`, screen control   |
|20 | `find`   | Search for files recursively        | Recursive directory walking, expression trees  |
|21 | `xargs`  | Build commands from stdin           | Process spawning, `exec()`, argument limits    |
|22 | `chmod`  | Change file permissions             | Octal modes, symbolic parsing, `chmod()` call  |
|23 | `shell`  | A basic shell (bonus!)              | `fork/exec/wait`, pipes, redirection, signals  |

---

## How to Approach Each Tool

Follow this process every time:

1. **Read the man page** — `man <tool>`. Understand what it does and its most common flags.
2. **Use the real tool** — Run it with different inputs and flags. Observe exact output formatting (spaces, newlines, etc.).
3. **Start minimal** — Implement the simplest version first (no flags, happy path only).
4. **Add flags one at a time** — Each flag is a mini-project. Pick the most useful ones; you don't need all of them.
5. **Compare output** — Diff your tool's output against the real one:
   ```bash
   diff <(ls -l) <(./myls -l)
   ```
6. **Handle errors** — What happens with bad input? Missing files? No permissions? Add `errno` checks.
7. **Commit and move on** — Don't gold-plate. Get it working, commit, start the next tool.

---

## Your Daily 1-Hour Session Template

| Minutes   | Activity                                                  |
|-----------|-----------------------------------------------------------|
| 0–5       | Review yesterday's code, read notes                       |
| 5–15      | Read man page / research the concept you're tackling today|
| 15–50     | Write code, compile, test, iterate                        |
| 50–58     | Test edge cases, diff against real tool                   |
| 58–60     | Git commit with a clear message, jot a note on next steps |

---

## Essential Reference Commands

```bash
# Compile with warnings (always do this)
gcc -Wall -Wextra -pedantic -o mycat mycat.c

# Read the manual
man 2 stat      # syscall docs (section 2)
man 3 printf    # C library docs (section 3)

# Compare your output to the real tool
diff <(cat file.txt) <(./mycat file.txt)

# Check for memory leaks (install valgrind if needed)
valgrind ./mycat file.txt

# See what syscalls the real tool makes (great for learning)
strace ls -l 2>&1 | head -40
```

---

## Common Pitfalls

- **Don't try to be feature-complete.** The real `ls` has 50+ flags. Implement 4–5 useful ones and move on.
- **Don't skip error handling.** Checking return values of `fopen`, `malloc`, `read`, etc. is where real learning happens.
- **Don't ignore `stdin`.** Most text tools (cat, wc, grep, sort) should work with both files AND piped input.
- **Don't forget the newline.** Output formatting matters — match the real tool's output exactly.

---

## Recommended Reading (Optional)

- *The C Programming Language* by Kernighan & Ritchie (K&R) — the classic
- *Advanced Programming in the UNIX Environment* by W. Richard Stevens — the bible for this kind of work
- [GNU Coreutils source code](https://github.com/coreutils/coreutils) — read it when you're stuck
- [Rosetta Code](https://rosettacode.org) — see how others implement common tasks

---

**Start tomorrow with `echo`. It takes 15 minutes. Then do `yes`. Then `cat`. Build momentum. Good luck!**
