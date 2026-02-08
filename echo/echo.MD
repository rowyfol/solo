# Day 1 — Building `echo`

## What Does `echo` Do?

It prints its arguments to standard output, separated by spaces, followed by a newline.

```bash
echo hello world        # prints: hello world
echo -n hello world     # prints: hello world (no trailing newline)
echo                    # prints: (just an empty line)
```

That's it. Deceptively simple — perfect for day 1.

---

## Before You Code

### Read the man page

```bash
man echo
```

Pay attention to:
- What happens when there are **no arguments**?
- What does the `-n` flag do?
- What is the difference between `/bin/echo` and your shell's built-in `echo`? (Use `/bin/echo` as your reference.)

### Play with it

Run these and observe the **exact** output (spaces, newlines):

```bash
/bin/echo
/bin/echo hello
/bin/echo hello world
/bin/echo -n hello
/bin/echo -n
/bin/echo ""
/bin/echo "hello   world"
```

---

## What You Need to Know

### 1. `argc` and `argv`

Every C program receives command-line arguments through `main`:

```c
int main(int argc, char *argv[])
```

- `argc` — the count of arguments (includes the program name itself)
- `argv` — an array of strings (each argument as a `char *`)

For example, if you run `./myecho hello world`:
- `argc` is `3`
- `argv[0]` is `"./myecho"`
- `argv[1]` is `"hello"`
- `argv[2]` is `"world"`

Your actual arguments start at `argv[1]`.

### 2. Printing to stdout

You have two main options:
- `printf()` — formatted output, you control exactly what gets printed
- `fputs()` / `putchar()` — simpler, writes strings or single characters

For `echo`, `printf` or `fputs` both work fine. Think about when to print a **space** between words and when to print a **newline** at the end.

### 3. String comparison

To check if an argument equals `"-n"`, use `strcmp()` from `<string.h>`. Remember: `strcmp` returns `0` when strings are **equal** (not `1` — this trips up beginners).

### 4. Return value

Your program should `return 0` on success. This is the exit code — `0` means everything went fine.

---

## Step-by-Step Plan

### Step 1 — The skeleton

Set up your project:

```bash
mkdir -p echo
cd echo
touch myecho.c Makefile
```

Write a `main` function that just returns 0. Compile and run it to make sure your toolchain works:

```bash
gcc -Wall -Wextra -o myecho myecho.c
./myecho
```

### Step 2 — Print all arguments

Loop through `argv` starting at index `1`. Print each argument. Print a **space** between arguments (but not after the last one). Print a **newline** at the end.

Test:
```bash
./myecho hello world
# should output: hello world
```

### Step 3 — Handle no arguments

What should happen when you run `./myecho` with nothing? Just a newline. Make sure your loop handles this naturally.

### Step 4 — Add the `-n` flag

If the **first** argument is `"-n"`, skip the trailing newline and start printing from `argv[2]` instead.

Test:
```bash
./myecho -n hello
# should output: hello (with no newline — your prompt appears right after)
```

### Step 5 — Write a Makefile

A simple one is enough:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

myecho: myecho.c
	$(CC) $(CFLAGS) -o myecho myecho.c

clean:
	rm -f myecho
```

Now you can build with `make` and clean with `make clean`.

### Step 6 — Test against the real thing

```bash
diff <(/bin/echo hello world) <(./myecho hello world)
diff <(/bin/echo -n hello) <(./myecho -n hello)
diff <(/bin/echo) <(./myecho)
```

If `diff` prints nothing — you match. You're done.

---

## Edge Cases to Think About

- What if someone runs `./myecho -n` with no other arguments?
- What if the argument is literally `"-n"` but not the first argument? e.g., `./myecho hello -n world`
- What about multiple spaces? (Hint: the shell handles this before your program even sees it — understand why.)

---

## Stretch Goals (If You Have Time Left)

- Add support for `\\n` (print a newline in the middle of a string) and `\\t` (print a tab) — this is what the `-e` flag does in some versions of `echo`
- Look at what `strace /bin/echo hello` shows — what syscall actually writes to the terminal?

---

## Commit When Done

```bash
cd /home/ash/Documents/solo
git init   # only if you haven't already
git add echo/
git commit -m "day 1: implement echo"
```

**Tomorrow's tool: `yes`** — an infinite loop that teaches you about signals and `Ctrl+C`.
