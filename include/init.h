#ifndef INIT_H
#define INIT_H

#include "config.h"

// Return codes for `getuserinfo`
#define RETRIEVED 0         // Successful retrieval
#define NOUSER_ERR -1       // Failed to retrieve username
#define NOHOSTN_ERR -2      // Failed to retrieve hostname
#define NOINFO_ERR -3       // Failed both username and hostname

// Default fallback values
#define DEFAULT_USER "user"
#define DEFAULT_HOST "host"

/**
 * @brief Populates a `user_t` struct with the current user's information.
 *
 * @param user Pointer to a `user_t` struct where information will be stored.
 *
 * This function fills the following fields of the user struct:
 * 
 * - `username`: fetched using `getpwuid(getuid())`, or set to `DEFAULT_USER` if unavailable.
 * 
 * - `hostname`: fetched using `gethostname()`, trimmed at the first dot if present.
 * 
 * - `timestamp`: current time obtained with `time(NULL)`.
 *
 * @return `int exit_code`:
 * 
 * - `0` if successful
 * 
 * - `NOUSER_ERR` if username allocation failed
 * 
 * - `NOHOSTN_ERR` if hostname could not be retrieved
 * 
 * - `NOINFO_ERR` if both username and hostname retrieval failed
 */
int getuserinfo(user_t* user);

#endif
