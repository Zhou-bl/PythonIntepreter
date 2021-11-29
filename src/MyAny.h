//
// Created by zbl on 2021/11/27.
//

#ifndef EVALVISITOR_H_MYANY_H
#define EVALVISITOR_H_MYANY_H

#include "int2048.h"
#include <string>
#include <vector>

enum Types {MyBool, MyInt, MyFloat, MyStr, MyNone};

class MyAny{
public:
    bool bool_data = 0;
    int2048 int_data = 0;
    double float_data = 0;
    std::string str_data;

    Types ty = MyNone;
    //构造函数
    MyAny(){}
    MyAny(const std::string& str){ty = MyStr; str_data = str;}
    MyAny(const bool& a){ty = MyBool; bool_data = a;}
    MyAny(const int2048& a){ty = MyInt; int_data = a;}
    MyAny(const double& a){ty = MyFloat; float_data = a;}

    int2048 FloatToInt(const double& a) const{
        double b = a;
        //if(b < 0) b -= 1.0;
        std::string tem = std::to_string(b);
        tem.resize(tem.length() - 7);//截取整数部分
        return int2048(tem);
    }

    //类型转换函数
    bool ToBool() const{
        if(ty == MyBool) return bool_data;
        if(ty == MyFloat) return (bool)float_data;
        if(ty == MyInt) return int_data == (int2048)0 ? false : true;
        if(ty == MyStr) return str_data.empty();
    }

    int2048 ToInt() const{
        if(ty == MyBool) return bool_data;
        if(ty == MyInt) return int_data;
        if(ty == MyStr) return str_data;
        if(ty == MyFloat) return FloatToInt(float_data);
    }

    double ToFloat() const{
        if(ty == MyBool) return bool_data;
        if(ty == MyInt) return (double)int_data;
        if(ty == MyStr) return std::stod(str_data);
        if(ty == MyFloat) return float_data;
    }

    std::string Tostr() const{
        if(ty == MyStr) return str_data;
        if(ty == MyFloat){
            std::string tem = std::to_string(float_data);
            return tem;
        }
        if(ty == MyBool){
            std::string tem = bool_data == 0 ? "0" : "1";
            return tem;
        }
        if(ty == MyInt){
            int tt, ll;
            std::string tem;
            if(!int_data.flag){tem[0] = '-';}
            for(int i = 0; i < int_data.len; ++i){
                tt = int_data.a[i];
                ll = tem.length();
                for(int j = 3; j >= 0; --j){
                    tem[ll + j] = tt % 10;
                    tt /= 10;
                }
            }
            return tem;
        }
    }

    friend MyAny operator+(const MyAny& lhs, const MyAny& rhs){
        MyAny ans;
        if(lhs.ty == MyStr && rhs.ty == MyStr){
            ans.ty = MyStr;
            ans.str_data = lhs.str_data + rhs.str_data;
            return ans;
        }
        if(lhs.ty == MyInt && rhs.ty == MyInt){
            ans.ty = MyInt;
            ans.int_data = lhs.int_data + rhs.int_data;
            return ans;
        }
        if(lhs.ty == MyFloat && rhs.ty == MyFloat){
            ans.ty == MyFloat;
            ans.float_data = lhs.float_data + rhs.float_data;
            return ans;
        }
        if(lhs.ty == MyBool && rhs.ty == MyBool){
            ans.ty = MyBool;
            ans.bool_data = lhs.bool_data + rhs.bool_data;
            return ans;
        }
        if(lhs.ty == MyFloat){
            ans.ty = MyFloat;
            ans.float_data = lhs.float_data + rhs.ToFloat();
            return ans;
        }
        if(rhs.ty == MyFloat){
            ans.ty = MyFloat;
            ans.float_data = rhs.float_data + lhs.ToFloat();
            return ans;
        }
        if(rhs.ty == MyInt && lhs.ty == MyBool){
            ans.ty = MyInt;
            ans.int_data = rhs.int_data + lhs.ToInt();
            return ans;
        }
        if(lhs.ty == MyInt && rhs.ty == MyBool){
            ans.ty == MyInt;
            ans.int_data = lhs.int_data + rhs.ToInt();
            return ans;
        }
    }
    friend MyAny operator-(const MyAny& lhs, const MyAny& rhs){
        MyAny ans;
        if(lhs.ty == MyInt && rhs.ty == MyInt){
            ans.ty = MyInt;
            ans.int_data = lhs.int_data - rhs.int_data;
            return ans;
        }
        if(lhs.ty == MyFloat && rhs.ty == MyFloat){
            ans.ty = MyFloat;
            ans.float_data = lhs.float_data - rhs.float_data;
            return ans;
        }
        if(lhs.ty == MyBool && rhs.ty == MyBool){
            ans.ty = MyBool;
            ans.bool_data = lhs.bool_data - rhs.bool_data;
            return ans;
        }
        if(lhs.ty == MyFloat){
            ans.ty = MyFloat;
            ans.float_data = lhs.float_data - rhs.ToFloat();
            return ans;
        }
        if(rhs.ty == MyFloat){
            ans.ty = MyFloat;
            ans.float_data = rhs.float_data - lhs.ToFloat();
            return ans;
        }
        if(rhs.ty == MyInt && lhs.ty == MyBool){
            ans.ty = MyInt;
            ans.int_data = rhs.int_data - lhs.ToInt();
            return ans;
        }
        if(lhs.ty == MyInt && rhs.ty == MyBool){
            ans.ty = MyInt;
            ans.int_data = lhs.int_data - rhs.ToInt();
            return ans;
        }
    }
    friend MyAny operator * (const MyAny& lhs, const MyAny& rhs){
        MyAny ans;
        if(lhs.ty == MyStr){
            ans.ty = MyStr;
            for(int2048 i = 1; i <= rhs.ToInt(); i = i + (int2048)1) ans.str_data += lhs.str_data;
            return ans;
        }
        if(rhs.ty == MyStr){
            ans.ty = MyStr;
            for(int2048 i = 1; i <= lhs.ToInt(); i = i + (int2048)1) ans.str_data += rhs.str_data;
            return ans;
        }
        if(lhs.ty == MyInt && rhs.ty == MyInt){
            ans.ty = MyInt;
            ans.int_data = lhs.int_data * rhs.int_data;
            return ans;
        }
        if(lhs.ty == MyFloat && rhs.ty == MyFloat){
            ans.ty = MyFloat;
            ans.float_data = lhs.float_data * rhs.float_data;
            return ans;
        }
        if(lhs.ty == MyBool && rhs.ty == MyBool){
            ans.ty = MyBool;
            ans.bool_data = lhs.bool_data * rhs.bool_data;
            return ans;
        }
        //double * other type
        if(lhs.ty == MyFloat){
            ans.ty = MyFloat;
            ans.float_data = lhs.float_data * rhs.ToFloat();
            return ans;
        }
        if(rhs.ty == MyFloat){
            ans.ty = MyFloat;
            ans.float_data = rhs.float_data * lhs.ToFloat();
            return ans;
        }
        //int * other type
        if(lhs.ty == MyInt){
            ans.ty = MyInt;
            ans.int_data = lhs.int_data * rhs.ToInt();
            return ans;
        }
        if(rhs.ty == MyInt){
            ans.ty = MyInt;
            ans.int_data = rhs.int_data * lhs.ToInt();
            return ans;
        }
    }
    friend MyAny operator % (const MyAny& lhs, const MyAny& rhs){
        MyAny ans;
        ans.ty = MyInt;
        ans.int_data = lhs.int_data % rhs.int_data;
    }

    MyAny &operator += (const MyAny& rhs){
        return *this = *this + rhs;
    }
    MyAny &operator -= (const MyAny& rhs){
        return *this = *this - rhs;
    }
    MyAny &operator *= (const MyAny& rhs){
        return *this = *this * rhs;
    }
    MyAny &operator %= (const MyAny& rhs){
        return *this = *this * rhs;
    }
    friend MyAny FloatDiv(const MyAny& lhs, const MyAny& rhs){
        MyAny ans;
        ans.ty = MyFloat;
        ans.float_data = lhs.ToFloat() / rhs.ToFloat();
        return ans;
    }
    friend MyAny IntDiv(const MyAny& lhs, const MyAny& rhs){
        MyAny ans;
        ans.ty = MyInt;
        ans.int_data = lhs.int_data / rhs.int_data;
        return ans;
    }

    friend std::ostream &operator << (std::ostream &lhs, MyAny rhs){
        if(rhs.ty == MyFloat){
            lhs << std::fixed << std::setprecision(6) << rhs.float_data;
            return lhs;
        }
        if(rhs.ty == MyInt){
            lhs << rhs.int_data;
            return lhs;
        }
        if(rhs.ty == MyBool){
            lhs << (rhs.bool_data ? "True" : "False");
            return lhs;
        }
        if(rhs.ty == MyStr){
            lhs << rhs.str_data;
            return lhs;
        }
        lhs << "None";
        return lhs;
    }

};

#endif //EVALVISITOR_H_MYANY_H
