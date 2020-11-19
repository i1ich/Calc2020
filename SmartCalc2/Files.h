#pragma once
#include <experimental/filesystem>
#include <vector>
#include <string>
class Files
{
public:
  std::vector<std::string> Paths;


  Files(const char * Plugins);
  ~Files();
};

