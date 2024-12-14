#include "dbLinker.h"
#include <iostream>

// constructor
DBLinker::DBLinker() : db(nullptr) {}

// destructor
DBLinker::~DBLinker() {
  if (db) {
    sqlite3_close(db);
  }
}

// Connect to database
bool DBLinker::connectToDB() {
  int rc = sqlite3_open("todo.db", &db);

  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return false;
  } else {
    return true;
  }
}

// Execute query
bool DBLinker::executeQuery(const std::string &query,
                            const std::vector<std::string> &values) {
  sqlite3_stmt *stmt = nullptr;

  int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db)
              << std::endl;
    return false;
  }

  // Bind values to the statement
  for (size_t i = 0; i < values.size(); i++) { // Changed to size_t
    // Check if the value can be converted to an integer
    try {
      int intValue = std::stoi(values[i]);
      rc = sqlite3_bind_int(stmt, static_cast<int>(i + 1),
                            intValue); // Cast i+1 to int for binding
    } catch (const std::invalid_argument &) {
      // If not an integer, bind as text
      rc = sqlite3_bind_text(stmt, static_cast<int>(i + 1), values[i].c_str(),
                             -1, SQLITE_TRANSIENT);
    }

    if (rc != SQLITE_OK) {
      std::cerr << "Failed to bind value at index " << i + 1 << ": "
                << sqlite3_errmsg(db) << std::endl;
      sqlite3_finalize(stmt);
      return false;
    }
  }

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);
  return true;
}

void DBLinker::listTasks() {
  std::string query = "SELECT id, name, priority, done FROM tasks;";

  // prepare statement
  sqlite3_stmt *stmt = nullptr;
  int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

  if (rc != SQLITE_OK) {
    std::cerr << "Failed to perpare statement: " << sqlite3_errmsg(db)
              << std::endl;
    return;
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    const char *name =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    int priority = sqlite3_column_int(stmt, 2);
    const char *done =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

    std::cout << "ID: " << id << ", Name: " << name
              << ", Priority: " << priority << ", Done: " << done << std::endl;
  }

  sqlite3_finalize(stmt);
}
