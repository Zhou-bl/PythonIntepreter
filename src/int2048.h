//
// Created by zbl on 2021/11/27.
//

#ifndef SJTU_BIGINTEGER
#define SJTU_BIGINTEGER

// Integer 1:
// 实现一个有符号的大整数类，只需支持简单的加减

// Integer 2:
// 实现一个有符号的大整数类，支持加减乘除，并重载相关运算符

// 请不要使用除了以下头文件之外的其它头文件
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <complex>

// 请不要使用 using namespace std;
    const int Max_Size = 5005;
    const int Base_Len = 4;
    const int Base = 10000;
    class int2048
    {
        // todo
    public:
        std ::vector<int> a;
        int len;
        bool flag; //大于等于零 ：flag = 1；负数 ：flag = 0；
        // 构造函数

        int2048(){
            a.clear();
            a.push_back(0);
            len = 1;
            flag = 1;
        }
        int2048(long long x){
            a.clear();
            len = 0;
            if(x < 0){
                flag = 0;
                x = -x;
            }
            else flag = 1;
            do {
                ++len;
                a.push_back(x % Base);
                x /= Base;
            }while(x);
        }
        int2048(const std::string &s){
            a.clear();
            len = 0;
            int l = s.length(),cur = 0,k,sum;
            flag = s[0] == '-' ? 0 : 1;
            if(flag){
                len = l / Base_Len + (l % Base_Len ? 1 : 0);
                for(int i = l - 1; i >= 0; i -= Base_Len){
                    k = i - Base_Len + 1;
                    if(k < 0) k = 0;
                    sum = 0;
                    for(int j = k; j <= i; ++j)
                        sum = sum * 10 + s[j] - '0';
                    a.push_back(sum);
                }
            }
            else{
                l--;
                len = l / Base_Len + (l % Base_Len ? 1 : 0);
                for(int i = l; i >= 1; i -= Base_Len){
                    k = i - Base_Len + 1;
                    if(k < 1) k = 1;
                    sum = 0;
                    for(int j = k; j <= i; ++j)
                        sum = sum * 10 + s[j] - '0';
                    a.push_back(sum);
                }
            }
            if(!a[len - 1]) flag = 1;
        }
        int2048(const int2048 &tem){
            a.clear();
            flag = tem.flag;
            len = tem.len;
            for(int i = 0; i < tem.a.size(); ++i)
                a.push_back(tem.a[i]);
        }

        // 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
        // 如果需要，可以自行增加其他所需的函数
        // =================================== Integer1 ===================================

        // 读入一个大整数
        void read(const std::string &s){
            a.clear();
            len = 0;
            int l = s.length(),cur = 0,k,sum;
            flag = s[0] == '-' ? 0 : 1;
            if(flag){
                len = l / Base_Len + (l % Base_Len ? 1 : 0);
                for(int i = l - 1; i >= 0; i -= Base_Len){
                    k = i - Base_Len + 1;
                    if(k < 0) k = 0;
                    sum = 0;
                    for(int j = k; j <= i; ++j)
                        sum = sum * 10 + s[j] - '0';
                    a.push_back(sum);
                }
            }
            else{
                l--;
                len = l / Base_Len + (l % Base_Len ? 1 : 0);
                for(int i = l; i >= 1; i -= Base_Len){
                    k = i - Base_Len + 1;
                    if(k < 1) k = 1;
                    sum = 0;
                    for(int j = k; j <= i; ++j)
                        sum = sum * 10 + s[j] - '0';
                    a.push_back(sum);
                }
            }
            if(!a[len - 1]) flag = 1;
        }
        // 输出储存的大整数
        void print(){
            if(!flag && a[len - 1]) putchar('-');
            printf("%d",a[len - 1]);
            for(int i = len - 2; i >= 0; --i){
                printf("%04d",a[i]);
            }
        }

        void trim(){
            while (!get(len - 1) && len - 1 > 0){
                len--;
                a.pop_back();
            }
        }

        int cmp(int2048 a, int2048 b){
            for(int i = ( a.len >= b.len ? a.len : b.len ) - 1; i >= 0; --i){
                if(a.get(i) > b.get(i)) return 1;
                if(a.get(i) < b.get(i)) return -1;
            }
            return 0;
        }
        void swap(int2048 &a, int2048 &b){
            int2048 tem;
            tem = a;
            a = b;
            b = tem;
        }
        // 加上一个大整数
        int2048 &None_Flag_Add(const int2048 &b){//无符号绝对值相加
            int x = 0;
            for (int i = 0; i < len || i < b.len; ++i){
                int tem;
                if (i >= len) a.push_back(0);
                if (i >= b.len)
                    tem = get(i) + x;
                else tem = get(i) + b.get(i) + x;
                x = tem / Base;
                tem %= Base;
                a[i] = tem;
            }
            if (len < b.len) len = b.len;
            if (x != 0) {
                len++;
                a.push_back(x);
            }
            return *this;
        }
        int2048 &None_Flag_Minus(const int2048 &b){//无符号绝对值大的减绝对值小的
            for (int i = 0; i < len || i < b.len; ++i){
                int temp;
                if (i >= b.len)
                    temp = get(i);
                else
                    temp = get(i) - b.get(i);
                if (temp < 0) {
                    temp += Base;
                    a[i + 1]--;
                }
                a[i] = temp;
            }
            trim();
            return *this;
        }
        int2048 &add(const int2048 &b){
            if ((flag && b.flag) || (!flag && !b.flag)){
                None_Flag_Add(b);
            } else {
                int f = cmp(*this, b);
                if (f == 1) {
                    None_Flag_Minus(b);
                } else {
                    int2048 t(b);
                    swap(*this, t);
                    None_Flag_Minus(t);
                }
            }
            return *this;
        }
        // 输出两个大整数之和
        friend int2048 add(int2048 a,const int2048 &b){
            int2048 c(a);
            c.add(b);
            return c;
        }

        // 减去一个大整数
        int2048 &minus(const int2048 &b){
            int f = cmp(*this, b);
            if ((f == 1) && ((flag && b.flag) || (!flag && !b.flag))) {
                None_Flag_Minus(b);
            } else if ((f == -1) && ((flag && b.flag) || (!flag && !b.flag))) {
                int2048 t(b);
                t.flag ^= 1;
                swap(*this, t);
                None_Flag_Minus(t);
            } else if (f == 0) {
                if ((flag && b.flag) || (!flag && !b.flag)) None_Flag_Minus(b);
                else None_Flag_Add(b);
            } else {
                None_Flag_Add(b);
            }
            return *this;
        }
        // 输出两个大整数之差
        friend int2048 minus(int2048 a, const int2048 &b){
            int2048 c(a);
            c.minus(b);
            return c;
        }

        // =================================== Integer2 ===================================

        int get(unsigned pos) const {
            if (pos >= a.size()) return 0;
            return a[pos];
        }

        int2048 &operator=(const int2048 &tem){
            a.clear();
            flag = tem.flag;
            len = tem.len;
            for(int i = 0; i < tem.a.size(); ++i)
                a.push_back(tem.a[i]);
            return *this;
        }

        int2048 &operator+=(int2048 tem){
            add(tem);
            return *this;
        }
        friend int2048 operator+(int2048 a, const int2048 &b){
            a += b;
            return a;
        }

        int2048 &operator-=(int2048 tem){
            minus(tem);
            return *this;
        }
        friend int2048 operator-(int2048 a, const int2048 &b){
            a -= b;
            return a;
        }

        int2048 &operator*=(const int2048 &tem){
            int all_len = len + tem.len;
            if((flag && tem.flag) || (!flag && !tem.flag)) flag = 1;
            else flag = 0;
            int2048 c(0);
            for(int i = len; i <= all_len + 1; ++i) a.push_back(0);
            for(int i = 0; i <= all_len + 1; ++i) c.a.push_back(0);
            for(int i = 0; i < len; ++i){
                for(int j = 0; j < tem.len; ++j){
                    c.a[i + j] += tem.a[j] * a[i];
                    c.a[i + j + 1] += c.a[i + j] / Base;
                    c.a[i + j] %= Base;
                }
            }
            for(int i = len + tem.len ; i >= 0; --i)
                a[i] = c.a[i];
            for(int i = len + tem.len - 1; i >= 0; --i)
                if(a[i] || !i){
                    len = i + 1;
                    break;
                }
            return *this;
        }
        friend int2048 operator*(int2048 a, const int2048 &b){
            a *= b;
            return a;
        }

        int2048 &operator/=(const int2048 &divisor){
            int max_len = len >= divisor.len ? len : divisor.len;
            int2048 ans(0), a(*this),b(divisor),product(0),multiple(0);
            for(int i = 0; i <= max_len; ++i){
                ans.a.push_back(0);
                product.a.push_back(0);
                multiple.a.push_back(0);
            }
            a.flag = 1;b.flag = 1;
            int maxsize = a.len - b.len + 1;
            int ll ,rr ,mid ,cur;
            if(a < b) return *this = int2048(0);
            while(a >= b){
                multiple = int2048(0);
                multiple.a.resize(max_len + 1,0);
                multiple.flag = 1;
                multiple.len = maxsize;
                multiple.a[maxsize - 1] = 1;
                product = b * multiple;
/*
                while(a >= product){
                    a -= product;
                    ans += multiple;
                }
*/
                //double fake_q = a.a[a.len - 1] / product.a[product.len - 1];

                ll = 0; rr = Base - 1,cur = 0;
                while(ll <= rr){
                    mid = ll + rr >> 1;
                    if((int2048)mid * product <= a){
                        cur = cur >= mid ? cur : mid;
                        ll = mid + 1;
                    }
                    else rr = mid - 1;
                }
                ans += multiple * (int2048)cur;
                a -= product * (int2048)cur;

                maxsize--;
            }
            if((flag && divisor.flag) || (!flag && !divisor.flag)) ans.flag = 1;
            else ans.flag = 0;
            if(!ans.flag) ans -= int2048(1);
            *this = ans;
            return *this;
        }
        friend int2048 operator / (int2048 a, const int2048 &b){
            a /= b;
            return a;
        }

        friend int2048 operator % (const int2048 &a, const int2048 &b) {
            return a - a / b * b;
        }

        int2048 operator %= (const int2048& tem){
            *this = *this % tem;
            return *this;
        }

        friend std::istream &operator>>(std::istream &input, int2048 &tem){
            std::string s;
            input >> s;
            tem.read(s);
            return input;
        }
        friend std::ostream &operator<<(std::ostream &output, const int2048 &tem){
            int2048 t(tem);
            t.print();
            return output;
        }

        inline friend bool operator==(const int2048 &a, const int2048 &b){
            if(a.flag != b.flag) return false;
            for(int i = ( a.len >= b.len ? a.len : b.len ) - 1; i >= 0; --i)
                if(a.get(i) != b.get(i)) return false;
            return true;
        }
        inline friend bool operator!=(const int2048 &a, const int2048 &b){
            if(a.flag != b.flag) return true;
            for(int i = ( a.len >= b.len ? a.len : b.len ) - 1; i >= 0; --i)
                if(a.get(i) != b.get(i)) return true;
            return false;
        }
        inline friend bool operator<(const int2048 &a, const int2048 &b){
            if(!a.flag && b.flag) return true;
            if(a.flag && !b.flag) return false;
            if(a.flag && b.flag){
                for(int i = ( a.len >= b.len ? a.len : b.len ) - 1; i >= 0; --i){
                    if(a.get(i) < b.get(i)) return true;
                    if(a.get(i) > b.get(i)) return false;
                }
                return false;
            }
            if(!a.flag && !b.flag){
                for(int i = ( a.len >= b.len ? a.len : b.len ) - 1; i >= 0; --i){
                    if(a.get(i) > b.get(i)) return true;
                    if(a.get(i) < b.get(i)) return false;
                }
                return false;
            }
        }
        inline friend bool operator>(const int2048 &a, const int2048 &b){
            if(!a.flag && b.flag) return false;
            if(a.flag && !b.flag) return true;
            if(a.flag && b.flag){
                for(int i = ( a.len >= b.len ? a.len : b.len ) - 1; i >= 0; --i){
                    if(a.get(i) > b.get(i)) return true;
                    if(a.get(i) < b.get(i)) return false;
                }
                return false;
            }
            if(!a.flag && !b.flag){
                for(int i = ( a.len >= b.len ? a.len : b.len ) - 1; i >= 0; --i){
                    if(a.get(i) < b.get(i)) return true;
                    if(a.get(i) > b.get(i)) return false;
                }
                return false;
            }
        }
        inline friend bool operator<=(const int2048 &a, const int2048 &b){
            if(a > b) return false;
            return true;
        }
        inline friend bool operator>=(const int2048 &a, const int2048 &b){
            if(a < b) return false;
            return true;
        }
        bool Is_Zero() const {
            if(len == 1 && !a[0]) return 1;
            return 0;
        }
        operator bool() const {return !Is_Zero();}
        operator double() const {
            double ans = 0;
            for(int i = 0; i < len; ++i){
                ans = ans * Base + a[i];
            }
            if(!flag) ans *= -1;
            return ans;
        }
    };

#endif

