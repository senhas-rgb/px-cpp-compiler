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
  Token nextToken() {
    skipWhitespace();

    int tokenline = line;
    int tokencolumn = column;

    if (isAtEnd()) {
      return {TokenType::EOF_TOKEN, "", tokenline, tokencolumn};
    }

    start = current;
    char c = advance();

    if (std::isalpha(c)) {
      while (std::isalnum(peek())) advance();
      std::string text = source.substr(start, current - start);
      if (text == "let") {
        return {TokenType::LET, text, tokencolumn, tokencolumn};
      }
      return {TokenType::IDENTIFIER, text, tokenline, tokencolumn};
    }

    if (std::isdigit(c)) {
      while (std::isdigit(peek())) advance();

      std::string number = source.substr(start, current - start);
      return {TokenType::NUMBER, number, tokenline, tokencolumn};
    }

    switch (c) {
      case '=': return {TokenType::EQUAL, "=", tokenline, tokencolumn};
      case ';': return {TokenType::SEMICOLON, ";", tokenline, tokencolumn};
      default:
                std::cerr << "Unexpected character: '" << c << "' at line " << line << ", column " << column << "\n";
                return nextToken();  // skip it
    }
  }

private:
  bool isAtEnd() {
    return current >= source.size();
  }

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

int main() {
  std::string source = readFile("source.txt");

  Lexer lexer(source);
  Token token;

  do {
    token = lexer.nextToken();
    std::cout << "Token: " << static_cast<int>(token.type)
      << ", Lexeme: '" << token.lexeme
      << "', Line: " << token.line
      << ", Column: " << token.column << "\n";
  } while (token.type != TokenType::EOF_TOKEN);

  return 0;
}
