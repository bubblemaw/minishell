# Minishell

Minishell is a minimal shell written in C and inspired by `bash`. The project
implements command reading, parsing, and execution in an interactive terminal.

## Features

- interactive prompt with Readline history;
- execution of external commands found in `PATH`;
- arguments and options;
- pipes (`|`);
- redirections:
  - input (`<`);
  - output with overwrite (`>`);
  - output in append mode (`>>`);
  - heredoc (`<<`);
- single and double quotes;
- environment variable expansion;
- builtins:
  `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`;
- terminal signal handling.

## Target platform and prerequisites

The project is primarily designed for **Linux**, which is the target platform.
Signal handling uses `rl_replace_line()`, available in the expected Linux
Readline environment.

macOS is not the target platform and may require adaptations depending on the
Readline version provided by the system. Full compilation and support are
therefore not guaranteed on macOS.

- Linux (recommended platform);
- a C compiler compatible with `cc`;
- `make`;
- the Readline library (`libreadline`).

On Debian/Ubuntu, install the dependencies with:

```bash
sudo apt install build-essential libreadline-dev
```

On macOS, Readline can be installed with Homebrew, but macOS is not the main
target platform:

```bash
brew install readline
```

## Compilation

```bash
make
```

To remove generated files:

```bash
make clean
make fclean
```

To perform a full rebuild:

```bash
make re
```

## Usage

```bash
./minishell
```

Examples:

```bash
echo "hello world"
pwd
ls -la | grep minishell
echo "$HOME"
cat < input.txt > output.txt
cat << EOF
heredoc content
EOF
```

## Project structure

- `srcs/main/`: entry point and initialization;
- `srcs/tokken/`: tokenization and token validation;
- `srcs/token_to_cmd/`: conversion from tokens to commands;
- `srcs/cmd_parsing/`: executable lookup;
- `srcs/execution/`: command execution and pipe handling;
- `srcs/redirection/`: redirections and heredocs;
- `srcs/expansion/`: variables, quotes, and expansions;
- `srcs/builtin/`: builtin commands;
- `srcs/error_free/`: error handling and memory cleanup;
- `srcs/utils/`: utility functions and signal handling;
- `libft/`: custom C library;
- `GNL/`: line-reading functions;
- `inc/minishell.h`: main structures and prototypes.
