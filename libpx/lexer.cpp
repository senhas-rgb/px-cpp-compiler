#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include "lexer.hpp"


Lexer::Lexer(const std::string& input) : source(input), start(0), current(0), line(1), column(1) {}

// lexer class skeleton
Token Lexer::nextToken() {
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

  bool Lexer::isAtEnd() {
    return current >= source.size();
  }

  // moving forward one token
  char Lexer::advance() {
    column++;
    return source[current++];
  }

  // look next token without moving
  char Lexer::peek() {
    if (current >= source.size()) {
      return '\0';
    }
    return source[current];
  }

  // consume character if known
  bool Lexer::match(char expected) {
    if (peek() != expected) {
      return false;
    }
    current++;
    column++;
    return true;
  }

  // skip whitespace
  void Lexer::skipWhitespace() {
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


// read string from file
std::string readFile(const std::string& filename) {
  std::ifstream file(filename);
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return content;
}

int lexer(const std::string& filename) {
  std::string source = readFile(filename);
  if (source.empty()) {
	return 1;
  }

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
