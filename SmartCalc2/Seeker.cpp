/* Seeker plugins (paths) declaration file */
#include "Seeker.h"

namespace fs = std::experimental::filesystem;

Seeker::Seeker(const char * Plugins)
{
  std::string path = Plugins;
  for (const auto & entry : fs::directory_iterator(path))
    Paths.push_back(entry.path().u8string());
}


Seeker::~Seeker()
{
}
