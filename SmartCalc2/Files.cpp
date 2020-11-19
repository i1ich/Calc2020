#include "Files.h"

namespace fs = std::experimental::filesystem;

Files::Files(const char * Plugins)
{
  std::string path = Plugins;
  for (const auto & entry : fs::directory_iterator(path))
    Paths.push_back(entry.path().u8string());
}


Files::~Files()
{
}
