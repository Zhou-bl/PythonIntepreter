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
    int dep;
    std::vector<std::map<std::string, MyAny>> VarTable;
    Scope() : dep(0) {VarTable.push_back(std::map<std::string, MyAny>());}
    void VarRegister(const std::string& str, const MyAny& data){ VarTable[dep][str] = data;}
    //bool VarExist(const std::string& str){return VarTable.find(str) == VarTable.end();}
    MyAny VarQuery(const std::string& str){return VarTable[dep][str];}
    MyAny &operator[](const std::string& name){
        if(VarTable[dep].find(name) != VarTable[dep].end()) return VarTable[dep][name];
        return VarTable[0][name];//全局变量
    }
    void AddLevel(){
        dep++;
        VarTable.push_back(std::map<std::string, MyAny>());
    }
    void DelLevel(){
        dep--;
        VarTable.pop_back();
    }

};
class Function{
public:
    std::map<std::string, Python3Parser::SuiteContext *> suite;//函数体
    std::map<std::string, ParametersType> para;//参数列表
    Python3Parser::SuiteContext *&Suite(const std::string& name){//执行函数体
        return suite[name];
    }
    ParametersType &Parameters(const std::string& name){//获取参数列表
        return para[name];
    }
};
#endif //PYTHON_INTERPRETER_SCOPE_H