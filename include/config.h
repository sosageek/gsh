#ifndef CONFIG_H
#define CONFIG_H

#define AUTHOR_NAME "Gabriele Lobello"
#define AUTHOR_LINK "https://github.com/sosageek"

#define VERSION         "0.1.0"
#define VERSION_NAME    "early dev"
#define APPNAME         "gsh"

// Buffer sizes
#define BUF_XS  64      // Smallest buffer
#define BUF_S   128     // Small buffer
#define BUF_M   512     // Medium buffer
#define BUF_L   1024    // Large buffer

#define TRUE    1
#define FALSE   0

// Shell loop control
#define SHELL_RUN   1
#define SHELL_QUIT  0

// User context structure used across the shell for prompt personalization
typedef struct user {
    char* username;  // Dynamically allocated username string
    char* hostname;  // Dynamically allocated hostname string
    long timestamp;  // UNIX timestamp of session start
} user_t;

#endif
