#include "db_connection.h"
#include "db_users.h"
#include "sql_commands.h"
#include "types.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    sqlite3* db;
    const char* dbName = "test.db";

    // Open database
    if (!openDb(dbName, &db)) {
        fprintf(stderr, "Failed to open database\n");
        return 1;
    }

    // Create tables
    if (!createTable(db)) {
        fprintf(stderr, "Failed to create tables\n");
        closeDb(&db);
        return 1;
    }

    // Create user
    const char* username = "testuser";
    const char* password = "password123";
    const char* salt = "random_salt";

    // Example function to hash a password (placeholder)
    char* hashedPassword = strdup("hashed_version_of_password123"); // Replace with actual hash function

    if (!create_user(db, username, hashedPassword, salt)) {
        fprintf(stderr, "Failed to create user\n");
        free(hashedPassword);
        closeDb(&db);
        return 1;
    }
    free(hashedPassword);

    // Retrieve password data
    PasswordData* pwdData = get_password(db, "users", username);
    if (pwdData == NULL) {
        fprintf(stderr, "Failed to retrieve password\n");
        closeDb(&db);
        return 1;
    }

    printf("Retrieved password hash: %s\n", pwdData->hash);
    printf("Retrieved salt: %s\n", pwdData->salt);

    // Clean up password data
    free(pwdData->hash);
    free(pwdData->salt);
    free(pwdData);

    // Close database
    if (!closeDb(&db)) {
        fprintf(stderr, "Failed to close database\n");
        return 1;
    }

    printf("Database operations completed successfully.\n");
    return 0;
}