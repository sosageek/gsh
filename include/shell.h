#ifndef SHELL_H
#define SHELL_H

#define TOK_DELIM " \t\r\n\a"

/**
 * @brief Reads a line of input from `stdin` with basic line editing.
 *
 * This function implements a simple line reader for the shell,
 * supporting:
 * 
 * - Dynamic buffer resizing
 * 
 * - Backspace key handling (`127` or `\b`)
 * 
 * - Immediate character echoing
 *
 * @return A dynamically allocated string containing the user's input.
 *         The caller is responsible for freeing the returned buffer.
 */
char* gsh_readline(void);

/**
 * @brief Splits a command line into tokens using predefined delimiters.
 *
 * This function tokenizes the input string `line` using the delimiters defined
 * in `TOK_DELIM` and returns an array of strings.
 * Each token is a pointer into the original input string (no deep copies).
 *
 * The returned array is dynamically allocated and null-terminated.
 *
 * @param line Input string to parse (will be modified in-place).
 * 
 * @return `char** tokens` Array of token strings (null-terminated). Must be freed by the caller.
 */
char** gsh_parse(char* line);

/**
 * @brief Launches a new process to execute a command.
 *
 * This function forks the current process and uses `execvp()` to execute
 * the given command (via the `args` array) in the child process.
 * The parent waits for the command to terminate and returns its exit status.
 *
 * @param args Null-terminated array of argument strings, where `args[0]` is the command name.
 * 
 * @return `int`
 * 
 * - If the child process exits normally, returns its exit status (`WEXITSTATUS`).
 * 
 * - If the child is terminated by a signal or an error occurs, returns `EXIT_FAILURE`.
 */
int gsh_launch(char** args);

/**
 * @brief Executes a shell command (built-in or external). It's the main command dispatcher.
 *
 * It checks whether the input corresponds to a built-in command, and if so,
 * delegates execution to the appropriate function defined in the `builtins[]` array. 
 * If the command is not recognized as built-in, it is assumed to be an external
 * command and passed to `gsh_launch()` for execution.
 *
 * If the input is empty (`args[0] == NULL`), the shell does nothing and simply continues.
 *
 * @param args Null-terminated array of strings representing the parsed command and its arguments.
 *             e.g.: `{"cd", "/home", NULL}`
 *
 * @return `int` Status code indicating the result of the command execution:
 * 
 *         - `SHELL_RUN` to continue shell execution.
 * 
 *         - `SHELL_QUIT` to terminate the shell (used by `exit`, `quit`, etc.).
 * 
 *         - Any other value as defined by the called command function.
 */
int gsh_execute(char** args);

#endif
