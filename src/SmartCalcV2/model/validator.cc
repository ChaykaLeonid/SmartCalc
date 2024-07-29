#include "validator.h"

namespace s21 {
Validator::Validator() {}

bool Validator::ValidateLength(const string &eq) { return (eq.length() < 256); }

bool Validator::ValidateParentheses(const string &eq) {
  stack<int> checking_stack;
  bool answer = true;
  for (auto &ch : eq) {
    if (ch == '(') {
      checking_stack.push(0);
    } else if (ch == ')') {
      if (!checking_stack.empty()) {
        checking_stack.pop();
      } else {
        answer = false;
      }
    }
  }
  if (!checking_stack.empty()) answer = false;
  return answer;
}

bool Validator::ValidateSymbols(const string &eq) {
  string pool = "1234567890+-/*()^.modsinctaqrlgEex ";
  return !(eq.find_first_not_of(pool) != string::npos);
}

bool Validator::ValidateNumber(const string &eq) {
  int dots = 0;
  int Ee = 0;
  int plus_minus = 0;

  for (auto it = eq.cbegin(); it != eq.cend(); ++it) {
    if (*it == '.') {
      ++dots;
    } else if (*it == 'e' || *it == 'E') {
      ++Ee;
    } else if (*it == '+' || *it == '-') {
      ++plus_minus;
    }
  }
  return dots <= 1 && Ee <= 1 && plus_minus <= 1;
}

bool Validator::ValidateOperator(const string &op) {
  return op == "+" || op == "-" || op == "*" || op == "/" || op == "mod" ||
         op == "(" || op == ")" || op == "sin" || op == "cos" || op == "tan" ||
         op == "atan" || op == "acos" || op == "asin" || op == "ln" ||
         op == "log" || op == "sqrt" || op == "^" || op == "~" || op == "plus";
}

bool Validator::ValidateDivision(const double &divisor) { return divisor != 0; }

bool Validator::ValidateSqrt(const double &sqr) { return sqr >= 0; }

bool Validator::ValidateUnars(const string &eq) {
  string questionable_operators = "+-*/^";
  bool answer = true;
  if (eq.front() == '-' || eq.front() == '+') answer = false;
  for (auto it = eq.cbegin(); it != eq.cend(); ++it) {
    if (questionable_operators.find(*it) != string::npos) {
      if (questionable_operators.find(*(it - 1)) != string::npos)
        answer = false;
    }
  }
  return answer;
}

bool Validator::ValidatePolishList(const list<Lexem> *list) {
  int operators = 0;
  int numbers = 0;
  for (auto it = list->cbegin(); it != list->cend(); ++it) {
    if (it->operation == "") {
      ++numbers;
    } else if (it->priority == 2 || it->priority == 1 || it->operation == "^") {
      ++operators;
    }
  }
  return operators <= numbers;
}

bool Validator::ValidateX(const string &x) {
  bool answer = true;
  string pool = "1234567890.eE-";
  if (!std::isdigit(x.front()) && x.front() != '-') answer = false;
  if (x.find_first_not_of(pool) != string::npos) answer = false;
  if (!ValidateNumber(x)) answer = false;
  return answer;
}
}  // namespace s21
