#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <sqlite3.h>
#include <stdbool.h>

bool openDb(const char* dbName, sqlite3** db);
bool closeDb(sqlite3** db);

#endif