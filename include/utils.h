#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Verifies that a memory allocation was successful.
 *
 * @param addr Pointer returned by a malloc-like function.
 * 
 * @return `0` if allocation was successful.
 * 
 * @note If the pointer is `NULL`, this function prints a fatal error and terminates the program.
 */
int check_malloc(void* addr);

/**
 * @brief Dynamically retrieves the current working directory.
 * 
 * This function attempts to allocate a buffer large enough to store the full
 * current working directory path. It handles `ERANGE` errors by progressively
 * increasing the buffer size until success or until another error occurs.
 * 
 * @return `char*` A dynamically allocated string containing the current working
 *         directory. Must be freed by the caller. Returns a fallback value if an
 *         error other than `ERANGE` occurs.
 */
char* gsh_getcwd(void);

/**
 * @brief Prints a fatal error message.
 *
 * @param msg The fatal error message to display.
 * 
 * @note The output format is `"Fatal: <msg>"` with red background (with ANSI escape codes)
 * and a newline at the end.
 */
void pfatal(char* msg);

/**
 * @brief Prints an error message.
 *
 * @param msg The error message to display.
 * 
 * @note The output format is `"Error: <msg>"` with red text (with ANSI escape codes)
 * and a newline at the end.
 */
void perr(char* msg);

/**
 * @brief Prints a warning message.
 *
 * @param msg The warning message to display.
 * 
 * @note The output format is `"Warning: <msg>"` with yellow text (with ANSI escape codes)
 * and a newline at the end.
 */
void pwarn(char* msg);

/**
 * @brief Prints a success message.
 *
 * @param msg The success message to display.
 * 
 * @note The output format is `"Success: <msg>"` with green text (with ANSI escape codes)
 * and a newline at the end
 */
void psucc(char* msg);

/**
 * @brief Prints an error message in red using the current value of `errno`.
 *
 * This function outputs a formatted error message to `stderr`, including:
 * 
 * - a custom context string (e.g., the name of the command or operation),
 * 
 * - the string description of the current `errno` value (from `strerror()`).
 *
 * The output is colored red using ANSI escape sequences for better visibility.
 *
 * @param context A string indicating where or in what context the error occurred.
 */
void perr_errno(const char* context);

#endif
