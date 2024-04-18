#ifndef DB_CREATE_H
#define DB_CREATE_H

#include <sqlite3.h>
#include <stdbool.h>

// bool table_exists(sqlite3* db, const char* table_name);
bool createTable(sqlite3* db);
bool create_user(sqlite3* db, const char* username, const char* hash, const char* salt);
bool create_service(sqlite3* db, int user_id, const char* username, const char* service_name,
                    const char* hash, const char* salt);
bool delete_user(sqlite3* db, const char* username);
bool delete_service(sqlite3* db, int user_id, const char* service_name);

#endif