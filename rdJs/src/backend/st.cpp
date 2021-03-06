#include "st.h"
#include <iostream>

using namespace ST;

void SymbolTable::newVariable(std::string id, ST::Kind kind, bool initialized){
  if (checkDeclaration(id)) yyerror("Variable %s alredy defined.", id.c_str());
  else {
    Symbol entry(kind, initialized);
    addSymbol(id,entry); //Adds variable to symbol table
  }
}

void SymbolTable::newFunction(std::string id, ST::Kind kind, int argsNumber){
  if (checkId(id)) yyerror("Function %s alredy defined.", id.c_str());
  else {
    Symbol entry(kind, true);
    entry.params = argsNumber;
    addSymbol(id,entry); //Adds variable to symbol table
  }
}

void SymbolTable::assignVariable(std::string id){
    if (!checkId(id)) {
      yyerror("Variable '%s' not declared.", id.c_str());
    } else {
      if(entryList[id].kind != ST::Kind::variable) yyerror("'%s' is a function.", id.c_str());
      entryList[id].initialized = true;
    }
}

void SymbolTable::useVariable(std::string id){
  if (!checkId(id)) {
    yyerror("Variable '%s' not declared.", id.c_str());
  } else {
    if (!entryList[id].initialized) yyerror("Variable '%s' not initialized.", id.c_str());
  }
}

void SymbolTable::useFunction(std::string id, int paramNumber){
  if (!checkId(id)) {
    yyerror("Variable '%s' not declared.", id.c_str());
  } else {
    int args = params(id);
    if (args != paramNumber)
      yyerror("Function '%s' expect %d parameters, received %d.", id.c_str(), args, paramNumber);
  }
}
