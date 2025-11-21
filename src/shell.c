#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "utils.h"
#include "builtins.h"

char* gsh_readline(void){
    int buffer_size = BUF_L;
    int position = 0;   // Current write position in buffer
    int character;      // Holds each character read
    /**
    *   NOTE: Keep `character` an int
    *   - getchar() returns an int
    *   - the EOF constant expands to -1
    */

    char* buffer = (char*)malloc(buffer_size);
    check_malloc(buffer);

    while(TRUE){
        character = getchar();          // Reads one single character from stdin

        // ========== BACKSPACE HANDLING ===========
        if(character == 127 || character == '\b') {
            if (position > 0){
                position--;
                printf("\b \b");        // Erases it visually from terminal
                fflush(stdout);         // Flushes output buffer
            }
            continue;
        }

        // ========== END OF LINE HANDLING ==========
        if(character == EOF || character == '\n'){
            buffer[position] = '\0';    // Null-terminate the string
            return buffer;
        }
        
        buffer[position++] = character; // Stores regular character

        // ==== BUFFER REALLOC IF SIZE EXCEEDED =====
        if(position >= buffer_size){
            buffer_size += BUF_S;       // Grow by BUF_S (safe chunking, avoid BUF_L)
            buffer = realloc(buffer, buffer_size);
            check_malloc(buffer);
        }
    }
}

char** gsh_parse(char* line){
    int buffer_size = BUF_XS;
    int position = 0;   // Current write position in tokens array

    char** tokens = (char**)malloc(buffer_size*sizeof(char*));  // Tokens array
    check_malloc((void*)tokens);
    char* token;

    token = strtok(line, TOK_DELIM);        // First token
    /**
     *  NOTE: STRTOK MODIFIES ITS FIRST ARGUMENT IN-LINE
     *  (replaces any delim defined in TOK_DELIM with '\0')
     *  IF YOU ARE WILLING TO REUSE THE ORIGINAL `line` LATER, YOU WILL NEED A COPY.
     */
    while(token != NULL){
        tokens[position] = token;           // Copy token into tokens array
        position++;

        // ==== BUFFER REALLOC IF SIZE EXCEEDED =====
        if(position >= buffer_size){
            buffer_size += BUF_XS;
            tokens = realloc(tokens, buffer_size*sizeof(char*));
            check_malloc(tokens);
        }

        token = strtok(NULL, TOK_DELIM);    // Get next token
    }

    tokens[position] = NULL;                // Null-terminated array of pointers
    return tokens;
}

int gsh_launch(char** args) {
    pid_t pid;
    int status;
    
    pid = fork();
    // ============= CHILD PROCESS ==============
    if (pid == 0) {
        if (execvp(args[0], args) == -1)
            perr_errno(args[0]);
        exit(EXIT_FAILURE);                 // Only reached if execvp fails
    }

    // ============= ERROR FORKING ==============
    else if (pid < 0)
        pfatal("gsh: could not create a new process and execute the command.");

    // ============= PARENT PROCESS =============
    else {
        do {
            (void)waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return SHELL_RUN;
}

int gsh_execute(char** args){
    if(args[0] == NULL)     // Empty command
        return SHELL_RUN;

    for(int i = 0; i < num_builtins(); i++){
        if(strcmp(args[0], builtins[i].command) == 0)
            return builtins[i].function(args);
    }

    return gsh_launch(args);
}
