*This project has been created as part of the 42 curriculum by mfumeaux.*

# minishell

## Description

**minishell** is a small Unix shell written in C as part of the 42 curriculum.
The goal of the project is to understand, reimplement, and connect the core mechanisms behind a real shell: reading user input, tokenizing and parsing commands, handling environment variables, managing processes, building pipelines, applying redirections, and reacting correctly to signals.

This project is not meant to reproduce the entire behavior of Bash. Instead, it focuses on a solid subset of shell features and aims to behave as closely as possible to **Bash in POSIX-like usage** for the features that are implemented.

At a high level, minishell:

- displays an interactive prompt,
- reads and parses user input,
- executes builtins in the correct context,
- launches external commands with `fork`, `execve`, and `wait`,
- handles pipes and redirections,
- supports heredocs,
- manages environment variables,
- updates the shell exit status,
- reacts properly to signals such as `Ctrl-C`.

This project was especially useful to learn how a shell is split into clear stages:

1. **Lexing / tokenization**
2. **Syntax checking and parsing**
3. **Expansion and command preparation**
4. **Execution**
5. **Signal and file descriptor management**

---

## Features

The exact feature set may vary depending on the current state of the project, but minishell is designed around the following elements:

### Prompt and interactive behavior

- Interactive prompt using `readline`
- Command history
- Clean redisplay after signals
- Exit status tracking through `$?`

### Builtins

The project commonly includes these builtins:

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Execution

- Execution of external programs with `execve`
- Path lookup through the environment
- Correct parent/child split depending on the command
- Waiting on child processes and collecting exit codes

### Redirections and pipes

- Input redirection: `<`
- Output redirection: `>`
- Append redirection: `>>`
- Heredoc: `<<`
- Pipelines with `|`

- Redirections (>, <, >>) are processed before the actual command is executed (execve). This leads to specific behaviors that minishell accurately replicates:

	- Setup before Execution: If a command fails (e.g., ls folder_that_does_not_exist > out.txt), out.txt will still be created or truncated. The shell opens the file descriptors before it even realizes the command will fail.

	-  Left-to-Right Priority: If multiple redirections of the same type are provided, they are evaluated from left to right. The last one wins.

		Example: echo "hello" > a.txt > b.txt > c.txt

		Result: a.txt and b.txt are created (and left empty), but "hello" is only written into c.txt.

	- Invalid File Descriptor: If an early redirection fails (e.g., < root_file_no_access), the command is instantly aborted, and subsequent redirections or executions are skipped.


- Heredocs are handled in a dedicated pre-execution phase.
When a pipeline contains one or multiple heredocs, minishell:

	- Forks a child process dedicated to reading from readline until the delimiter is found.

	- Writes the input into a secure, hidden temporary file (e.g., /tmp/minishell_tmp_X).

	- Replaces the << redirection with a standard < redirection pointing to that temporary file.

	- Cleans up and unlinks the temporary files once the command finishes.

### Environment handling

- Internal environment list
- Export / unset support
- Conversion to `char **envp` for `execve`
- Exit status propagation through the shell state

### Signals

Special care is required for:

- interactive prompt behavior,
- child process behavior,
- heredoc behavior.

A large part of the project consists of reproducing expected shell reactions for `SIGINT` and `SIGQUIT`, especially when `readline` and heredocs are involved.

---

## Project Goals

This project is mainly about understanding **how a shell really works internally**.
It teaches:

- process creation and synchronization,
- file descriptor duplication with `dup` / `dup2`,
- pipes,
- signal handling with `signal` / `sigaction`,
- terminal interaction,
- environment management,
- robust error handling,
- modular program architecture.

It also forces careful thinking about execution rules such as:

- when a builtin must run in the parent,
- when a command must run in a child,
- which redirection wins when there are multiple ones,
- how heredoc interruptions should affect the current command,
- how to preserve the shell loop after errors and signals.

---

## Instructions

### Requirements

- A Unix-like system (Linux recommended)
- `gcc` or `cc`
- `make`
- `readline` library installed

### Compilation

Clone the repository and run:

```bash
make
```

Depending on the project structure, additional targets may also be available:

```bash
make clean
make fclean
make re
```

### Execution

Run the shell with:

```bash
./minishell
```

You should then get an interactive prompt where you can test commands.

### Basic examples

```bash
pwd
ls -la
export TEST=42
echo $TEST
cat infile | grep hello | wc -l
echo hi > out.txt
cat << LIMITER
hello
LIMITER
```

---

## Usage Notes

### Builtins in parent vs child

Some builtins must be executed in the **parent process** when they modify the shell state itself.
For example:

- `cd`
- `export`
- `unset`
- `exit`

If those are executed only in a child process, the parent shell would not keep the changes.

### Exit codes

minishell should update its last exit status after each command so the prompt state remains coherent and `$?` behaves as expected.

Typical examples include:

- command succeeded -> `0`
- command failed -> non-zero
- command not found -> usually `127`
- permission denied / execution failure -> usually `126`
- signal interruption -> status derived from the signal

### Heredocs and signals

Heredocs are one of the trickiest parts of minishell.
A correct implementation must carefully separate:

- prompt signal behavior,
- child signal behavior,
- heredoc signal behavior.

In practice, this means making sure `Ctrl-C` interrupts the heredoc cleanly without corrupting the next prompt or leaving the shell in a broken `readline` state.

---

## Technical Choices

The implementation is usually easier to maintain when it is separated into clear modules.
A common structure is:

- **lexer**: turns the input line into tokens,
- **parser**: validates syntax and builds command structures,
- **expander**: handles variable expansion and command preparation,
- **executor**: handles builtins, redirections, pipes, and external commands,
- **signals**: centralizes signal behavior for prompt / child / heredoc,
- **env**: stores and updates the shell environment.

Typical internal data structures include:

- linked lists for tokens,
- linked lists for environment variables,
- command tables or parser-built command nodes,
- redirection lists attached to each command.

This modular approach makes debugging easier, especially for subtle issues involving:

- file descriptor leaks,
- incorrect redirection priority,
- parent/child confusion,
- signal side effects,
- `readline` edge cases.

---

## What This Project Covers Well

minishell is a strong project for practicing:

- low-level C programming,
- debugging real execution flows,
- reasoning about process trees,
- reproducing observable shell behavior,
- writing code that is both modular and robust.

It is also a project where many bugs are not about syntax, but about **behavior**:

- an extra prompt,
- a bad exit code,
- a wrong signal reaction,
- a heredoc that leaves ghost input,
- a redirection applied in the wrong order.

Because of that, testing against Bash behavior is essential.

---

## Resources

### Classic references

The following references are useful to understand and build a shell:

- The Linux manual pages: `man 2 fork`, `man 2 execve`, `man 2 wait`, `man 2 pipe`, `man 2 dup2`, `man 2 signal`, `man 2 sigaction`
- The GNU Readline documentation
- Bash manual
- POSIX Shell Command Language reference
- Codevault videos on Youtube, which were very helpful for implementing forks and signals. https://www.youtube.com/@CodeVault


### Helpful topics to study

- process creation and waiting,
- pipes and file descriptor duplication,
- signal handling,
- terminal behavior,
- environment storage and conversion,
- builtin execution rules,
- parsing strategy for shell grammars,
- heredoc execution flow.

### How AI was used

AI was used as a **support tool**, not as a substitute for implementation or testing.
In this project, AI assistance was used for:

- clarifying shell concepts and execution flow,
- understanding parent/child behavior,
- reasoning about pipes, redirections, and heredocs,
- debugging signal-related issues,
- checking expected Bash-like behavior for edge cases,
- improving documentation wording and structure.
- understanding termios for signal restoration

The architecture decisions, code integration, debugging, testing, and final validation remained the responsibility of the project author.

---

## Testing

A shell project should be tested both on simple commands and on edge cases.
Useful categories include:

### Basic commands

```bash
ls
pwd
env
echo hello
```

### Builtins

```bash
cd .
export A=42
echo $A
unset A
exit
```

### Redirections

```bash
echo hello > a.txt
cat < a.txt
echo more >> a.txt
```

### Pipes

```bash
cat file | grep hello | wc -l
```

### Heredocs

```bash
cat << LIMITER
hello
world
LIMITER
```

### Signal cases

- `Ctrl-C` at the prompt
- `Ctrl-C` during heredoc
- `Ctrl-C` while a child command is running
- `Ctrl-\\` on external commands

### Error cases

- nonexistent command
- invalid redirections
- permission denied
- invalid builtin arguments
- syntax errors near pipes or redirections

---

## Limitations

This project intentionally implements only a subset of a full shell.
Features outside the subject scope may be absent, incomplete, or intentionally ignored.

Examples may include:

- advanced Bash scripting features,
- command substitution,
- logical operators not required by the subject,
- wildcard expansion,
- subshell behavior beyond the requested scope.

---

## Final Note

minishell is one of the most formative projects in the 42 curriculum because it connects parsing, execution, signals, processes, and system programming into one coherent program.
It is less about printing the right output once, and more about building a shell that stays stable, predictable, and interactive across many real terminal situations.
