#include "controller.h"

namespace s21 {
Controller::Controller(Model *model) : model_(model) {}

void Controller::Solve(string equation, string x, AnswerErrors &info) {
  model_->SolveEquation(equation, x, info);
}

pair Controller::GetPlotFromModel(PlotInfo &info) {
  return model_->PlotGeneration(info);
}

void Controller::LoanAmortized(LoanInfo &info) {
  model_->LoanAmortizedProcessing(info);
}

void Controller::LoanDeferred(LoanInfo &info) {
  model_->LoanDeferredProcessing(info);
}

DepositResult Controller::Deposit(DepositInfo &info) {
  return model_->ProcessDeposit(info);
}
}  // namespace s21
