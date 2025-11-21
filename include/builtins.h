#ifndef BUILTINS_H
#define BUILTINS_H

/**
 * @typedef builtinc_t
 * 
 * @brief Structure representing a built-in shell command.
 *
 * This struct defines the interface and metadata for a built-in command in the shell.
 * Each entry includes the command name, a pointer to the function implementing it,
 * a short description for the help screen, and an example of usage.
 *
 * It is typically used to populate the `builtins[]` array and enables the shell to:
 * 
 * - dispatch the correct built-in function at runtime
 * 
 * - generate help documentation automatically
 *
 * Fields:
 * 
 * - `command`     The name of the built-in command (e.g., "cd", "exit").
 * 
 * - `function`    Pointer to the function implementing the command. 
 *                 All functions must match the signature: `int f(char** args)`.
 * 
 * - `description` A brief description of the command’s purpose.
 * 
 * - `use`         An example showing how to use the command in the shell.
 */
typedef struct builtinc{
    const char* command;
    int (*function)(char** args);
    const char* description;
    const char* use;
} builtinc_t;

/**
 * @brief Displays information about the shell.
 *
 * Prints the application name (`APPNAME`), version (`VERSION`, `VERSION_NAME`), and author 
 * details (`AUTHOR_NAME`, `AUTHOR_LINK`). Typically shown as part of the help screen.
 * 
 * All the constant values printed are defined into `config.h`.
 *
 * @return `int` Returns `SHELL_RUN` to continue shell execution.
 */
int gsh_hello_screen(char** args);

/**
 * @brief Changes the current working directory.
 *
 * Implements the behavior of the `cd` shell command.
 * 
 *  - If no argument is provided, prints an error via `perr()`.
 * 
 *  - If `chdir()` fails, displays the corresponding `errno` message
 *    via `perr_errno("cd")`.
 *
 * This command never terminates the shell; it only affects the
 * process' working directory.
 *
 * @param args Argument vector, where `args[1]` is the target directory.
 * @return `int` Always returns `SHELL_RUN`.
 */
int gsh_cd(char** args);

/**
 * @brief Displays help for built‑in commands.
 *
 * Behavior summary:
 * 
 *  - `help` with no arguments shows a formatted list of all built‑ins.
 * 
 *  - `help <command>` prints extended help for a specific built‑in.
 * 
 *  - Extra arguments generate a warning but execution continues.
 * 
 *  - Unknown commands produce an error before showing the generic help list.
 *
 * The command descriptions and usage examples are taken directly
 * from the `builtins[]` table, keeping documentation centralized.
 *
 * @param args Argument vector passed from the parser.
 * 
 *             - `args[0]` is always `"help"`
 * 
 *             - `args[1]` may be `NULL` or a command name
 * 
 * @return `int` Always returns `SHELL_RUN`.
 */
int gsh_help(char** args);

/**
 * @brief Requests termination of the shell.
 *
 * Returning `SHELL_QUIT` causes the main shell loop to terminate,
 * cleanly ending execution.
 *
 * @param args Ignored. Kept for interface consistency.
 * 
 * @return `int` Always returns `SHELL_QUIT`.
 */
int gsh_exit(char** args);

/**
 * @brief Table of all built‑in shell commands.
 *
 * This array defines:
 * 
 *  - the textual command users can type (e.g., `cd`)
 * 
 *  - the C function that implements the built‑in
 * 
 *  - a short human‑readable description
 * 
 *  - a usage example displayed by the `help` command
 *
 * The structure type `builtinc_t` is defined in `builtins.h`.
 * New built‑ins can be added simply by appending to this list.
 */
extern builtinc_t builtins[];

/**
 * @brief Returns the number of built‑in commands defined in `builtins[]`.
 *
 * The size is computed at runtime using `sizeof`, ensuring it automatically
 * adapts if new built‑ins are added or removed.
 *
 * @return `int` Number of elements in the `builtins[]` table.
 */
int num_builtins(void);

#endif
