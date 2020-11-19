#pragma once
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <vector>
// Operation loader from dll class
class Operation
{
public:
  enum OP_TYPE
  {
    BINARY,
    PREFIX,
    POSTFIX
  };

private:
  const LPCSTR FuncName = "GetName"; // Any other name will be error
  const LPCSTR ResName = "Result"; // название загружаемой функции
  const LPCSTR TypeName = "GetType"; // название загружаемой функции POSTFIX|PREFIX|BINARY
  const LPCSTR PriorityName = "GetPriority"; // название загружаемой функции приоритет: 1 2 3
protected:
  LPCSTR Name; // file name
  HINSTANCE Module;
  FARPROC NameAddress;
  FARPROC ResultAddress;
  OP_TYPE Type;
  int Priority;
public:
  // File name
  Operation(LPCSTR name);
  const char *getName( void );
  OP_TYPE getType( void );
  int getPrior( void );
  double Result( double a, double b );
  double Result( double a );
  ~Operation();
};

