/* Reverse Polish notation declaration file */
#pragma once
#include <string>
#include <vector>
#include <stack>
#include <algorithm>    // std::find_if
#include "Input.h"
#include "Operation.h"
// Reverse Polish notation class
class Poliz : public Input
{
public:
  struct Symbol
  {
    enum Type // "symbol" type
    {
      NUM,
      POSTFIX,
      PREFIX,
      OPENB,
      CLOSEB,
      BINARY,
      __ERROR
    };
  private:
  static bool IsPrefix(std::string S, std::vector<Operation *> Opers);
  static bool IsBinary(std::string S, std::vector<Operation *> Opers);
  static bool IsNum(std::string S);
  static bool IsPostfix(std::string S, std::vector<Operation *> Opers);
  public:
    std::string S; // Symbol
    Type T;        // Symbol type
    Symbol(std::string s);
    static Type Define(std::string s, std::vector<Operation *> Opers);
  };
private:
  std::vector<Operation *> Opers;
  int getPrior( Symbol S );
public:
  Poliz(std::vector<Operation *> opers);
  std::vector<Symbol> Convert( std::string S );
  ~Poliz();
};

