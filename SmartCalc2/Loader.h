/* Plugins loader declaration file */
#pragma once
#include <map>
#include <tchar.h>
#include "Operation.h"
#include "Seeker.h"
/* Plugins loader class */
class Loader
{
private:
  // Seeker plugins
  Seeker Plugins;
  std::vector<Operation *> Operations;
public:
  std::map<std::string, Operation *> OperMap; // operations and functions
  //std::vector<std::string> Strings; // all operations and functions strings
  Loader(const char * Path);
  std::vector<Operation *> getOpers( void );
  void MakeMap(void);
  ~Loader();
};

