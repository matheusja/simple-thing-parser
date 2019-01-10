#pragma once
#include <iosfwd>
#include <forward_list>
#include <string>

namespace Thing {
class Base {
private:
  std::string name;
public:
  Base(std::string name);
  const std::string &getName();
  virtual ~Base() = 0;
  virtual void std2Stream(std::ostream *strm, int tabs = 0) = 0;
  virtual void lbn2Stream(std::ostream *strm) = 0;
};
class Container : public Base {
private:
  std::forward_list<Base*> data;
public:
  Container(std::string name);
  ~Container();
  void insert(Base* ptr);
  void std2Stream(std::ostream *strm, int tabs = 0);
  void lbn2Stream(std::ostream *strm);
};
class Integer : public Base {
private:
  int data;
public:
  Integer(std::string name, int data);
  ~Integer();
  void std2Stream(std::ostream *strm, int tabs = 0);
  void lbn2Stream(std::ostream *strm);
};
class String : public Base {
private:
  std::string data;
public:
  String(std::string name, std::string data);
  ~String();
  void std2Stream(std::ostream *strm, int tabs = 0);
  void lbn2Stream(std::ostream *strm);
};
}
