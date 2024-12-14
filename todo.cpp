#include "headers/dbLinker.h"
#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <string>
#include <vector>

void showHelp();
int addTask(DBLinker &db, int argc, char *argv[]);
void listTask(DBLinker &db);
int deleteTask(DBLinker &db, int argc, char *argv[]);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: ./todo <command> [options]" << std::endl;
    std::cout << "For help: ./todo --help" << std::endl;
    return 1;
  }

  std::string command = argv[1];

  DBLinker db;

  if (db.connectToDB()) {
    db.executeQuery("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, "
                    "name TEXT NOT NULL, priority INTEGER NOT NULL, done "
                    "TEXT NOT NULL DEFAULT 'NOT DONE');",
                    {});
  }

  if (command == "--help" || command == "-h") {
    showHelp();
  } else if (command == "add") {
    addTask(db, argc, argv);
  } else if (command == "list") {
    listTask(db);
  } else if (command == "delete") {
    deleteTask(db, argc, argv);
  } else {
    std::cout << "Unknown command: " << command << std::endl;
  }

  return 0;
}

void showHelp() {
  std::cout << "Usage: ./todo <command> [options]" << std::endl;
  std::cout << "<command>" << std::endl;
  std::cout << "  add" << std::endl;
  std::cout << "  list" << std::endl;
  std::cout << "  delete" << std::endl;
  std::cout << "[options]" << std::endl;
  std::cout << "  -h  --help      shows this page" << std::endl;
  std::cout << "  -p  --priority  set priority" << std::endl;
}

int addTask(DBLinker &db, int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Error: Please specify a task to add." << std::endl;
    return 1;
  }
  std::string task = argv[2];

  std::string priority = "0";
  if (argc > 3) {
    if (strcmp(argv[3], "-p") || strcmp(argv[3], "--priority")) {
      std::string priority = argv[4];
    }
  }

  std::string query =
      "INSERT INTO tasks (name, priority, done) VALUES (?, ?, ?);";
  std::vector<std::string> values = {task, priority, "NOT DONE"};

  if (db.executeQuery(query, values)) {
    std::cout << "Task added successfully." << std::endl;
  } else {
    std::cout << "Failed to add task." << std::endl;
  }

  return 0;
}

void listTask(DBLinker &db) {
  std::cout << "Listing all tasks..." << std::endl;
  db.listTasks();
}

int deleteTask(DBLinker &db, int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Error: Please specify a task to delete." << std::endl;
    return 1;
  }
  std::string taskNum = argv[2];
  std::cout << "Deleting task number: " << taskNum << std::endl;

  std::string query = "DELETE FROM tasks WHERE id = ?;";
  std::vector<std::string> values = {taskNum};

  if (db.executeQuery(query, values)) {
    std::cout << "Task deleted successfully." << std::endl;
  } else {
    std::cout << "Failed to delete task." << std::endl;
  }

  return 0;
}
