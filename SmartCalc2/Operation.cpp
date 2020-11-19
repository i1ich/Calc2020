#include "Operation.h"



Operation::Operation(LPCSTR name)
{
  Name = name;
  Module = LoadLibrary(name);
  if (Module==NULL){std::cout << "\nбиблиотека не загружена!";}
  
  NameAddress = GetProcAddress(Module, FuncName);
  FARPROC TypeAddress = GetProcAddress(Module, TypeName); // Binary...
  if (TypeAddress != 0)
  {
    typedef const char * (__cdecl *prototype)(void);
    const char *Type1 = ((prototype)TypeAddress)();
    if (strcmp(Type1, "BINARY") == 0)
      Type = OP_TYPE::BINARY;
    else if (strcmp(Type1, "PREFIX") == 0)
      Type = OP_TYPE::PREFIX;
    else if (strcmp(Type1, "POSTFIX") == 0)
      Type = OP_TYPE::POSTFIX;
    else
      {std::cout << "\nбиблиотека не загружена!(wrong type)";}
  }
  if (Type == OP_TYPE::BINARY)
  {
    FARPROC PriorityAddress =  GetProcAddress(Module, PriorityName);
    if (PriorityAddress != 0)
    {
      typedef int (__cdecl *prototype)(void);
      Priority = ((prototype)PriorityAddress)();
    }
  }
  ResultAddress = GetProcAddress(Module, ResName);
}

const char * Operation::getName(void)
{
  if (NameAddress != 0)
  {
    typedef const char * (__cdecl *prototype)(void);
    return ((prototype)NameAddress)();
  }
  return "";
}

Operation::OP_TYPE Operation::getType(void)
{
  return Type;
}

int Operation::getPrior(void)
{
  return Priority;
}

double Operation::Result(double a, double b)
{
  if (Type != OP_TYPE::BINARY)
  {
    std::cout << "\nwrong call !";
    return 0.0;
  }
  if (NameAddress != 0)
  {
    typedef double (__cdecl *prototype)(double a, double b);
    return ((prototype)ResultAddress)(a, b);
  }
  std::cout << "\nбиблиотека не загружена(result)!";
  return 0.0;
}
double Operation::Result(double a)
{
  if(Type == OP_TYPE::BINARY)
  {
    std::cout << "\nwrong call !";
    return 0.0;
  }
  if (NameAddress != 0)
  {
    typedef double (__cdecl *prototype)(double a);
    return ((prototype)ResultAddress)(a);
  }
  std::cout << "\nбиблиотека не загружена(result)!";
  return 0.0;
}
Operation::~Operation()
{
  FreeLibrary(Module);
}
