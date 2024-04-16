#include "db_connection.h"
#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>

bool openDb(const char* dbName, sqlite3** db)
{
  bool success = true;

  int rc = sqlite3_open(dbName, db);

  if(rc == SQLITE_OK)
  {
    printf("Database %s opened!\n", dbName);
    char* errMsg = 0;
    rc = sqlite3_exec(*db, "PRAGMA foreign_keys = ON;", 0, 0, &errMsg);
    if(rc != SQLITE_OK)
    {
      printf("SQL error: %s\n", errMsg);
      sqlite3_free(errMsg);
      success = false;
    }
  }
  else
  {
    printf("Error in opening connection to database %s\n%s\n", dbName, sqlite3_errmsg(*db));
    closeDb(db);
    success = false;
  }
  return success;
}

bool closeDb(sqlite3** db)
{
  bool success = true;

  if(*db != NULL)
  {
    int rc = sqlite3_close(*db);

    if(rc == SQLITE_OK)
    {
      printf("Database closed successfully!\n");
      *db = NULL;
    }
    else
    {
      printf("Error in closing connection to database\n%s\n", sqlite3_errmsg(*db));
      success = false;
    }
  }
  else
  {
    printf("Database connection is already NULL\n");
    success = false;
  }
  return success;
}