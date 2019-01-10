#include <iostream>
#include <fstream>
#include "parser.hpp"
int main() {
  std::ifstream file("teste.thing");
  Lexer::Base lexer(&file);
  Parser::Base parser(&lexer);
  Thing::Base *a = parser.parseThing();
  a->std2Stream(&std::cout);
  std::cout << "\n";
  a->lbn2Stream(&std::cout);
  std::cout << "\n";
}
