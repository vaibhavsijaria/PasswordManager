#ifndef DB_CREATE_H
#define DB_CREATE_H

#include "types.h"
#include <sqlite3.h>
#include <stdbool.h>

// bool table_exists(sqlite3* db, const char* table_name);
bool createTable(sqlite3* db);
User* create_user(sqlite3* db, const char* username, const char* password, const char* key);
bool create_service(sqlite3* db, int user_id, const char* username, const char* service_name,
                    const char* password);
bool delete_user(sqlite3* db, const char* username);
bool delete_service(sqlite3* db, int user_id, const char* service_name);

#endif