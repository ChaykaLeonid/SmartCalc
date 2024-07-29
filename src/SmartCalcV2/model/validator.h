#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <list>
#include <stack>
#include <string>

#include "supportive.h"

using std::list;
using std::stack;
using std::string;

namespace s21 {
class Validator {
 public:
  Validator();
  bool ValidateLength(const string &eq);
  bool ValidateParentheses(const string &eq);
  bool ValidateSymbols(const string &eq);
  bool ValidateNumber(const string &eq);
  bool ValidateOperator(const string &op);
  bool ValidateDivision(const double &divisor);
  bool ValidateSqrt(const double &sqr);
  bool ValidateUnars(const string &eq);
  bool ValidatePolishList(const list<Lexem> *list);
  bool ValidateX(const string &x);
};
}  // namespace s21

#endif  // VALIDATOR_H
