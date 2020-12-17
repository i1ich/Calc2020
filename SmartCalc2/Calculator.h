/* Poliz evaluation declaration file */
#pragma once
#include <map>
#include <functional>
#include "Poliz.h"
// Calculcate POLIZ equation class
class Calculator
{
  std::map<std::string, Operation *> *Opers;
public:
  Calculator(std::map<std::string, Operation *> *opers);
  double Compute(std::vector<Poliz::Symbol> in);
  ~Calculator();
};

