#ifndef DB_USERS_H
#define DB_USERS_H

#include "types.h"
#include <sqlite3.h>

PasswordData* get_password(sqlite3* db, const char* table, const char* username);
User* login(sqlite3* db, char* username, char* password, char* key);
#endif