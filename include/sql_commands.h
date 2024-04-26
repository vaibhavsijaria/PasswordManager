#define CREATE_USER_TABLE                                                                          \
  "CREATE TABLE IF NOT EXISTS users ("                                                             \
  "id INTEGER PRIMARY KEY AUTOINCREMENT, "                                                         \
  "username TEXT NOT NULL, "                                                                       \
  "hash TEXT NOT NULL, "                                                                           \
  "salt TEXT NOT NULL, "                                                                           \
  "UNIQUE(username));"

#define CREATE_SERVICE_TABLE                                                                       \
  "CREATE TABLE IF NOT EXISTS services ("                                                          \
  "id INTEGER PRIMARY KEY AUTOINCREMENT, "                                                         \
  "user_id INTEGER NOT NULL, "                                                                     \
  "service_name TEXT NOT NULL, "                                                                   \
  "username TEXT NOT NULL, "                                                                       \
  "password TEXT NOT NULL, "                                                                       \
  "FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE);"

#define CREATE_USER "INSERT INTO users(username, hash, salt) VALUES('%s', '%s', '%s');"

#define DELETE_USER "DELETE FROM users WHERE username = ?;"

#define GET_PWD "SELECT id ,hash, salt FROM %s WHERE username = ?;"

#define GET_SERVICE "SELECT * FROM services WHERE user_id = %d;"

#define CREATE_SERVICE                                                                             \
  "INSERT INTO services(user_id, service_name, username, password) "                               \
  "VALUES (%d, '%s', '%s', '%s');"

#define DELETE_SERVICE "DELETE FROM services WHERE user_id = ? AND service_name = ?;"
