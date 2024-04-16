#include "db_connection.h"
#include "db_create.h"
#include "db_users.h"
#include "types.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  sqlite3* db = NULL;
  if(openDb("test.db", &db))
  {
    if(createTable(db))
    {
      if(create_user(db, "vaibhav", "hash", "salt"))
      {
      }
      if(create_service(db, 1, "buddha404", "cocaine.ninja", "hash", "salt"))
      {
      }
      // PasswordData* temp = get_password(db, "services", "buddha404");
      // printf("%s\n%s", temp->hash, temp->salt);
      delete_user(db, "vaibhav");
    }
  }
}