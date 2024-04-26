#include "crypto.h"
#include "db_connection.h"
#include "db_create.h"
#include "db_users.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_NAME "test.db"
#define STR_SIZE 64
#define KEY "awA43^gZ4$KdqwyNV!7$GF&%sLAo3WTf"

int main()
{
  sqlite3* db = NULL;
  User* user = NULL;
  if(openDb(DB_NAME, &db) && createTable(db))
  {
    while(1)
    {
      if(!user)
      {
        printf("Enter 1 to login, 2 to create new account\n");

        char* username = malloc(STR_SIZE);
        char* password = malloc(STR_SIZE);
        int choice;

        scanf("%d", &choice);
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if(choice == 1)
        {
          user = login(db, username, password, KEY);
        }
        else if(choice == 2)
        {
          user = create_user(db, username, password, KEY);
          break;
        }
      }
    }

    closeDb(&db);
  }
  return 0;
}