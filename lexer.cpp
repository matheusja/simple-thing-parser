
#include <iostream>

#include "lexer.hpp"

namespace {

bool isWhiteSpace(char c) {
  return (c == ' ') || (c == '\t') || (c == '\r') || (c == '\n');
}
bool isDigit(char c) {
  return (c >= '0') && (c <= '9');
}
bool consumeWhiteSpace(std::istream *strm, char &current) {
  *strm >> current;
  while ((isWhiteSpace(current) || current == '#')) {
    if (strm->eof()) {
      return true;
    }
    if (current == '#') {
      do {
        *strm >> current;
        if (strm->eof()) {
          return true;
        }
      } while (current != '\n');
    }
    *strm >> current;
  }
  return false;
}
}
Lexer::Base::Base(std::istream *strm) : strm(strm) {}

Lexer::Token Lexer::Base::seekToken() {
  char current;
  Token t;
  if (consumeWhiteSpace(this->strm, current)) {
    t.type = Token::Type::Final;
    return t;
  }
  switch(current) {
  case '=':
    t.type = Token::Type::Equal;
    break;
  case '{':
    t.type = Token::Type::OpenBracket;
    break;
  case '}':
    t.type = Token::Type::CloseBracket;
    break;
  case '"':
    t.type = Token::Type::String;
    std::getline(*this->strm, t.val, '"');
    if (strm->eof()) {
      throw new Lexer::Exception::UnexpectedEOF();
    }
    break;
  default:
    if(isDigit(current)) {
      t.type = Lexer::Token::Type::Integer;
      while(!this->strm->eof() && isDigit(current)) {
        t.val += current;
        *this->strm >> current;
      }
      this->strm->unget();
    } else {
      throw new Lexer::Exception::UnknowToken();
    }
  }
  return t;
}

Lexer::Token Lexer::Base::nextToken() {
  Lexer::Token t;
  if (this->tDeque.empty()) {
    *this->strm >> std::noskipws;
    t = this->seekToken();
    *this->strm >> std::skipws;
    return t;
  }
  t = this->tDeque.front();
  this->tDeque.pop_front();
  return t;
}

void Lexer::Base::pushBackToken(Lexer::Token t) {
  this->tDeque.push_front(t);
}
