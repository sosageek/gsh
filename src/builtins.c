#include "builtins.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "utils.h"

builtinc_t builtins[] = {
    {"cd",      &gsh_cd,            "Changes current working directory.",               "'cd <dir>'"},
    {"help",    &gsh_help,          "Shows help screen for built-in functions.",        "'help <command>' or just 'help'"},
    {"exit",    &gsh_exit,          "Quits the shell. You can also use: quit.",         "'exit'"},
    {"quit",    &gsh_exit,          "Quits the shell. You can also use: exit.",         "'quit'"},
    {"info",    &gsh_hello_screen,  "Displays info about the program and the author.",  "'info'"}
};

int num_builtins(void){
    return sizeof(builtins) / sizeof(builtinc_t);
}

int gsh_hello_screen(char** args){
    printf("\t\033[96;1m>%s - made a shell just for the fun of it\033[0m\n", APPNAME);
    printf("\t>%s (\033[94;4m%s\033[0m)\n", AUTHOR_NAME, AUTHOR_LINK);
    printf("\t>currently running %s (%s)\n\n", VERSION, VERSION_NAME);

    return SHELL_RUN;
}

int gsh_cd(char** args){
    if(args[1] == NULL)            // Must provide at least one argument to cd
        perr("gsh: expected argument to 'cd'");
    
    else if(chdir(args[1]) != 0)   // Calls chdir, which returns 0 if everything went right
        perr_errno("cd");

    return SHELL_RUN;
}

int gsh_help(char** args){
    if (args[1] != NULL){ 
        if(args[2] != NULL)   // Warning if more args then expected
            pwarn("Usage: 'help <command>'. Trimmed input to first argument.");

        // ===== SPECIFIC BUILTIN COMMAND HELP =====
        for(int i = 0; i < num_builtins(); i++){
            if(strcmp(args[1], builtins[i].command) == 0){
                printf("$\t\033[92;1m%s\033[0m\t\t%s\n", builtins[i].command, builtins[i].description);
                printf("\t\033[4;1muse example:\033[0m\t%s\n\n", builtins[i].use);
                return SHELL_RUN;
            }
        }

        // =========== COMMAND NOT FOUND ===========
        perr("unknown command. Printing a list of all buit-in commands.");
    }

    // ============= GENERIC HELP ==============
    (void)gsh_hello_screen(NULL);
    printf("\033[1m>list of built-in commands\n\n\033[4;1m$\tcommand\t\tdescription\033[0m\n\n");

    for(int i = 0; i < num_builtins(); i++){
        printf("$\t\033[92;1m%-15s\033[0m%s\n", builtins[i].command, builtins[i].description);
        printf("\t\033[4;1muse example:\033[0m\t%s\n\n", builtins[i].use);
    }

    return SHELL_RUN;
}

int gsh_exit(char** args){ return SHELL_QUIT; }
