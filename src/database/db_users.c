#include "db_users.h"
#include "sql_commands.h"
#include "types.h"
#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PasswordData* get_password(sqlite3* db, const char* table, const char* username)
{
  sqlite3_stmt* stmt;
  char sql[256];
  sprintf(sql, GET_PWD, table);

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if(rc != SQLITE_OK)
  {
    fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
    return NULL;
  }

  sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);

  if(rc != SQLITE_ROW)
  {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
    return NULL;
  }

  PasswordData* pwdData = malloc(sizeof(PasswordData));
  pwdData->hash = strdup((char*)sqlite3_column_text(stmt, 0));
  pwdData->salt = strdup((char*)sqlite3_column_text(stmt, 1));

  sqlite3_finalize(stmt);

  return pwdData;
}