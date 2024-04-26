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
  int choice;

  if(openDb(DB_NAME, &db) && createTable(db))
  {
    char* username = malloc(STR_SIZE);
    char* password = malloc(STR_SIZE);
    while(1)
    {
      if(!user)
      {
        printf("Enter 1 to login, 2 to create new account, 3 to exit: ");

        scanf("%d", &choice);
        if(choice == 3)
        {
          break;
        }

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
        }
      }

      if(user)
      {
        printf("Enter 0 to logout, 1 to create new service, 2 to list out all services: ");
        scanf("%d", &choice);
        switch(choice)
        {
        case 0:
          user = NULL;
          continue;

        case 1:
          char* service_name = malloc(STR_SIZE);
          printf("Enter service name: ");
          scanf("%s", service_name);
          printf("Enter username: ");
          scanf("%s", username);
          printf("Enter password: ");
          scanf("%s", password);
          create_service(db, user->user_id, username, service_name, password);
          continue;

        case 2:
          list_services(db, user->user_id);

        default:
          break;
        }
      }
    }
    free(username);
    free(password);

    closeDb(&db);
  }
  return 0;
}