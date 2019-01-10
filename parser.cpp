#include <iostream>

#include "parser.hpp"
/*
  E-><string> = X
  X-> <num> | <string> | { E* }
*/
namespace {
  Thing::Base *parseE(Lexer::Base *l);
  void parseEStar(Lexer::Base *l, Thing::Container *ctr);
  Thing::Base *parseX(Lexer::Base *l, std::string name);
}


Parser::Base::Base(Lexer::Base *l) {
  this->lexer = l;
}
Thing::Base *Parser::Base::parseThing() {
  Thing::Base *thing = parseE(this->lexer);
  if (this->lexer->nextToken().type != Lexer::Token::Type::Final)
    //WTF????
    std::cerr << "WTF?\n";
  return thing;
}

namespace {
Thing::Base *parseE(Lexer::Base *l) {
  Lexer::Token t = l->nextToken(), t1;
  if (t.type != Lexer::Token::Type::String) {
    l->pushBackToken(t);
    throw Parser::Exception::ExpectedString();
  }
  t1 = l->nextToken();
  if (t1.type != Lexer::Token::Type::Equal)
    throw Parser::Exception::ExpectedEqual();
  return parseX(l, t.val);
}
Thing::Base *parseX(Lexer::Base *l, std::string name) {
  Thing::Base *ptr = nullptr;
  Lexer::Token t = l->nextToken();
  switch(t.type) {
  case Lexer::Token::Type::OpenBracket:
    ptr = new Thing::Container(name);
    parseEStar(l, (Thing::Container *)ptr);
    break;
  case Lexer::Token::Type::Integer:
    ptr = new Thing::Integer(name, std::stoi(t.val));
    break;
  case Lexer::Token::Type::String:
    ptr = new Thing::String(name, t.val);
    break;
  default:
    std::cerr << "WTF?\n";
  }
  return ptr;
}
void parseEStar(Lexer::Base *l, Thing::Container *ctr) {
  Lexer::Token t;
  t = l->nextToken();
  while (t.type != Lexer::Token::Type::CloseBracket) {
    l->pushBackToken(t);
    ctr->insert(parseE(l));
    t = l->nextToken();
  }
}

}
