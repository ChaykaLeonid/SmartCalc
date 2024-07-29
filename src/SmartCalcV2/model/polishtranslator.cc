#include "polishtranslator.h"

namespace s21 {
PolishTranslator::PolishTranslator() {
  stack_ = new stack<Lexem>;
  polish_list_ = new list<Lexem>;
}

s21::PolishTranslator::~PolishTranslator() {
  delete stack_;
  delete polish_list_;
}

void PolishTranslator::set_x_(string x) { x_ = x; }

list<Lexem> *PolishTranslator::Stacking(list<string> *origin, string x,
                                        AnswerErrors &status,
                                        Validator &validator) {
  Cleanse();
  string unars = "+-";

  for (auto it = origin->begin(); it != origin->end(); ++it) {
    size_t priority = 0;

    if (isdigit((*it)[0]) || *it == "x") {
      if (!validator.ValidateNumber(*it) || !validator.ValidateNumber(x))
        status.error = ErrorsCodes::kWrongDouble;
      double operand = ConvertToDouble(*it, x);
      polish_list_->push_back(Lexem(priority, operand));
    } else {
      if (!validator.ValidateOperator(*it))
        status.error = ErrorsCodes::kWrongOperator;
      priority = ConvertToOperator(*it);
      if (priority < 6) {
        LowerPriorityProcessing(priority, it);
      } else if (priority == 6) {
        ClosingParenthesesProcessing();
      } else {
        HigherPriorityProcessing(priority, it);
      }
    }
  }

  while (!stack_->empty()) {
    FromStackToList();
  }
  return polish_list_;
}

list<Lexem> *PolishTranslator::get_list_() { return polish_list_; }

double PolishTranslator::ConvertToDouble(string &number, string x) {
  double operand = 0;
  if (number == "x") number = x;
  operand = stod(number);
  return operand;
}

size_t PolishTranslator::ConvertToOperator(string &op) {
  size_t priority = 0;
  if (op == "plus") {
    priority = 9;
  } else if (op == "~") {
    priority = 8;
  } else if (op == ")") {
    priority = 6;
  } else if (op == "(") {
    priority = 5;
  } else if (op == "^" || op == "sqrt") {
    priority = 4;
  } else if ((op.length() == 3 && op != "mod") || op.at(0) == 'a' ||
             op == "ln") {
    priority = 3;
  } else if (op == "*" || op == "/" || op == "mod") {
    priority = 2;
  } else if (op == "+" || op == "-") {
    priority = 1;
  }
  return priority;
}

void PolishTranslator::FromStackToList() {
  polish_list_->push_back(stack_->top());
  stack_->pop();
}

void PolishTranslator::ClosingParenthesesProcessing() {
  while (stack_->top().priority != 5) {
    FromStackToList();
  }
  stack_->pop();
  if (!stack_->empty() &&
      (stack_->top().priority == 3 || stack_->top().operation == "sqrt" ||
       stack_->top().priority == 9 || stack_->top().priority == 8)) {
    FromStackToList();
  }
}

void PolishTranslator::LowerPriorityProcessing(size_t priority,
                                               list<string>::iterator it) {
  if (stack_->empty() || stack_->top().priority < priority || priority == 4 ||
      stack_->top().priority == 9 || stack_->top().priority == 8) {
    stack_->push(Lexem(priority, 0, *it));
  } else if (stack_->top().priority >= priority) {
    while (!stack_->empty() && stack_->top().priority != 5 &&
           stack_->top().priority >= priority) {
      if (stack_->top().priority >= priority) {
        FromStackToList();
      }
    }
    stack_->push(Lexem(priority, 0, *it));
  }
}

void PolishTranslator::HigherPriorityProcessing(size_t priority,
                                                list<string>::iterator it) {
  string top_oper;
  if (!stack_->empty()) top_oper = stack_->top().operation;
  while (!stack_->empty() && stack_->top().priority >= priority &&
         stack_->top().priority != 5) {
    FromStackToList();
    if (!stack_->empty()) top_oper = stack_->top().operation;
  }
  stack_->push(Lexem(priority, 0, *it));
}

void PolishTranslator::Cleanse() {
  polish_list_->clear();
  x_ = "";
  while (!stack_->empty()) stack_->pop();
}
}  // namespace s21
