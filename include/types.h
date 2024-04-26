#ifndef TYPES_H
#define TYPES_H

typedef struct
{
  char* hash;
  char* salt;
  int user_id;
} PasswordData;

typedef struct
{
  // char* username;
  // char* password;
  int user_id;
} User;

#endif