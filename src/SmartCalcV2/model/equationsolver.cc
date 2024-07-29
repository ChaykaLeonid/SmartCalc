#include "equationsolver.h"

namespace s21 {
void EquationSolver::Solve(list<Lexem> *eq_list, AnswerErrors &status,
                           Validator &validator) {
  auto it = eq_list->begin();
  while (it != eq_list->end() && status.error == ErrorsCodes::kOk) {
    iterator tmp = it;
    ++tmp;
    if ((*it).operation != "") Operation(it, eq_list, status, validator);
    it = tmp;
  }

  it = eq_list->begin();
  if (eq_list->size() == 1 && it->operation == "") {
    status.answer = it->value;
  } else {
    status.error = ErrorsCodes::kJustWrong;
  }
}

void EquationSolver::Operation(iterator iter, list<Lexem> *eq_list,
                               AnswerErrors &status, Validator &validator) {
  if (IsBinaryOperator(iter->operation)) {
    ProcessingBinary(iter, eq_list, status, validator);
  } else {
    ProcessingUnary(iter, eq_list, status, validator);
  }
}

bool EquationSolver::IsBinaryOperator(const string &op) {
  return (op == "mod" || op == "^" || op == "/" || op == "*" || op == "+" ||
          op == "-");
}

void EquationSolver::ProcessingBinary(iterator &iter, list<Lexem> *eq_list,
                                      AnswerErrors &status,
                                      Validator &validator) {
  string operation = iter->operation;
  double result = 0;
  iterator second_previous = iter;
  --second_previous;
  if (second_previous == eq_list->end()) status.error = ErrorsCodes::kJustWrong;
  double second_operand = second_previous->value;
  --second_previous;
  if (second_previous == eq_list->end()) status.error = ErrorsCodes::kJustWrong;
  double first_operand = second_previous->value;

  if (status.error == ErrorsCodes::kOk) {
    if (operation == "mod") {
      if (validator.ValidateDivision(second_operand))
        result = fmod(first_operand, second_operand);
      else
        status.error = ErrorsCodes::kWrongDivisor;
    } else if (operation == "*") {
      result = first_operand * second_operand;
    } else if (operation == "+") {
      result = first_operand + second_operand;
    } else if (operation == "-") {
      result = first_operand - second_operand;
    } else if (operation == "/") {
      if (validator.ValidateDivision(second_operand))
        result = first_operand / second_operand;
      else
        status.error = ErrorsCodes::kWrongDivisor;
    } else if (operation == "^") {
      result = pow(first_operand, second_operand);
    }

    eq_list->erase(second_previous, iter);
    iter->value = result;
    iter->operation = "";
    iter->priority = 0;
  }
}

void EquationSolver::ProcessingUnary(iterator &iter, list<Lexem> *eq_list,
                                     AnswerErrors &status,
                                     Validator &validator) {
  string operation = iter->operation;
  iterator prev = iter;
  --prev;
  if (prev == eq_list->end()) status.error = ErrorsCodes::kJustWrong;

  if (operation == "sin") {
    prev->value = sin(prev->value);
  } else if (operation == "cos") {
    prev->value = cos(prev->value);
  } else if (operation == "tan") {
    prev->value = tan(prev->value);
  } else if (operation == "sqrt") {
    if (validator.ValidateSqrt(prev->value))
      prev->value = sqrt(prev->value);
    else
      status.error = ErrorsCodes::kWrongSqrt;
  } else if (operation == "ln") {
    prev->value = log(prev->value);
  } else if (operation == "log") {
    prev->value = log10(prev->value);
  } else if (operation == "atan") {
    prev->value = atan(prev->value);
  } else if (operation == "acos") {
    prev->value = acos(prev->value);
  } else if (operation == "asin") {
    prev->value = asin(prev->value);
  } else if (operation == "~") {
    prev->value *= -1;
  }
  eq_list->erase(iter);
}
}  // namespace s21
