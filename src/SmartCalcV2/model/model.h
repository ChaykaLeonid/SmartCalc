#ifndef MODEL_H
#define MODEL_H

#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "equationsolver.h"
#include "parser.h"
#include "polishtranslator.h"
#include "supportive.h"
#include "validator.h"

using pair = std::pair<std::vector<double>, std::vector<double>>;

namespace s21 {
class Model {
 public:
  Model();
  void SolveEquation(string equation, string x, AnswerErrors &info);
  pair PlotGeneration(PlotInfo &info);
  void LoanAmortizedProcessing(LoanInfo &info);
  void LoanDeferredProcessing(LoanInfo &info);
  DepositResult ProcessDeposit(DepositInfo &info);

 private:
  Parser parser_;
  PolishTranslator translator_;
  EquationSolver solver_;
  Validator validator_;
};
}  // namespace s21

#endif  // MODEL_H
