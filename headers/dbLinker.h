#ifndef DBLINKER_H
#define DBLINKER_H

#include <sqlite3.h>
#include <string>
#include <vector>

class DBLinker {
private:
  sqlite3 *db;

public:
  DBLinker();
  ~DBLinker();

  bool connectToDB();
  bool executeQuery(const std::string &query,
                    const std::vector<std::string> &values);
  void listTasks();
};

#endif // !DBLINKER_H
