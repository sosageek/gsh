#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

#include "config.h"

int check_malloc(void* addr){
    if(addr) return 0;
    pfatal("Dynamic memory error. Quitting execution.");
    exit(EXIT_FAILURE);
    /**
    *   IMPORTANT:
    *   
    *   THIS FUNCTION THROWS A FATAL ERROR AND QUITS THE EXECUTION AFTER A FAILED MALLOC.
    *
    *   PLEASE NOTE THAT MOST STRINGS IN THIS PROJECT ARE DINAMICALLY ALLOCATED.
    * 
    *   IF YOU EDIT THIS FUNCTION TO ALLOW EXECUTION TO CONTINUE AFTER A FAILED ALLOCATION,
    *   YOU MUST ENSURE THAT STATIC FALLBACK VALUES ARE AVAILABLE FOR ALL RELEVANT STRINGS.
    * 
    *   OTHERWISE, THE PROGRAM MAY DEREFERENCE NULL POINTERS AND EVENTUALLY CRASH.
    */
}

char* gsh_getcwd(void) {
    char* buffer;
    int buffer_size = PATH_MAX;

    while(TRUE) {
        buffer = malloc(buffer_size);
        check_malloc(buffer);

        if(getcwd(buffer, buffer_size)) return buffer;  // Copies cwd into buffer
        free(buffer);

        if (errno != ERANGE) return strdup("?");        // Fallback
        buffer_size = buffer_size + BUF_S;              // If the error is ERANGE -> retry with larger buffer
    }
}

/**
 *  TEXT OUTPUT FUNCTIONS
 * 
 *  NOTE: The "\033[0m" ANSI escape code resets all text formatting (color, background, etc.)
 *  The reset code is necessary to avoid leaking formatting into subsequent shell output.
 */

void pfatal(char* msg){
    fprintf(stderr, "\033[41mFatal: %s\033[0m\n", msg);
    /** 
     * ANSI escape codes used:
     * - "\033[41m" sets the background color to red
     * - reset code
     */
}

void perr(char* msg){
    fprintf(stderr, "\033[31mError: %s\033[0m\n", msg);
    /**
     * ANSI escape codes used:
     * - "\033[31m" sets the text color to red
     * - reset code
     */
}

void perr_errno(const char* context){
    fprintf(stderr, "\033[31mError: %s: %s\033[0m\n", context, strerror(errno));
}

void pwarn(char* msg){
    printf("\033[33mWarning: %s\033[0m\n", msg);
    /**
     * ANSI escape codes used:
     * - "\033[33m" sets the text color to yellow
     * - reset code
     */
}

void psucc(char* msg){
    printf("\033[32mSuccess: %s\033[0m\n", msg);
    /**
     * ANSI escape codes used:
     * - "\033[32m" sets the text color to green
     * - reset code
     */
}
