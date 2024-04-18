#include "db_create.h"
#include "sql_commands.h"
#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>

// if table exists, then exist variable is set to true
// static int callback(void* exists, int argc, char** argv, char** azColName)
// {
//   *(bool*)exists = true;
//   return 0;
// }

// bool table_exists(sqlite3* db, const char* table_name)
// {
//   char* errMsg = 0;
//   bool exists = false;
//   char sql[256];
//   snprintf(sql, sizeof(sql), "SELECT name FROM sqlite_master WHERE type='table' AND name='%s';",
//            table_name);

//   int rc = sqlite3_exec(db, sql, callback, &exists, &errMsg);
//   if(rc != SQLITE_OK)
//   {
//     printf("SQL error: %s\n", errMsg);
//     sqlite3_free(errMsg);
//   }

//   return exists;
// }

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
    printf("Created 'users' table or it already exist\n");
  }

  if(sqlite3_exec(db, CREATE_SERVICE_TABLE, 0, 0, &errMsg) != SQLITE_OK)
  {
    printf("SQL error: %s\n", errMsg);
    sqlite3_free(errMsg);
    success = false;
  }
  else
  {
    printf("Created 'services' table or it already exist\n");
  }

  return success;
}

bool create_user(sqlite3* db, const char* username, const char* hash, const char* salt)
{
  bool success = true;
  char* err_msg = 0;
  char sql[256];
  sprintf(sql, CREATE_USER, username, hash, salt);
  int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    success = false;
  }
  else
  {
    printf("User '%s' created successfully", username);
  }

  return success;
}

bool create_service(sqlite3* db, int user_id, const char* username, const char* service_name,
                    const char* hash, const char* salt)
{
  bool success = true;
  char* err_msg = 0;
  char sql[256];
  sprintf(sql, CREATE_SERVICE, user_id, service_name, username, hash, salt);
  int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    success = false;
  }
  else
  {
    printf("Service '%s' created successfully", service_name);
  }

  return success;
}

bool delete_user(sqlite3* db, const char* username)
{
  sqlite3_stmt* stmt;
  const char* sql = DELETE_USER;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if(rc != SQLITE_OK)
  {
    fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
    return false;
  }

  sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);

  if(rc != SQLITE_DONE)
  {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    return false;
  }

  sqlite3_finalize(stmt);

  return true;
}

bool delete_service(sqlite3* db, int user_id, const char* service_name)
{
  sqlite3_stmt* stmt;
  const char* sql = DELETE_SERVICE;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

  if(rc != SQLITE_OK)
  {
    fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
    return false;
  }

  sqlite3_bind_int(stmt, 1, user_id);
  sqlite3_bind_text(stmt, 2, service_name, -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);

  if(rc != SQLITE_DONE)
  {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    return false;
  }

  sqlite3_finalize(stmt);

  return true;
}