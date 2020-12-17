/* Console input implementation file */
#include "Input.h"



Input::Input(): Out("")
{
}

std::string Input::getStr(void)
{
  std::getline(std::cin, Out);
  return Out;
}


Input::~Input()
{
}
