#include <gtest/gtest.h>

#include "../controller/controller.h"
#include "../model/model.h"

TEST(CalcTest, BasicEquation) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("2+2", "0", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_EQ(answer.answer, 4);
}

TEST(CalcTest, BetterEquation1) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("2^3^2", "0", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_EQ(answer.answer, 512);
}

TEST(CalcTest, BetterEquation2) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("(8+2*5)/(1+3*2-4)", "0", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_EQ(answer.answer, 6);
}

TEST(CalcTest, BetterEquation3) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("cos(1*2)-1", "0", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_DOUBLE_EQ(answer.answer, -1.4161468365471424);
}

TEST(CalcTest, BetterEquation4) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("3+4*2/1-5+2^2", "0", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_EQ(answer.answer, 10);
}

TEST(CalcTest, BetterEquation5) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("atan(2*x)", "0.0019", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_EQ(answer.answer, 0.0037999817094918021);
}

TEST(CalcTest, BetterEquation6) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("3-(3)", "0", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_EQ(answer.answer, 0);
}

TEST(CalcTest, BetterEquation7) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("14^23/6*9+5-1+(56*2)", "0", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_EQ(answer.answer, 344378539330472184817647616.0);
}

TEST(CalcTest, BetterEquation8) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("sin(-(-2^(-3)))+log(10^(-4)*10^4*10)", "0", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_EQ(answer.answer, 1.1246747333852276);
}

TEST(CalcTest, BetterEquation9) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("asdf", "0", answer);

  ASSERT_FALSE(answer.error == s21::ErrorsCodes::kOk);
}

TEST(CalcTest, BetterEquation10) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve("sqrt(-1)", "0", answer);

  ASSERT_FALSE(answer.error == s21::ErrorsCodes::kOk);
}

TEST(CalcTest, BetterEquation11) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::AnswerErrors answer;
  controller.Solve(
      "cos(45)+sin(45)+tan(45)+acos(45)+asin(45)+atan(45)+sqrt(45)+ln(45)+log("
      "45)",
      "0", answer);

  ASSERT_TRUE(answer.error == s21::ErrorsCodes::kOk);
  ASSERT_EQ("nan", std::to_string(answer.answer));
}

TEST(CalcTest, CreditCalcAmortized) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::LoanInfo info;
  info.loan_amount = 5000000;
  info.loan_interest = 10;
  info.loan_months = 16;
  controller.LoanAmortized(info);

  ASSERT_EQ(info.monthly_payment, 335094.52489486785);
  ASSERT_EQ(info.interest_payment, 361512.39831788559);
  ASSERT_EQ(info.total_amount, 5361512.3983178856);
}

TEST(CalcTest, CreditCalcDeferred) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::LoanInfo info;
  info.loan_amount = 5000000;
  info.loan_interest = 10;
  info.loan_months = 16;
  controller.LoanDeferred(info);

  ASSERT_EQ(info.monthly_payment, 315104.16666666669);
  ASSERT_EQ(info.interest_payment, 354166.66666666698);
  ASSERT_EQ(info.step, -2604.1666666666861);
}

TEST(CalcTest, DepositCalc) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::DepositInfo info;
  s21::DepositResult result;
  info.initial_amount = 5000000;
  info.return_rate = 5;
  info.tax_rate = 13;
  info.capitalization = true;
  info.withdrawals_monthly = true;
  info.months = 12;
  result = controller.Deposit(info);

  ASSERT_EQ(result.withdrawal_total, 5255809.4894086663);
  ASSERT_EQ(result.tax_total, 33255.233623126573);
  ASSERT_EQ(result.interest_total, 255809.48940866595);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
