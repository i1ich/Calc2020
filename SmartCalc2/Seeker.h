/* Seeker plugins (paths) declaration file */
#pragma once
#include <experimental/filesystem>
#include <vector>
#include <string>
/* Seekeer plugins class */
class Seeker
{
public:
  std::vector<std::string> Paths;


  Seeker(const char * Plugins);
  ~Seeker();
};

