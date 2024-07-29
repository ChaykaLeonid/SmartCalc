#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <sstream>
#include <stack>
#include <string>
#include <utility>

#include "../controller/controller.h"
#include "qcustomplot.h"

using s21::Controller;
using std::stack;
using std::string;

using pair = std::pair<std::vector<double>, std::vector<double>>;

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr, Controller *controller = nullptr);
  ~View();

  Controller *controller_;

 private slots:
  void on_clear_button_clicked();
  void on_undo_button_clicked();
  void on_button_eq_clicked();

  void on_button_E_clicked();
  void on_asin_clicked();
  void on_acos_clicked();
  void on_atan_clicked();
  void on_ln_clicked();
  void on_sin_clicked();
  void on_cos_clicked();
  void on_tan_clicked();
  void on_log_clicked();
  void on_mod_button_clicked();
  void on_sqrt_clicked();
  void on_caret_clicked();
  void on_left_parentheses_clicked();
  void on_right_parentheses_clicked();
  void on_x_button_clicked();
  void on_button_mult_clicked();
  void on_button_minus_clicked();
  void on_button_plus_clicked();
  void on_button_div_clicked();
  void on_button_dot_clicked();

  void on_button_0_clicked();
  void on_button_1_clicked();
  void on_button_2_clicked();
  void on_button_3_clicked();
  void on_button_4_clicked();
  void on_button_5_clicked();
  void on_button_6_clicked();
  void on_button_7_clicked();
  void on_button_8_clicked();
  void on_button_9_clicked();

  void ShowMessage(string message, int milliseconds);
  void ShowAnswer(double answer, int milliseconds);

  void on_draw_button_clicked();
  void on_calc_loan_button_clicked();
  void on_deferred_loan_radio_clicked();
  void on_amortized_loan_radio_clicked();
  void on_deposit_calc_button_clicked();
  void on_deposit_add_button_clicked();
  void on_pushButton_clicked();
  void on_deposit_withdraw_button_clicked();

 private:
  Ui::View *ui;
  map<int, double> deposit_addings_;
  map<int, double> deposit_withdrawals_;

  void InputButtonProcessing(string text);
  void ErrorProcessing(const AnswerErrors &info);
  stack<string> *buffer_;
};
}  // namespace s21
#endif  // VIEW_H
