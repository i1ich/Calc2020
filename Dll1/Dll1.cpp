// Dll1.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <string.h>

extern "C" __declspec(dllexport) const char * GetName(void);
extern "C" __declspec(dllexport) const char * GetName(void)
{
  return "^";
}
extern "C" __declspec(dllexport) const char * GetType(void);
extern "C" __declspec(dllexport) const char * GetType(void)
{
  return "BINARY";
}
extern "C" __declspec(dllexport) int GetPriority(void);
extern "C" __declspec(dllexport) int GetPriority(void)
{
  return 3;
}
extern "C" __declspec(dllexport) double Result(double a, double b);
extern "C" __declspec(dllexport) double Result(double a, double b)
{
  return pow(a, b);
}

