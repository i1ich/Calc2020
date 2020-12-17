/* Operation loader implementation file */
#include "Operation.h"
  
const std::function<std::string(FARPROC)> Operation::__getString = 
    [](FARPROC Adress)
    {
      //using prototype = const char * (*)(void);
      //typedef const char * (__cdecl *prototype)(void);
      return (reinterpret_cast<const char * (*)(void)>(Adress))();
    };
const std::function<int(FARPROC)> Operation::__getInt = 
    [](FARPROC Adress)
    { 
      //using prototype = int (*)(void);
      //typedef int (__cdecl *prototype)(void);
      return (reinterpret_cast<int (*)(void)>(Adress))();
    };
const std::function<double(FARPROC, double)> Operation::__getResult1 = 
    [](FARPROC Adress, double a)
    { 
      //using prototype = int (*)(void);
      //typedef int (__cdecl *prototype)(void);
      return (reinterpret_cast<double (*)(double)>(Adress))(a);
    };
const std::function<double(FARPROC, double, double)> Operation::__getResult2 = 
    [](FARPROC Adress, double a, double b)
    { 
      //using prototype = int (*)(void);
      //typedef int (__cdecl *prototype)(void);
      return (reinterpret_cast<double (*)(double, double)>(Adress))(a, b);
    };
Operation::Operation(LPCSTR name)
{
  Name = name;
  Module = LoadLibrary(name);
  if (Module==NULL){std::cout << "\nбиблиотека не загружена!";}
  
  NameAddress = GetProcAddress(Module, FuncName);
  FARPROC TypeAddress = GetProcAddress(Module, TypeName); // Binary...
  if (TypeAddress != 0)
  {
    
    //typedef const char * (__cdecl *prototype)(void);
    //const char *Type1 = ((prototype)TypeAddress)();
    std::string Type1 = __getString(TypeAddress);
    //std::string S( TypeAddress);
    if (Type1 == "BINARY")
      Type = OP_TYPE::BINARY;
    else if (Type1 == "PREFIX")
      Type = OP_TYPE::PREFIX;
    else if (Type1 == "POSTFIX")
      Type = OP_TYPE::POSTFIX;
    else
      {std::cout << "\nбиблиотека не загружена!(wrong type)";}
  }
  if (Type == OP_TYPE::BINARY)
  {
    FARPROC PriorityAddress =  GetProcAddress(Module, PriorityName);
    if (PriorityAddress != 0)
    {
      /*typedef int (__cdecl *prototype)(void);
      Priority = ((prototype)PriorityAddress)();*/
      Priority = __getInt(PriorityAddress);
    }
  }
  ResultAddress = GetProcAddress(Module, ResName);
}

std::string Operation::getName(void)
{
  if (NameAddress != 0)
  {
    /*typedef const char * (__cdecl *prototype)(void);
    return std::string(((prototype)NameAddress)());*/
    return __getString(NameAddress);
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
    //typedef double (__cdecl *prototype)(double a, double b);
    //return ((prototype)ResultAddress)(a, b);
    return __getResult2(ResultAddress, a, b);
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
    //typedef double (__cdecl *prototype)(double a);
    //return ((prototype)ResultAddress)(a);
    return __getResult1(ResultAddress, a);
  }
  std::cout << "\nбиблиотека не загружена(result)!";
  return 0.0;
}
Operation::~Operation()
{
  FreeLibrary(Module);
}
