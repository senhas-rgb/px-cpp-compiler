#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>


// defining token types and token

enum class TokenType {
  LET, IDENTIFIER, EQUAL, NUMBER, SEMICOLON, EOF_TOKEN
};

struct Token {
  TokenType type;
  std::string lexeme;
  int line;
  int column;
};


// lexer class skeleton
class Lexer {
private: 
  std::string source;
  size_t start = 0;
  size_t current = 0;
  int line = 1;
  int column = 1;

public:
  Lexer(const std::string& input) : source(input) {}
  Token nextToken();

private:
  // moving forward one token
  char advance() {
    column++;
    return source[current++];
  }

  // look next token without moving
  char peek() {
    if (current >= source.size()) {
      return '\0';
    }
    return source[current];
  }

  // consume character if known
  bool match(char expected) {
    if (peek() != expected) {
      return false;
    }
    current++;
    column++;
    return true;
  }

  // skip whitespace
  void skipWhitespace() { 
    while (true) {
      char c = peek();
      if (c == ' ' || c == '\r' || c == '\t') {
        advance();
      } else if (c == '\n') {
        line++;
        column = 1;
        advance();
      } else {
        break;
      }
    }
  }

};

// read string from file
std::string readFile(const std::string& filename) {
  std::ifstream file(filename);
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return content;
}

// tokenizing input
// todo


// running the lexer
int main() {
  return 0;
}
