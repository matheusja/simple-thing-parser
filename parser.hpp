#pragma once
#include <iosfwd>
#include "lexer.hpp"
#include "thing.hpp"
namespace Parser {
namespace Exception {
class ExpectedString: public std::exception {};
class ExpectedStringCBracket: public std::exception {};
class ExpectedEqual: public std::exception {};
class ExpectedValue: public std::exception {};
}
class Base {
private:
  Lexer::Base *lexer;
public:
  Base(Lexer::Base *l);
  Thing::Base *parseThing();
};
}
