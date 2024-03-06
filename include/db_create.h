#ifndef DB_CREATE_H
#define DB_CREATE_H

#include <sqlite3.h>
#include <stdbool.h>

bool table_exists(sqlite3* db, const char* table_name);
bool createTable(sqlite3* db);

#endif