#define CREATE_USER_TABLE                                                                          \
  "CREATE TABLE IF NOT EXISTS users ("                                                             \
  "id INTEGER PRIMARY KEY AUTOINCREMENT, "                                                         \
  "username TEXT NOT NULL, "                                                                       \
  "master_password TEXT NOT NULL, UNIQUE(username));"

#define CREATE_SERVICE_TABLE                                                                       \
  "CREATE TABLE IF NOT EXISTS services ("                                                          \
  "id INTEGER PRIMARY KEY AUTOINCREMENT, "                                                         \
  "user_id INTEGER NOT NULL, "                                                                     \
  "service_name TEXT NOT NULL, "                                                                   \
  "username TEXT NOT NULL, "                                                                       \
  "password TEXT NOT NULL, "                                                                       \
  "FOREIGN KEY(user_id) REFERENCES users(id));"