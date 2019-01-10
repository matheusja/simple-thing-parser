#pragma once
#include <deque>
#include <exception>
#include <iosfwd>
#include <string>
namespace Lexer {
struct Token {
  enum class Type {String, Integer, OpenBracket, CloseBracket, Equal, Final};
  Type type;
  std::string val;
};
namespace Exception {
  class UnexpectedEOF : public std::exception {};
  class UnknowToken   : public std::exception {};
}
class Base {
private:
  std::deque<Token> tDeque;
  std::istream *strm;
protected:
  virtual Token seekToken();
public:
  Base(std::istream *strm);
  virtual ~Base() = default;
  Token nextToken();
  void pushBackToken(Token t);
};
}
