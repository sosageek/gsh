#include "loop.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "utils.h"
#include "shell.h"

void gsh_loop(user_t* user) {
    char* cwd;      // Current working directory
    char* line;     // Raw input line entered by the user
    char** args;    // Tokenized argument array from the input line
    int status = SHELL_RUN;

    // ========== MAIN SHELL PROMPT LOOP ==========
    do {
        cwd = gsh_getcwd(); // Dynamically allocates the current working directory
        printf("%s@%s %s$ ", user->username, user->hostname, cwd); // Shell prompt

        line = gsh_readline();       // Read user input
        args = gsh_parse(line);      // Parse input into arguments
        status = gsh_execute(args);  // Execute built-in or external command

        // Free all dynamically allocated buffers
        free(line);
        free(args);
        free(cwd);
    } while (status);
}
