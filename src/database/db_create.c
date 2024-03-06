#include "db_create.h"
#include "sql_commands.h"
#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>

// if table exists, then exist variable is set to true
static int callback(void* exists, int argc, char** argv, char** azColName)
{
  *(bool*)exists = true;
  return 0;
}

bool table_exists(sqlite3* db, const char* table_name)
{
  char* errMsg = 0;
  bool exists = false;
  char sql[256];
  snprintf(sql, sizeof(sql), "SELECT name FROM sqlite_master WHERE type='table' AND name='%s';",
           table_name);

  int rc = sqlite3_exec(db, sql, callback, &exists, &errMsg);
  if(rc != SQLITE_OK)
  {
    printf("SQL error: %s\n", errMsg);
    sqlite3_free(errMsg);
  }

  return exists;
}

bool createTable(sqlite3* db)
{
  char* errMsg = 0;
  bool success = true;

  if(sqlite3_exec(db, CREATE_USER_TABLE, 0, 0, &errMsg) != SQLITE_OK)
  {
    printf("SQL error: %s\n", errMsg);
    sqlite3_free(errMsg);
    success = false;
  }
  else
  {
    printf("Created 'users' table\n");
  }

  if(sqlite3_exec(db, CREATE_SERVICE_TABLE, 0, 0, &errMsg) != SQLITE_OK)
  {
    printf("SQL error: %s\n", errMsg);
    sqlite3_free(errMsg);
    success = false;
  }
  else
  {
    printf("Created 'services' table\n");
  }

  return success;
}