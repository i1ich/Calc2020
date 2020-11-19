#pragma once
#include <map>
#include <tchar.h>
#include "Operation.h"
#include "Files.h"
class Loader
{
private:
  Files Plugins;
  std::vector<Operation *> Operations;
public:
  std::map<std::string, Operation *> OperMap; // operations and functions
  //std::vector<std::string> Strings; // all operations and functions strings
  Loader(const char * Path);
  std::vector<Operation *> getOpers( void );
  void MakeMap(void);
  ~Loader();
};

