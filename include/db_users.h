#ifndef DB_USERS_H
#define DB_USERS_H

#include <sqlite3.h>

char* get_password(sqlite3* db, const char* username);

#endif