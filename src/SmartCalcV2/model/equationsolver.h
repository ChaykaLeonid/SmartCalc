#ifndef EQUATIONSOLVER_H
#define EQUATIONSOLVER_H

#include <cmath>
#include <list>
#include <string>

#include "supportive.h"
#include "validator.h"

using std::list;
using std::string;

using iterator = list<s21::Lexem>::iterator;

namespace s21 {
class EquationSolver {
 public:
  void Solve(list<Lexem> *eq_list, AnswerErrors &status, Validator &validator);

 private:
  void Operation(iterator iter, list<Lexem> *eq_list, AnswerErrors &status,
                 Validator &validator);
  bool IsBinaryOperator(const string &op);
  void ProcessingBinary(iterator &iter, list<Lexem> *eq_list,
                        AnswerErrors &status, Validator &validator);
  void ProcessingUnary(iterator &iter, list<Lexem> *eq_list,
                       AnswerErrors &status, Validator &validator);
};
}  // namespace s21
#endif  // EQUATIONSOLVER_H
