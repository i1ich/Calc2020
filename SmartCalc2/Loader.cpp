/* Plugins loader implementation file */
#include "Loader.h"



Loader::Loader(const char * Path): Plugins(Path)
{
}

std::vector<Operation*> Loader::getOpers(void)
{
  return Operations;
}

void Loader::MakeMap(void)
{
  for (int i = 0; i < Plugins.Paths.size(); i++)
  {
    LPCSTR name = _T(Plugins.Paths[i].c_str()); // load dll
    Operation *Oper =  new Operation(name);
    Operations.push_back(Oper);
    //Strings.push_back(Oper->getName());
    OperMap[Oper->getName()] = (Operations[i]);
  }
}


Loader::~Loader()
{
  for (int i = 0; i < Operations.size(); i++)
  {
    delete Operations[i];
    Operations[i] = nullptr;
  }
}
