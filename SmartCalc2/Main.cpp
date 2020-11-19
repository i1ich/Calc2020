#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <vector>
#include <experimental/filesystem>
//namespace fs = std::experimental::filesystem;
using namespace std;

#include "Loader.h"
#include "Poliz.h"
#include "Calculator.h"
int main()
{
  //vector<string> Paths;

  //std::system("chcp 1251");
  const std::string path = "\plugins";

  std::string str_in;
  Input In;
  str_in = In.getStr();
  Loader L(path.c_str());
  L.MakeMap();
  Poliz P(L.getOpers());
  //vector<Poliz::Symbol> Pol = P.Convert("3 + 4 * 2 / (1 - 5)^2");
  vector<Poliz::Symbol> Pol = P.Convert(str_in);
  Calculator Calc(&L.OperMap);
  double ans = Calc.Compute(Pol);
  std::cout << ans;
  std::cout << "\n";
  std::system("pause");
  /*for (const auto & entry : fs::directory_iterator(path))
    Paths.push_back(entry.path().u8string());


LPCSTR name = _T(Paths[0].c_str()); // загрузка модуля DLL*/
Operation *A = L.OperMap["-"];
/*
LPCSTR name = _T("plugins/Dll1"); // загрузка модуля DLL
HINSTANCE le_module = LoadLibrary(name);
if(le_module==NULL){std::cout << "\nбиблиотека не загружена!";}

LPCSTR func_name = "dll_function"; // название загружаемой функции
FARPROC adresse_la_func = GetProcAddress(le_module, func_name);
if (adresse_la_func!=0)
{
  std::cout << "\nadresse_la_func=" << adresse_la_func;
  typedef void (__cdecl *прототип)(int);
  ((прототип)adresse_la_func)(5);
}

FreeLibrary(le_module);
*/
//std::cout << A->Result(4, 1);
//std::cout << "\n";
//std::system("pause");
return 0;
}