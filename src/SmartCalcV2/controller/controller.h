#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

using pair = std::pair<std::vector<double>, std::vector<double>>;

namespace s21 {
class Controller {
 public:
  Controller(Model *model);
  Model *model_;
  void Solve(string equation, string x, AnswerErrors &info);
  pair GetPlotFromModel(PlotInfo &info);
  void LoanAmortized(LoanInfo &info);
  void LoanDeferred(LoanInfo &info);
  DepositResult Deposit(DepositInfo &info);
};
}  // namespace s21

#endif  // CONTROLLER_H
