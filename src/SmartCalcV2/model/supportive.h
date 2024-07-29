#ifndef SUPPORTIVE_H
#define SUPPORTIVE_H

#include <iostream>
#include <map>
#include <string>

using std::map;
using std::string;

namespace s21 {

enum ErrorsCodes {
  kOk,
  kWrongEqLength,
  kWrongParenthesesSequence,
  kWrongSymbolFound,
  kWrongDouble,
  kWrongOperator,
  kWrongDivisor,
  kWrongSqrt,
  kUnarWinthoutParenthesis,
  kJustWrong,
  kMoreOperationsThanOperands
};

struct Lexem {
  Lexem(size_t prior, double val, string oper = "")
      : priority(prior), value(val), operation(oper) {}

  size_t priority = 0;
  double value = 0;
  string operation = "";
};

struct AnswerErrors {
  double answer = 0;
  ErrorsCodes error = ErrorsCodes::kOk;
};

struct PlotInfo {
  double x_begin, x_end, h;
  string eq;
};

struct LoanInfo {
  double loan_amount = 0;
  double loan_interest = 0;
  int loan_months = 0;
  double total_amount = 0;
  double monthly_payment = 0;
  double interest_payment = 0;
  double step = 0;
  double last_payment = 0;
};

struct DepositInfo {
  double initial_amount = 0;
  double return_rate = 0;
  bool capitalization = false;
  double tax_rate = 0;
  bool withdrawals_monthly = false;
  int months = 0;
  map<int, double> addings;
  map<int, double> withdrawals;
};

struct DepositResult {
  double interest_total = 0;
  double tax_total = 0;
  double withdrawal_total = 0;
};

bool IfContains(string where, char symbol);
}  // namespace s21

#endif  // SUPPORTIVE_H
