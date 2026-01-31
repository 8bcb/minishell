*This project has been created as part of the 42 curriculum by jziola, pkosciel.*

# Minishell

## Description

Minishell is a simplified Unix shell implemented in C.  
The goal of this project is to understand how a real shell works by recreating its core behavior, including command parsing, process creation, signal handling, pipes, redirections, environment variables, and built-in commands.

The shell provides an interactive prompt, executes external programs using `execve`, and supports basic shell features such as:
- pipelines (`|`)
- input/output redirections (`<`, `>`, `>>`)
- heredocs (`<<`)
- environment variable expansion (`$VAR`, `$?`)
- built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
- proper handling of signals like `Ctrl-C` and `Ctrl-\`

This project is designed to deepen understanding of Unix system calls, process management, file descriptors, and terminal behavior.

---

## Instructions

### Compilation

To compile the project, run:

```sh
make
```

This will produce an executable named:

```sh
./mini
```

### Execution

Run the shell with:

```sh
./mini
```

You will then see an interactive prompt:

```sh
Prompt[0]>
```

From there, you can execute commands similarly to a standard shell:

```sh
echo hello | wc -w
export VAR=value
cat << EOF
```

To exit the shell, use:

```sh
exit
```

or press `Ctrl-D`.

## Features Overview

- Interactive prompt with command history
- Lexing and parsing into an AST
- Execution of external programs with fork + execve
- Builtins executed in the parent process when required
- Pipelines using Unix pipes
- Redirections with proper file descriptor handling
- Heredoc support with correct signal behavior
- Environment stored internally and converted to envp when needed
- Signal handling adapted to interactive mode, execution mode, and heredoc mode

## Resources

### Technical References

**GNU Bash Manual**

https://www.gnu.org/software/bash/manual/

**Advanced Programming in the UNIX Environment** – W. Richard Stevens

**Linux Man Pages**

- `man fork`
- `man execve`
- `man pipe`
- `man dup2`
- `man signal`
- `man readline`
- `man termios`

**42 Minishell Subject PDF**

## AI Usage Disclosure

AI tools were used during the development of this project as **an assistance tool**, not as a code generator.

Specifically, AI was used to:

- clarify Unix concepts such as processes, signals, pipes, and heredocs
- explain expected shell behavior and edge cases
- help debug logic errors and memory issues
- assist in understanding and structuring the project architecture
- help draft this README file

All code was written, tested, and validated by the project authors, in compliance with the 42 school rules and constraints.

## Notes

This project follows the 42 Norm and only uses functions explicitly allowed by the subject.
The implementation focuses on correctness, robustness, and clear separation of responsibilities between parsing, execution, and signal handling.