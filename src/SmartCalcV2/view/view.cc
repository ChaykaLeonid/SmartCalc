#include "view.h"

#include "ui_view.h"

namespace s21 {
View::View(QWidget *parent, Controller *controller)
    : QMainWindow(parent), controller_(controller), ui(new Ui::View) {
  ui->setupUi(this);
  buffer_ = new stack<string>;
}

View::~View() {
  delete buffer_;
  delete ui;
}

void View::on_clear_button_clicked() {
  while (!buffer_->empty()) buffer_->pop();
  ui->display->setText("0");
}

void View::on_undo_button_clicked() {
  if (!buffer_->empty()) {
    ui->display->setText(QString::fromStdString(buffer_->top()));
    buffer_->pop();
  }
}

void View::on_button_eq_clicked() {
  AnswerErrors info;
  string equation = ui->display->text().toStdString();
  string x = ui->x_display->text().toStdString();
  controller_->Solve(equation, x, info);
  if (info.error == ErrorsCodes::kOk) {
    ShowAnswer(info.answer, 5000);
  } else {
    ErrorProcessing(info);
  }
}

void View::on_button_E_clicked() {
  if (ui->display->text() != "0" &&
      std::isdigit(ui->display->text().toStdString().back())) {
    InputButtonProcessing("E");
  } else {
    ShowMessage("NO", 200);
  }
}

void View::on_asin_clicked() { InputButtonProcessing("asin("); }

void View::on_acos_clicked() { InputButtonProcessing("acos("); }

void View::on_atan_clicked() { InputButtonProcessing("atan("); }

void View::on_ln_clicked() { InputButtonProcessing("ln("); }

void View::on_sin_clicked() { InputButtonProcessing("sin("); }

void View::on_cos_clicked() { InputButtonProcessing("cos("); }

void View::on_tan_clicked() { InputButtonProcessing("tan("); }

void View::on_log_clicked() { InputButtonProcessing("log("); }

void View::on_mod_button_clicked() { InputButtonProcessing("mod"); }

void View::on_sqrt_clicked() { InputButtonProcessing("sqrt("); }

void View::on_caret_clicked() { InputButtonProcessing("^"); }

void View::on_left_parentheses_clicked() { InputButtonProcessing("("); }

void View::on_right_parentheses_clicked() { InputButtonProcessing(")"); }

void View::on_x_button_clicked() { InputButtonProcessing("x"); }

void View::on_button_mult_clicked() { InputButtonProcessing("*"); }

void View::on_button_minus_clicked() { InputButtonProcessing("-"); }

void View::on_button_plus_clicked() { InputButtonProcessing("+"); }

void View::on_button_div_clicked() { InputButtonProcessing("/"); }

void View::on_button_dot_clicked() { InputButtonProcessing("."); }

void View::on_button_0_clicked() { InputButtonProcessing("0"); }

void View::on_button_1_clicked() { InputButtonProcessing("1"); }

void View::on_button_2_clicked() { InputButtonProcessing("2"); }

void View::on_button_3_clicked() { InputButtonProcessing("3"); }

void View::on_button_4_clicked() { InputButtonProcessing("4"); }

void View::on_button_5_clicked() { InputButtonProcessing("5"); }

void View::on_button_6_clicked() { InputButtonProcessing("6"); }

void View::on_button_7_clicked() { InputButtonProcessing("7"); }

void View::on_button_8_clicked() { InputButtonProcessing("8"); }

void View::on_button_9_clicked() { InputButtonProcessing("9"); }

void View::ShowMessage(string message, int milliseconds) {
  QString Answer = QString::fromStdString(message);
  ui->statusbar->showMessage(Answer, milliseconds);
}

void View::ShowAnswer(double answer, int milliseconds) {
  QString Answer = QString::number(answer, 'f', 7);
  ui->statusbar->showMessage(Answer, milliseconds);
}

void View::InputButtonProcessing(string text) {
  buffer_->push(ui->display->text().toStdString());
  if (ui->display->text() == "0") {
    ui->display->setText(QString::fromStdString(text));
  } else {
    ui->display->insert(QString::fromStdString(text));
  }
}

void View::ErrorProcessing(const AnswerErrors &info) {
  string output;
  if (info.error == ErrorsCodes::kWrongEqLength) {
    output = "More than 255 symbols.";
  } else if (info.error == ErrorsCodes::kWrongParenthesesSequence) {
    output = "Wrong parentheses sequnce.";
  } else if (info.error == ErrorsCodes::kWrongSymbolFound) {
    output = "Wrong symbol in equasion.";
  } else if (info.error == ErrorsCodes::kWrongDouble) {
    output = "Wrong number is present.";
  } else if (info.error == ErrorsCodes::kWrongOperator) {
    output = "Wrong operator is present.";
  } else if (info.error == ErrorsCodes::kWrongDivisor) {
    output = "Division by zero is present.";
  } else if (info.error == ErrorsCodes::kWrongSqrt) {
    output = "Finding square root of negative number attempt.";
  } else if (info.error == ErrorsCodes::kUnarWinthoutParenthesis) {
    output = "Add parenthesis to unar plus/minus.";
  } else if (info.error == ErrorsCodes::kJustWrong) {
    output = "Something is wrong with the equation.";
  } else if (info.error == ErrorsCodes::kMoreOperationsThanOperands) {
    output = "Too many operators.";
  }
  ShowMessage(output, 3500);
}

void View::on_draw_button_clicked() {
  PlotInfo info;
  info.eq = ui->display->text().toStdString();
  info.h = ui->step_input->value();
  info.x_begin = ui->xmin_input->value();
  info.x_end = ui->xmax_input->value() + info.h;

  pair plot = controller_->GetPlotFromModel(info);

  ui->widget->xAxis->setRange(ui->xmin_input->value(), ui->xmax_input->value());
  ui->widget->yAxis->setRange(ui->ymin_input->value(), ui->ymax_input->value());

  ui->widget->clearGraphs();
  ui->widget->addGraph();
  QVector<double> q_first =
      QVector<double>(plot.first.begin(), plot.first.end());
  QVector<double> q_second =
      QVector<double>(plot.second.begin(), plot.second.end());
  ui->widget->graph(0)->addData(q_first, q_second);
  ui->widget->replot();
}

void View::on_calc_loan_button_clicked() {
  LoanInfo info;
  info.loan_amount = ui->loan_amount_SpinBox->value();
  info.loan_interest = ui->loan_interest_spinBox->value();
  info.loan_months = ui->loan_months_spinBox->value();

  if (!ui->deferred_loan_radio->isChecked()) {
    controller_->LoanAmortized(info);
  } else {
    controller_->LoanDeferred(info);
    ui->loan_step_label->setText(QString::number(info.step, 'f', 7));
    ui->loan_last_payment_label->setText(
        QString::number(info.last_payment, 'f', 7));
  }

  ui->loan_total_payment_label->setText(
      QString::number(info.total_amount, 'f', 7));
  ui->loan_monthly_also_first_label->setText(
      QString::number(info.monthly_payment, 'f', 7));
  ui->loan_interest_label->setText(
      QString::number(info.interest_payment, 'f', 7));
}

void View::on_deferred_loan_radio_clicked() {
  ui->turnable_label_1->setText("Last Payment:");
  ui->turnable_label_2->setText("First Payment:");
  ui->turnable_label_3->setText("Step:");
  ui->loan_monthly_also_first_label->setText("");
  ui->loan_interest_label->setText("");
  ui->loan_total_payment_label->setText("");
}

void View::on_amortized_loan_radio_clicked() {
  ui->turnable_label_1->setText("Payment Every Month:");
  ui->turnable_label_2->setText("");
  ui->turnable_label_3->setText("");
  ui->loan_last_payment_label->setText("");
  ui->loan_step_label->setText("");
  ui->loan_monthly_also_first_label->setText("");
  ui->loan_interest_label->setText("");
  ui->loan_total_payment_label->setText("");
}

void View::on_deposit_calc_button_clicked() {
  DepositInfo info;
  info.initial_amount = ui->deposit_initial->value();
  info.return_rate = ui->deposit_return->value();
  info.tax_rate = ui->deposit_tax->value();
  info.months = ui->deposit_after_spinBox->value();
  if (ui->returns_comboBox->currentText().toStdString() == "Monthly")
    info.withdrawals_monthly = true;
  if (ui->capitalization_checkBox->isChecked()) info.capitalization = true;
  info.addings = deposit_addings_;
  info.withdrawals = deposit_withdrawals_;

  DepositResult result;
  result = controller_->Deposit(info);

  ui->deposit_amount_total->setText(
      QString::number(result.withdrawal_total, 'f', 7));
  ui->deposit_interest_total->setText(
      QString::number(result.interest_total, 'f', 7));
  ui->deposit_tax_total->setText(QString::number(result.tax_total, 'f', 7));
  ShowMessage("Taxes not included.", 2500);
}

void View::on_deposit_add_button_clicked() {
  if (deposit_addings_.count(ui->deposit_add_month->value())) {
    ShowMessage("Нельзя пополнить дважды за один месяц.", 2500);
  } else {
    std::stringstream ss;
    int month = ui->deposit_add_month->value();
    double value = ui->added_value->value();
    deposit_addings_.insert(std::make_pair(month, value));
    ss << "month: " << month << " action: +" << value;
    ui->addings_info->append(QString::fromStdString(ss.str()));
  }
}

void View::on_pushButton_clicked() {
  ui->addings_info->clear();
  deposit_addings_.clear();
  deposit_withdrawals_.clear();
}

void View::on_deposit_withdraw_button_clicked() {
  if (deposit_withdrawals_.count(ui->deposit_withdraw_month->value())) {
    ShowMessage("Нельзя снять дважды за один месяц.", 2500);
  } else {
    std::stringstream ss;
    int month = ui->deposit_withdraw_month->value();
    double value = ui->withdrawed_value->value();
    deposit_withdrawals_.insert(std::make_pair(month, value));
    ss << "month: " << month << " action: -" << value;
    ui->addings_info->append(QString::fromStdString(ss.str()));
  }
}
}  // namespace s21
