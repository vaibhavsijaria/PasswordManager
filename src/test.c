#include "crypto.h"
#include "db_connection.h"
#include "db_create.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool create_user(sqlite3* db, const char* username, const char* hash, const char* salt);
bool create_service(sqlite3* db, int user_id, const char* username, const char* service_name,
                    const char* hash, const char* salt);

int main()
{
  const char* dbName = "test.db";
  sqlite3* db;

  if(!openDb(dbName, &db))
  {
    printf("Failed to open database\n");
    return 1;
  }

  createTable(db);

  char username[256];
  char password[256];
  char serviceName[256] = "ExampleService";
  printf("Enter username: ");
  scanf("%255s", username);
  printf("Enter password: ");
  scanf("%255s", password);

  CryptoUtils* crypto = CryptoUtils_init();
  const char* salt = "123456789";
  Hash hashedPassword = CryptoUtils_hashData(crypto->mdctx, password, salt);

  char hexHash[65];
  for(int i = 0; i < EVP_MD_size(EVP_sha256()); i++)
    printf(&hexHash[i * 2], "%02x", (unsigned char)hashedPassword[i]);

  if(!create_user(db, username, hexHash, salt))
  {
    printf("Failed to create user\n");
  }
  if(!create_service(db, 1, username, serviceName, hexHash, salt))
  {
    printf("Failed to create service\n");
  }

  free(hashedPassword);
  CryptoUtils_cleanup(crypto);
  closeDb(&db);

  return 0;
}