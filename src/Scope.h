//
// Created by zbl on 2021/11/24.
//

#ifndef PYTHON_INTERPRETER_SCOPE_H
#define PYTHON_INTERPRETER_SCOPE_H

#include <map>
#include <string>
#include <map>
#include "MyAny.h"
#include "int2048.h"
typedef std::pair<std::string, MyAny> ArguType;
typedef std::vector<ArguType> ParametersType;
class Scope{
public:
    std::map<std::string, MyAny> VarTable;
    Scope(){}
    void VarRegister(const std::string& str, const MyAny& data){ VarTable[str] = data;}
    bool VarExist(const std::string& str){return VarTable.find(str) == VarTable.end();}
    MyAny VarQuery(const std::string& str){return VarTable[str];}

};
#endif //PYTHON_INTERPRETER_SCOPE_H