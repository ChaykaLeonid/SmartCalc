#include "parser.h"

namespace s21 {
Parser::Parser() { tokens_ = new list<string>(); }

Parser::~Parser() { delete tokens_; }

list<string> *Parser::get_tokens_() {
  list<string> *answer = nullptr;
  if (!tokens_->empty()) answer = tokens_;
  return answer;
}

void Parser::ParseToList(string &equation) {
  tokens_->clear();
  size_t string_length = equation.length();
  string token = "";
  string maybe_unary = "+-";
  string char_unary = "tclsma";
  string symbolic_operators = "()*^/";
  while (!equation.empty()) {
    bool to_add = true;
    if (equation[0] == ' ') {
      equation.erase(0, 1);
      to_add = false;
    } else if (IfContains(char_unary, equation[0])) {
      OperatorFinder(equation, token);
    } else if (IfContains(symbolic_operators, equation[0])) {
      token = equation.substr(0, 1);
    } else if (IfContains(maybe_unary, equation[0])) {
      if (WhetherUnary(token, string_length, equation)) {
        if (equation[0] == '+')
          token = "plus";
        else
          token = "~";
      } else {
        token = equation.substr(0, 1);
      }
    } else if (isdigit(equation[0])) {
      token = equation.substr(0, SearchForNumberEnd(equation));
    } else if (equation[0] == 'x') {
      token = equation.substr(0, 1);
    }
    if (to_add) {
      tokens_->push_back(token);
      equation.erase(0, token.length());
    }
  }
}

size_t Parser::SearchForNumberEnd(string number) {
  size_t length = 0;
  string exponential = "Ee";
  string exponential_signs = "-+";
  while (isdigit(number[length]) || number[length] == '.' ||
         IfContains(exponential, number[length]) ||
         (IfContains(exponential_signs, number[length]) &&
          IfContains(exponential, number[length - 1]))) {
    ++length;
  }
  return length;
}

bool Parser::OperatorFinder(string &equation, string &answer) {
  string three_char_operators = "tcslm";
  string four_char_operators = "as";
  bool no_error = true;
  if (IfContains(three_char_operators, equation[0]) && equation[1] != 'q' &&
      equation[1] != 'n') {
    answer = equation.substr(0, 3);
  } else if (IfContains(four_char_operators, equation[0])) {
    answer = equation.substr(0, 4);
  } else if (equation[0] == 'l') {
    answer = equation.substr(0, 2);
  } else {
    no_error = false;
  }
  return no_error;
}

bool Parser::WhetherUnary(string &token, size_t initial_length,
                          const string &actual) {
  return token == "(" || initial_length == actual.length();
}
}  // namespace s21
