#include "model.h"

namespace s21 {
Model::Model() {}

void Model::SolveEquation(string equation, string x, AnswerErrors &info) {
  if (!validator_.ValidateLength(equation))
    info.error = ErrorsCodes::kWrongEqLength;
  else if (!validator_.ValidateParentheses(equation))
    info.error = ErrorsCodes::kWrongParenthesesSequence;
  else if (!validator_.ValidateSymbols(equation))
    info.error = ErrorsCodes::kWrongSymbolFound;
  else if (!validator_.ValidateUnars(equation))
    info.error = ErrorsCodes::kUnarWinthoutParenthesis;
  else if (!validator_.ValidateX(x))
    info.error = ErrorsCodes::kWrongDouble;

  if (info.error == ErrorsCodes::kOk) {
    parser_.ParseToList(equation);
    translator_.Stacking(parser_.get_tokens_(), x, info, validator_);
  }
  if (!validator_.ValidatePolishList(translator_.get_list_()))
    info.error = ErrorsCodes::kMoreOperationsThanOperands;
  if (info.error == ErrorsCodes::kOk)
    solver_.Solve(translator_.get_list_(), info, validator_);
}

pair Model::PlotGeneration(PlotInfo &info) {
  double x, y;
  std::vector<double> vector_x_, vector_y_;
  for (x = info.x_begin; x <= info.x_end; x += info.h) {
    AnswerErrors data;
    SolveEquation(info.eq, std::to_string(x), data);
    if (data.error == ErrorsCodes::kOk) {
      y = data.answer;
      vector_x_.push_back(x);
      vector_y_.push_back(y);
    }
  }
  return pair(vector_x_, vector_y_);
}

void Model::LoanAmortizedProcessing(LoanInfo &info) {
  double k, p;
  p = (info.loan_interest / 12) / 100;
  k = p * pow((1 + p), info.loan_months) / (pow((1 + p), info.loan_months) - 1);
  info.monthly_payment = info.loan_amount * k;
  info.total_amount = info.monthly_payment * info.loan_months;
  info.interest_payment = info.total_amount - info.loan_amount;
}

void Model::LoanDeferredProcessing(LoanInfo &info) {
  info.total_amount = 0;
  double d = info.loan_amount / info.loan_months;
  double p = (info.loan_interest / 12) / 100;
  for (int n = 1; n < info.loan_months + 1; ++n) {
    if (n == 1) info.last_payment = d + (info.loan_amount - d * (n - 1)) * p;
    if (n == 3) info.step = info.monthly_payment - info.last_payment;
    info.monthly_payment = d + (info.loan_amount - d * (n - 1)) * p;
    info.total_amount += info.monthly_payment;
  }
  info.interest_payment = info.total_amount - info.loan_amount;
}

DepositResult Model::ProcessDeposit(DepositInfo &info) {
  double intermediate_amount = info.initial_amount;
  DepositResult result;
  int T = info.months;

  for (int i = 1; i <= T; ++i) {
    double income = 0;
    if (info.withdrawals_monthly) {
      income = ((intermediate_amount * info.return_rate * 1 / 12) / 100);
    } else {
      if (i % 12 == 0)
        income = ((intermediate_amount * info.return_rate) / 100);
      else if (i == T)
        income =
            ((intermediate_amount * info.return_rate * (T % 12) / 12) / 100);
    }
    if (info.addings.count(i)) {
      intermediate_amount += info.addings.at(i);
      info.initial_amount += info.addings.at(i);
    }
    if (info.withdrawals.count(i)) {
      intermediate_amount -= info.withdrawals.at(i);
      info.initial_amount -= info.withdrawals.at(i);
    }
    result.interest_total += income;
    if (info.capitalization) intermediate_amount += income;
  }
  result.withdrawal_total = info.initial_amount + result.interest_total;
  result.tax_total = result.interest_total * info.tax_rate / 100;

  return result;
}
}  // namespace s21
