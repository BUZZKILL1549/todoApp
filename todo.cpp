#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: ./todo <command> [options]" << std::endl;
    std::cout << "For help: ./todo --help" << std::endl;
    return 1;
  }

  std::string command = argv[1];

  if (command == "--help" || command == "-h") {
    std::cout << "Usage: ./todo <command> [options]" << std::endl;
    std::cout << "<command>" << std::endl;
    std::cout << "  add\n  list\n  delete" << std::endl;
    std::cout << "[options]" << std::endl;
    std::cout
        << "  -h  --help      shows this page\n  -p  --priority  sets priority"
        << std::endl;
  } else if (command == "add") {
    if (argc < 3) {
      std::cout << "Error: Please specify a task to add." << std::endl;
      return 1;
    }
    std::string task = argv[2];
    std::cout << "Adding task: " << task << std::endl;
  } else if (command == "list") {
    std::cout << "Listing all tasks..." << std::endl;
  } else if (command == "delete") {
    if (argc < 3) {
      std::cout << "Error: Please specify a task to delete." << std::endl;
      return 1;
    }
    int taskNum = std::stoi(argv[2]);
    std::cout << "Deleting task number: " << taskNum << std::endl;
  } else {
    std::cout << "Unknown command: " << command << std::endl;
  }

  return 0;
}
