#ifndef LEXER_HPP
#define LEXER_HPP


#include <string>

enum class TokenType {
  IDENTIFIER, EQUAL, NUMBER, SEMICOLON, EOF_TOKEN
};

struct Token {
  TokenType type;
  std::string lexeme;
  int line;
  int column;
};

class Lexer {
  private:
    std::string source;
    size_t start;
    size_t current;
    int line;
    int column;
  public:
    explicit Lexer(const std::string& input);

    Token nextToken();
  private:
    bool isAtEnd();
    char advance();
    char peek();
    bool match(char expected);
    void skipWhitespace();
};
std::string readFile(const std::string& filename);

int lexer(const std::string& filename);

#endif
