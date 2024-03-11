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

#define CREATE_USER "INSERT INTO users(username, master_password) VALUES('%s', '%s');"

#define DELETE_USER "DELETE FROM users WHERE username = ?;"

#define GET_PWD "SELECT master_password FROM users WHERE username = ?;"