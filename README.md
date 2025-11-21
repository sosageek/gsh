# > gsh - made a shell just for the fun of it

A small shell for UNIX-like systems written in C with POSIX APIs, which I made for fun and learning purposes.
I may keep improving it if I feel like it.

[![version](https://img.shields.io/badge/version-0.1.0-informational)]()


## Features

- Minimal  REPL (read-eval-print loop)
- A few built-in commands:
  - `cd`
  - `help`
  - `info`
  - `exit`, `quit`
- Executes external programs (via `fork` + `execvp`)
- Colored and dynamic prompt (user@host + cwd)
- Easy to extend with new built-ins


## Build

You can compile `gsh` using `make`:

```bash
make
```

To run the shell:

```bash
./gsh
```

To clean the project:

```bash
make clean
```

## Project structure

I tried to keep the project as modular and scalable as I could, but I genuinely feel that there is still a lot of room for improvement.
I am still searching for a cleaner way to reorganize this, although the current structure is more than acceptable.

```text
.
├── src/            # C source files
├── include/        # Header files
├── Makefile        # Build script
└── README.md       # The file you are currently reading
```

## Notes
`gsh` runs on terminal environments (GNU/Linux, macOS, ...) and assumes POSIX compliance. If you really like it and want to launch it with a double click, first consider using an actual good shell. If after that you are still willing to use `gsh`, then consider using a wrapper script or `.desktop` file.

This project was built just for fun and learning purposes. No license, no support - do whatever you want with it.
If you want to contribute, go ahead and pull the code, hack on it, and send patches if you feel like it. You can reach me at my [email](mailto:gabrielelobello@outlook.com).

`gsh` stands for Gangstas' SHell.
