#include <iostream>

#include "thing.hpp"

#define UNUSED __attribute__((unused))

namespace {
void printTabs(std::ostream *strm, int tabs) {
  for (int i = 0; i < tabs; ++i) {
    *strm << "\t";
  }
}
}

Thing::Base::Base(std::string name) : name(name) {}
Thing::Container::Container(std::string name) : Thing::Base(name) {}
Thing::Integer::Integer(std::string name, int data) : Thing::Base(name), data(data) {}
Thing::String::String(std::string name, std::string data) : Thing::Base(name), data(data) {}

Thing::Base::~Base() {}
Thing::Container::~Container() {
  for(auto const &iter : this->data) {
    delete iter;
  }
}
Thing::Integer::~Integer() {}
Thing::String::~String() {}

const std::string &Thing::Base::getName() {
  return this->name;
}

void Thing::Container::std2Stream(std::ostream *strm, int tabs) {
  printTabs(strm, tabs);
  *strm << this->getName() << " = {\n";
  for(auto const &iter : this->data) {
    iter->std2Stream(strm, tabs + 1);
  }
  printTabs(strm, tabs);
  *strm << "}";
}

void Thing::Integer::std2Stream(std::ostream *strm, int UNUSED tabs) {
  printTabs(strm, tabs);
  *strm << this->getName() << " = " << this->data << "\n";
}

void Thing::String::std2Stream(std::ostream *strm, int UNUSED tabs) {
  printTabs(strm, tabs);
  *strm << this->getName() << " = \"" << this->data << "\"" << "\n";
}

void Thing::Container::lbn2Stream(std::ostream *strm) {
  *strm << "[" << this->getName();
  for(auto const &iter : this->data) {
    iter->lbn2Stream(strm);
  }
  *strm << "]";
}

void Thing::Integer::lbn2Stream(std::ostream *strm) {
  *strm << "[" << this->getName() << "[" << this->data << "]]";
}
void Thing::String::lbn2Stream(std::ostream *strm) {
  *strm << "[" << this->getName() << "[" << this->data << "]]";
}

void Thing::Container::insert(Base *ptr) {
    this->data.push_front(ptr);
}
