#include <QApplication>

#include "model/model.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::View w(nullptr, &controller);
  w.show();
  return a.exec();
}
