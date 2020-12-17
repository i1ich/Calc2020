/* Poliz evaluation implementation file */
#include "Calculator.h"



Calculator::Calculator(std::map<std::string, Operation *> *opers)
{
  Opers = opers;
}

double Calculator::Compute(std::vector<Poliz::Symbol> in)
{
  std::stack<double> Out;
  int i = 0;
  double a = 0, b = 0;
  while (i < in.size())
  {
    if (in[i].T == Poliz::Symbol::NUM)
    {
      Out.push(std::stod(in[i].S));
      i++;
    }
    else if (in[i].T == Poliz::Symbol::POSTFIX || in[i].T == Poliz::Symbol::PREFIX )
    {
      Operation *tmp = (*Opers)[in[i].S];
      a = Out.top();
      Out.pop();
      Out.push(tmp->Result(a));
      i++;
    }
    else if(in[i].T == Poliz::Symbol::BINARY)
    {
      Operation *tmp = (*Opers)[in[i].S];
      b = Out.top();
      Out.pop();
      a = Out.top();
      Out.pop();
      Out.push(tmp->Result(a, b));
      i++;
    }
  }

  return Out.top();
}


Calculator::~Calculator()
{
}
