#ifndef POLISHTRANSLATOR_H
#define POLISHTRANSLATOR_H

#include <cctype>
#include <iostream>
#include <list>
#include <stack>
#include <string>

#include "supportive.h"
#include "validator.h"

using std::list;
using std::stack;
using std::string;

namespace s21 {
class PolishTranslator {
 public:
  PolishTranslator();
  ~PolishTranslator();

  void set_x_(string x);
  list<Lexem> *Stacking(list<string> *origin, string x, AnswerErrors &status,
                        Validator &validator);
  list<Lexem> *get_list_();

 private:
  stack<Lexem> *stack_;
  list<Lexem> *polish_list_;
  string x_;

  double ConvertToDouble(string &number, string x);
  size_t ConvertToOperator(string &op);
  void FromStackToList();
  void ClosingParenthesesProcessing();
  void LowerPriorityProcessing(size_t priority, list<string>::iterator it);
  void HigherPriorityProcessing(size_t priority, list<string>::iterator it);
  void Cleanse();
};
}  // namespace s21

#endif  // POLISHTRANSLATOR_H
