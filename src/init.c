#include "init.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pwd.h>

#include "utils.h"

int getuserinfo(user_t* user){
    int exit_code = RETRIEVED;
    int buffer_size = BUF_S;
    char host_buffer[buffer_size];  // Small buffer to store the hostname

    // Retrieve the passwd entry for the current user
    struct passwd* pw = getpwuid(getuid());

    user->username = (pw && pw->pw_name) ? strdup(pw->pw_name) : NULL;

    // If username could not be retrieved, set error code NOUSER_ERR and fallback username 'user'
    if(user->username == NULL){
        exit_code = NOUSER_ERR;
        user->username = strdup(DEFAULT_USER);  // Fallback username
        /*
        * check_malloc() currently terminates the program (via exit)
        * if the memory allocation fails.
        * 
        * WARNING: If check_malloc() is ever modified to allow execution to continue,
        * and user->username remains NULL, the program may later crash.
        * In that case, a static fallback like:
        *     user->username = DEFAULT_USER;
        * should be added to avoid undefined behavior.
        */
        check_malloc(user->username);
    }

    // Try to get the system hostname
    if(gethostname(host_buffer, buffer_size) == -1){
        // If username already failed, return NOINFO_ERR; otherwise NOHOSTN_ERR
        exit_code = (exit_code == NOUSER_ERR) ? NOINFO_ERR : NOHOSTN_ERR;
        strncpy(host_buffer, DEFAULT_HOST, buffer_size);  // Fallback hostname
        host_buffer[BUF_S - 1] = '\0';
    }

    // Trim hostname at the first dot (remove domain part if present)
    char* dot = strchr(host_buffer, '.');
    if (dot) *dot = '\0';

    // Copy hostname into user struct, ensuring null-termination
    user->hostname = strdup(host_buffer);
    check_malloc(user->hostname);

    // Store the current timestamp
    user->timestamp = time(NULL);

    return exit_code;
}
