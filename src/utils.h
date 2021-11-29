//
// Created by zbl on 2021/11/24.
//

#ifndef PYTHON_INTERPRETER_UTILS_H
#define PYTHON_INTERPRETER_UTILS_H

#include <string>

static int StringToInt(const std::string& str){
    int res = 0;
    for(int i = 0; i < str.length(); ++i){
        res = res * 10 + str[i] - '0';
    }
    return res;
}


#endif //PYTHON_INTERPRETER_UTILS_H
