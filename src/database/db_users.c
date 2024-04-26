#include "db_users.h"
#include "crypto.h"
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
  pwdData->user_id = sqlite3_column_int(stmt, 0);
  pwdData->hash = strdup((char*)sqlite3_column_text(stmt, 1));
  pwdData->salt = strdup((char*)sqlite3_column_text(stmt, 2));

  sqlite3_finalize(stmt);

  return pwdData;
}

User* login(sqlite3* db, char* username, char* password, char* key)
{
  CryptoUtils* crypto = CryptoUtils_init();
  PasswordData* pwdData = get_password(db, "users", username);
  char* temp = pwdData->hash;
  pwdData->hash = hex_to_bin(pwdData->hash);
  bool loggedIn = CryptoUtils_verifyData(crypto->mdctx, password, pwdData->hash, key);
  free(temp);
  free(pwdData->salt);
  CryptoUtils_cleanup(crypto);

  if(loggedIn)
  {
    printf("Logged in to %s account\n", username);
    User* user = malloc(sizeof(User));
    user->user_id = pwdData->user_id;
    free(pwdData);
    return user;
  }
  else
  {
    printf("Password does not match\n");
    free(pwdData);
    return NULL;
  }
}

bool print_header = true;

int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
  int i;
  if(print_header)
  {
    for(i = 0; i < argc; i++)
    {
      printf("%s\t", azColName[i]);
    }
    printf("\n");
    print_header = false;
  }
  for(i = 0; i < argc; i++)
  {
    printf("%s\t", argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

void list_services(sqlite3* db, int user_id)
{
  char* zErrMsg = 0;
  int rc;
  char sql[256];

  sprintf(sql, GET_SERVICE, user_id);

  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

  if(rc != SQLITE_OK)
  {
    printf("SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  print_header = true;
}