#include <iostream>
#include <string>
#include "../libpx/lexer.hpp"

void showHelp() {} // todo

void runPrompt() {
  std::string line;
  std::cout << "pLang: ";
  while (std::getline(std::cin, line)) {
    std::cout << "pLang: ";
    if (line == "help") {
      showHelp();
    } else if (line == "exit()") {
      std::cout << "Exiting...\n";
      exit(0);
    }
  }
}

int main (int argc, char *argv[]) {
  
  if (argc > 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 64;
  } else if (argc == 2) {
    lexer(std::string(argv[1]));
  } else {
    runPrompt();
  }

  return 0;
}
