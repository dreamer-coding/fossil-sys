/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_SYS_USER_H
#define FOSSIL_SYS_USER_H

#include <stdbool.h>
#include <stddef.h>

// Define the maximum length for usernames, passwords, etc.
#define FOSSIL_SYS_USER_MAX_LEN 256

#ifdef __cplusplus
extern "C" {
#endif

// Define structures for user accounts and credentials
typedef struct {
    char username[FOSSIL_SYS_USER_MAX_LEN];
    char password_hash[FOSSIL_SYS_USER_MAX_LEN];
    unsigned int privileges; // Bitmask for different privileges (e.g., admin, user, etc.)
} fossil_sys_user_account_t;

typedef struct {
    char username[FOSSIL_SYS_USER_MAX_LEN];
    char password[FOSSIL_SYS_USER_MAX_LEN];
} fossil_sys_user_credentials_t;

/**
 * @brief Creates a new user account.
 * 
 * @param account Pointer to the user account structure.
 * @return true if the account was created successfully, false otherwise.
 */
bool fossil_sys_user_create_account(const fossil_sys_user_account_t *account);

/**
 * @brief Deletes an existing user account.
 * 
 * @param username The username of the account to be deleted.
 * @return true if the account was deleted successfully, false otherwise.
 */
bool fossil_sys_user_delete_account(const char *username);

/**
 * @brief Updates an existing user account.
 * 
 * @param account Pointer to the user account structure with updated information.
 * @return true if the account was updated successfully, false otherwise.
 */
bool fossil_sys_user_update_account(const fossil_sys_user_account_t *account);

/**
 * @brief Retrieves information about a user account.
 * 
 * @param username The username of the account to retrieve.
 * @param account Pointer to the user account structure to be filled with account information.
 * @return true if the account information was retrieved successfully, false otherwise.
 */
bool fossil_sys_user_get_account(const char *username, fossil_sys_user_account_t *account);

/**
 * @brief Authenticates a user with given credentials.
 * 
 * @param credentials Pointer to the user credentials structure.
 * @return true if the authentication was successful, false otherwise.
 */
bool fossil_sys_user_authenticate(const fossil_sys_user_credentials_t *credentials);

/**
 * @brief Verifies the password of a user.
 * 
 * @param username The username of the account.
 * @param password The password to verify.
 * @return true if the password is correct, false otherwise.
 */
bool fossil_sys_user_verify_password(const char *username, const char *password);

/**
 * @brief Checks if a user has a specific privilege.
 * 
 * @param username The username of the account.
 * @param privilege The privilege to check.
 * @return true if the user has the privilege, false otherwise.
 */
bool fossil_sys_user_check_privilege(const char *username, unsigned int privilege);

/**
 * @brief Grants a specific privilege to a user.
 * 
 * @param username The username of the account.
 * @param privilege The privilege to grant.
 * @return true if the privilege was granted successfully, false otherwise.
 */
bool fossil_sys_user_grant_privilege(const char *username, unsigned int privilege);

/**
 * @brief Revokes a specific privilege from a user.
 * 
 * @param username The username of the account.
 * @param privilege The privilege to revoke.
 * @return true if the privilege was revoked successfully, false otherwise.
 */
bool fossil_sys_user_revoke_privilege(const char *username, unsigned int privilege);

#ifdef __cplusplus
}

#include <string>
#include <vector>

/**
 * C++ wrapper for the process management API.
 */
namespace fossil {

    /**
     * Process management utilities.
     */
    namespace sys {
        /**
         * Process management class.
         */
        class User {
        public:
            /**
             * Create a new user account.
             *
             * @param account The user account to create.
             * @return True if the account was created successfully, false otherwise.
             */
            bool create_account(const fossil_sys_user_account_t &account) {
                return fossil_sys_user_create_account(&account);
            }

            /**
             * Delete a user account.
             *
             * @param username The username of the account to delete.
             * @return True if the account was deleted successfully, false otherwise.
             */
            bool delete_account(const std::string &username) {
                return fossil_sys_user_delete_account(username.c_str());
            }

            /**
             * Update a user account.
             *
             * @param account The user account to update.
             * @return True if the account was updated successfully, false otherwise.
             */
            bool update_account(const fossil_sys_user_account_t &account) {
                return fossil_sys_user_update_account(&account);
            }

            /**
             * Get a user account by username.
             *
             * @param username The username of the account to retrieve.
             * @param account The account structure to populate.
             * @return True if the account was found, false otherwise.
             */
            bool get_account(const std::string &username, fossil_sys_user_account_t &account) {
                return fossil_sys_user_get_account(username.c_str(), &account);
            }

            /**
             * Authenticate a user based on credentials.
             *
             * @param credentials The user credentials to authenticate.
             * @return True if the user was authenticated, false otherwise.
             */
            bool authenticate(const fossil_sys_user_credentials_t &credentials) {
                return fossil_sys_user_authenticate(&credentials);
            }

            /**
             * Verify a user password (without actual authentication).
             *
             * @param username The username of the account to verify.
             * @param password The password to verify.
             * @return True if the password is correct, false otherwise.
             */
            bool verify_password(const std::string &username, const std::string &password) {
                return fossil_sys_user_verify_password(username.c_str(), password.c_str());
            }

            /**
             * Check if a user has a specific privilege.
             *
             * @param username The username of the account to check.
             * @param privilege The privilege to check.
             * @return True if the user has the privilege, false otherwise.
             */
            bool check_privilege(const std::string &username, unsigned int privilege) {
                return fossil_sys_user_check_privilege(username.c_str(), privilege);
            }

            /**
             * Grant a privilege to a user.
             *
             * @param username The username of the account to grant the privilege.
             * @param privilege The privilege to grant.
             * @return True if the privilege was granted, false otherwise.
             */
            bool grant_privilege(const std::string &username, unsigned int privilege) {
                return fossil_sys_user_grant_privilege(username.c_str(), privilege);
            }

            /**
             * Revoke a privilege from a user.
             *
             * @param username The username of the account to revoke the privilege.
             * @param privilege The privilege to revoke.
             * @return True if the privilege was revoked, false otherwise.
             */
            bool revoke_privilege(const std::string &username, unsigned int privilege) {
                return fossil_sys_user_revoke_privilege(username.c_str(), privilege);
            }

        };

    } // namespace sys

} // namespace fossil

#endif

#endif /* FOSSIL_SYS_PROCESS_H */
