/* Reverse Polish notation implementation file */
#include "Poliz.h"


int Poliz::getPrior(Symbol Symb)
{
  switch (Symb.T)
  {
    case Symbol::Type::OPENB:
    case Symbol::Type::CLOSEB:
      return 0;
    case Symbol::Type::BINARY:
      for (int i = 0; i < Opers.size(); i++)
        if (Symb.S == Opers[i]->getName())
          return Opers[i]->getPrior();
      break;
  default:
    return -1;
  }
  /*if (Symb.S == ")" || Symb.S ==  "(" )
    return 0;*/
  /*if (Symb.T != Symbol::Type::BINARY)
    return -1;*/
  return -1;
}

Poliz::Poliz(std::vector<Operation *> opers)
{
  for (int i = 0; i < opers.size(); i++)
  {
    Opers.push_back(opers[i]);
  }
}

std::vector<Poliz::Symbol> Poliz::Convert(std::string S)
{
  std::vector<Symbol> V;
  std::stack<Symbol> Stack;
  std::vector<Symbol> Out;
  std::string tmp = "";
  int i = 0, l = S.length();

  for (i = 0; i < l; i++)
  {
    // push tmp
    if(tmp.size() != 0)
      V.push_back(tmp);
    tmp = "";
    // spaces skip
    while (S[i] == ' ')
      i++;
    // number 
    while (S[i] >= '0' && S[i] <= '9')
    {
      tmp.push_back(S[i]);
      i++;
    }
    if(tmp.size() != 0)
      V.push_back(tmp);
    tmp = "";
    // spaces skip
    while (S[i] == ' ')
      i++;
    // smth else

    while (S[i] != ' ' && S[i] != '(' && S[i] != ')' && !(S[i] >= '0' && S[i] <= '9'))
    { 
      tmp.push_back(S[i]);
      i++;
    }
    if(S[i] == ' ')
    {
      if(tmp.size() != 0)
        V.push_back(tmp);
      tmp = "";
      continue;
    }
    else
    {
      if(tmp.size() != 0)
        V.push_back(tmp);
      tmp = "";
      tmp.push_back(S[i]);
      V.push_back(tmp);
      tmp = "";
      continue;
    }
  }
  if(tmp.size() != 0 && tmp[0] != 0)
    V.push_back(tmp);
  tmp = "";
  l = V.size();
  for (i = 0; i < l; i++)
    V[i].T = Symbol::Define(V[i].S, Opers);
  // Start conversion

  for (i = 0; i < l; i++)
  {
    Symbol curr = V[i];
    tmp = V[i].S;
    Symbol::Type type = V[i].T;
    switch (type)
    {
    case Symbol::Type::NUM:
    case Symbol::Type::POSTFIX:
      Out.push_back(curr);
     break;
    case Symbol::Type::PREFIX:
    case Symbol::Type::OPENB:
      Stack.push(curr);
      break;
    case Symbol::Type::CLOSEB:
      while (1)
      {
        Symbol curr2 = Stack.top();
        if (curr2.T == Symbol::Type::OPENB)
        {
          Stack.pop();
          break;
        }
        else
        {
          Out.push_back(curr2);
        }
        Stack.pop();
        if (Stack.size() == 0)
        {
          printf("bug 1 ");
          break;
        }
      }
      break;
    case Symbol::Type::BINARY:
      if (Stack.size() == 0)
        Stack.push(curr);
      else
      {// Get Priority of stack top operation
        while (Stack.top().T == Symbol::Type::PREFIX || getPrior(Stack.top()) > getPrior(curr) || getPrior(Stack.top()) == getPrior(curr)) //!
        {
           Out.push_back(Stack.top());
           Stack.pop();
           if (Stack.size() == 0)
             break;
        }
        Stack.push(curr);
      }
      break;
    case Symbol::Type::__ERROR: // bug
      std::cout << "BUG REPORT ANSWER IS INCORRECT!\n";
    default:
      break;
    }
  }
  while (Stack.size() != 0)
  {
    Out.push_back(Stack.top());
    //! check
    Stack.pop();
  }


  return Out;
}


Poliz::~Poliz()
{
}
bool Poliz::Symbol::IsPrefix(std::string S, std::vector<Operation *> Opers)
  {
    for (int i = 0; i < Opers.size(); i++)
    {
      if(Opers[i]->getType() == Operation::PREFIX && S == Opers[i]->getName())
        return true;
    }
    return false;
  
  }
bool Poliz::Symbol::IsBinary(std::string S, std::vector<Operation *> Opers)
  {
    for (int i = 0; i < Opers.size(); i++)
    {
      std::string tmp = Opers[i]->getName(); // debug view
      if(Opers[i]->getType() == Operation::BINARY && S == tmp)
        return true;
    }
    return false;
  }
bool Poliz::Symbol::IsNum(std::string S)
  {
    int i;
    bool flag = true;
    for (i = 0; i < S.length(); i++)
    {
      if(!(S[i] >= '0' && S[i] <= '9'))
        if (S[i] == '.' && flag)
        {
          flag = false;
          continue;
        }
        else
          return false;
    }

    return true;
  }
bool Poliz::Symbol::IsPostfix(std::string S, std::vector<Operation *> Opers)
  {
    for (int i = 0; i < Opers.size(); i++)
    {
      if (Opers[i]->getType() == Operation::POSTFIX && S == Opers[i]->getName())
        return true;
    }
    return false;
  }
Poliz::Symbol::Symbol(std::string s)
{
  S = s;
  T = __ERROR;
}
Poliz::Symbol::Type Poliz::Symbol::Define(std::string s, std::vector<Operation *> Opers)
{
  if (IsNum(s))
    return Type::NUM;
  if (IsPostfix(s, Opers))
    return Type::POSTFIX;
  if (IsPrefix(s, Opers))
    return Type::PREFIX;
  if (s.length() == 1 && s[0] == '(')
    return Type::OPENB;
  if (s.length() == 1 && s[0] == ')')
    return Type::CLOSEB;
  if (IsBinary(s, Opers))
    return Type::BINARY;
  return Type::__ERROR;
}
