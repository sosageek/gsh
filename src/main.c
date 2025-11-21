#include <stdlib.h>

#include "config.h"
#include "utils.h"
#include "init.h"
#include "loop.h"

int main(void){
    // ============== INIT ==============
    user_t* user = (user_t*)malloc(sizeof(user_t));
    check_malloc(user);

    // Retrieve username, hostname and timestamp
    int user_info_status = getuserinfo(user);

    // Display warnings depending on what failed
    if(user_info_status == NOUSER_ERR)
        pwarn("gsh: could not retrieve actual username. Using default username instead.");
    if(user_info_status == NOHOSTN_ERR)
        pwarn("gsh: could not retrieve actual hostname. Using default hostname instead.");
    if(user_info_status == NOINFO_ERR)
        pwarn("gsh: could not retrieve actual user info. Using default user info instead.");
    
    // ========== COMMAND LOOP ===========
    gsh_loop(user);

    // ========= CLEANUP ON EXIT =========
    free(user->username);
    free(user->hostname);
    free(user);
    
    return EXIT_SUCCESS;
}
