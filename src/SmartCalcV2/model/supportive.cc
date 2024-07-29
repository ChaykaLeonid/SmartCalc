#include "supportive.h"

bool s21::IfContains(string where, char symbol) {
  return where.find(symbol) != string::npos;
}
