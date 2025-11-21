#ifndef LOOP_H
#define LOOP_H

#include "config.h"

/**
 * @brief Main execution loop of the shell.
 *
 * This function runs the core REPL (Read-Eval-Print Loop) of the shell.
 * It assumes that the `user_t` struct has already been initialized and populated
 * by the caller (e.g., in main, via `getuserinfo()`).
 *
 * @param user Pointer to a pre-filled `user_t` struct containing:
 * 
 *  - `username`: the shell username to display in the prompt
 * 
 *  - `hostname`: the hostname to display in the prompt
 * 
 *  - `timestamp`: the session start time
 *
 * Responsibilities:
 * 
 * - Display the prompt in the format: `<username>\@<hostname> $ `.
 * 
 * - Read input lines from the user.
 * 
 * - Parse the input into arguments.
 * 
 * - Execute the corresponding shell command.
 * 
 * - Repeat until a termination condition is met.
 * 
 * - Clean up all dynamically allocated input buffers and arguments.
 *
 * @note The `user` pointer must not be `NULL` and should be freed by the caller.
 */
void gsh_loop(user_t* user);

#endif
