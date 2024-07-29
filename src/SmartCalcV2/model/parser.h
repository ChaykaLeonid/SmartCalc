#ifndef PARSER_H
#define PARSER_H

#include <cctype>
#include <iostream>
#include <list>
#include <string>

#include "supportive.h"

using s21::IfContains;
using std::list;
using std::string;

namespace s21 {
class Parser {
 public:
  Parser();
  ~Parser();
  void ParseToList(string &init_equation);  // TODO exp число
  list<string> *get_tokens_();

 private:
  list<string> *tokens_;

  size_t SearchForNumberEnd(string number);
  bool OperatorFinder(string &equation, string &answer);
  bool WhetherUnary(string &token, size_t initial_length, const string &actual);
};
}  // namespace s21

#endif  // PARSER_H
