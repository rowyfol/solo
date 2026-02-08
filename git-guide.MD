# Git Setup & Daily Workflow — The Simple Version

## Option 1: You Haven't Cloned the Repo Yet (Starting Fresh)

### Step 1: Clone your GitHub repo

```bash
cd /home/ash/Documents
git clone https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git solo
cd solo
```

Replace `YOUR_USERNAME` and `YOUR_REPO_NAME` with your actual GitHub username and repository name.

**Alternative if using SSH:**
```bash
git clone git@github.com:YOUR_USERNAME/YOUR_REPO_NAME.git solo
```

Now you have a `solo` folder connected to your GitHub repo.

---

## Option 2: You Already Have Files Here (Connect Existing Folder)

You already have `/home/ash/Documents/solo` with files. Here's how to connect it:

### Step 1: Check if git is already initialized

```bash
cd /home/ash/Documents/solo
git status
```

**If it says "not a git repository":**
```bash
git init
git remote add origin https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git
```

**If it already shows git info but wrong remote:**
```bash
git remote -v                                    # see current remote
git remote set-url origin https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git
```

### Step 2: Pull existing content from GitHub (if any)

```bash
git pull origin main --allow-unrelated-histories
```

If it says "couldn't find remote ref main", try `master` instead:
```bash
git pull origin master --allow-unrelated-histories
```

**Note:** Some repos use `main`, others use `master` as the default branch. Use whichever one exists.

---

## Daily Workflow — How to Commit & Push Changes

### The 4-Step Loop (Do This Every Day)

```bash
# 1. See what changed
git status

# 2. Add your changes
git add .                    # adds everything
# OR be specific:
git add echo/                # add only the echo folder
git add instruct.MD echo.MD  # add specific files

# 3. Commit with a message
git commit -m "day 1: implement echo"

# 4. Push to GitHub
git push origin main         # or 'master' if that's your branch name
```

**That's it.** Repeat this loop after every session.

---

## Common Problems & Fixes

### Problem 1: "Please tell me who you are" error

Git needs to know your name and email (first time only):

```bash
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

Then try your `git commit` again.

---

### Problem 2: "Permission denied (publickey)" when pushing

You're using SSH but haven't set up SSH keys. **Two solutions:**

**Quick fix — Use HTTPS instead:**
```bash
git remote set-url origin https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git
git push origin main
```

It will ask for your GitHub username and password (or personal access token).

**Proper fix — Set up SSH keys** (do once, works forever):
1. Generate a key:
   ```bash
   ssh-keygen -t ed25519 -C "your.email@example.com"
   # Press Enter 3 times (use defaults)
   ```

2. Copy the public key:
   ```bash
   cat ~/.ssh/id_ed25519.pub
   ```

3. Go to GitHub.com → Settings → SSH and GPG keys → New SSH key
4. Paste the key, save it
5. Test:
   ```bash
   ssh -T git@github.com
   # Should say "Hi USERNAME! You've successfully authenticated"
   ```

---

### Problem 3: "Updates were rejected because the remote contains work..."

Someone (or you from another machine) pushed changes you don't have locally.

**Fix:**
```bash
git pull origin main         # download remote changes first
git push origin main         # now push yours
```

If you get a merge conflict, don't panic:
```bash
git status                   # shows which files have conflicts
# Open the files, look for <<<<<<< and >>>>>>>
# Edit to keep what you want, delete the markers
git add .
git commit -m "merge conflict resolved"
git push origin main
```

---

### Problem 4: "fatal: refusing to merge unrelated histories"

This happens when local and remote repos started separately.

**Fix:**
```bash
git pull origin main --allow-unrelated-histories
# If conflicts, resolve them (see Problem 3)
git push origin main
```

---

### Problem 5: "Password authentication was removed"

GitHub no longer accepts passwords for HTTPS. You need a **Personal Access Token (PAT)**.

**How to create one:**
1. Go to GitHub.com → Settings → Developer settings → Personal access tokens → Tokens (classic)
2. Click "Generate new token (classic)"
3. Give it a name like "solo project"
4. Check `repo` (full control of private repositories)
5. Click Generate token
6. **Copy the token immediately** (you can't see it again)

**Use it instead of your password:**
```bash
git push origin main
# Username: YOUR_USERNAME
# Password: paste_your_token_here
```

**To avoid typing it every time:**
```bash
git config --global credential.helper cache
# Now it remembers for 15 minutes
```

---

## Quick Reference Card

```bash
# Check status
git status

# Add everything
git add .

# Commit
git commit -m "your message here"

# Push
git push origin main

# Pull (download updates)
git pull origin main

# See remote URL
git remote -v

# Change remote URL
git remote set-url origin https://github.com/USER/REPO.git

# See your git config
git config --list
```

---

## Your Daily Git Routine (End of Each Session)

```bash
cd /home/ash/Documents/solo
git add .
git commit -m "day X: completed [tool name]"
git push origin main
```

**That's it.** Three commands. Do this every day and your work is always backed up.

---

## Test It Right Now

Let's make sure everything works:

```bash
cd /home/ash/Documents/solo
git status                                    # see current state
echo "# My Linux Tools Journey" > README.md   # create a readme
git add README.md
git commit -m "initial commit: add readme"
git push origin main                          # or master
```

If this works without errors — you're all set! 🎉
