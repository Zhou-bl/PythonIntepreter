#ifndef PYTHON_INTERPRETER_EVALVISITOR_H
#define PYTHON_INTERPRETER_EVALVISITOR_H


#include "Python3BaseVisitor.h"
#include "Scope.h"
#include "utils.h"
#include "int2048.h"
#include "MyAny.h"

static Scope VarScope;
static MyAny return_value;
enum StmtRes { kNormal, kBreak, kContinue, kReturn };
class EvalVisitor: public Python3BaseVisitor {

//todo:override all methods of Python3BaseVisitor
public:

    static MyAny &GetValue(antlrcpp::Any tmp){
        if(tmp.is<std::string>()) return VarScope.VarTable[tmp.as<std::string>()];
        else return tmp.as<MyAny>();
    }

    virtual antlrcpp::Any visitFile_input(Python3Parser::File_inputContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFuncdef(Python3Parser::FuncdefContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitParameters(Python3Parser::ParametersContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTypedargslist(Python3Parser::TypedargslistContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTfpdef(Python3Parser::TfpdefContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitStmt(Python3Parser::StmtContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) override {
        return visitChildren(ctx);
    }


    virtual antlrcpp::Any visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) override {
        auto testlistArray = ctx->testlist();
        if (testlistArray.size() == 1) {
            visitTestlist(testlistArray[0]);
            return MyAny();
        }

        std::string varName = testlistArray[0]->getText();
        MyAny varData = visitTestlist(testlistArray[1]);

        VarScope.VarRegister(varName, varData);
        return MyAny();
    }


    virtual antlrcpp::Any visitAugassign(Python3Parser::AugassignContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitIf_stmt(Python3Parser::If_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitWhile_stmt(Python3Parser::While_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSuite(Python3Parser::SuiteContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTest(Python3Parser::TestContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitOr_test(Python3Parser::Or_testContext *ctx) override {
        auto And_Array = ctx->and_test();
        if(And_Array.size() == 1) return visitAnd_test(And_Array[0]);
        bool tmp = 0;
        for(auto it : And_Array){
            tmp = tmp || GetValue(visitAnd_test(it));
            if(tmp) return MyAny(tmp);//短路
        }
        return MyAny(tmp);
    }

    virtual antlrcpp::Any visitAnd_test(Python3Parser::And_testContext *ctx) override {
        auto Not_Array = ctx->not_test();
        if(Not_Array.size() == 1) return visitNot_test(Not_Array[0]);
        bool tmp = 1;
        for(auto it : Not_Array){
            tmp = tmp && GetValue(visitNot_test(it));
            if(!tmp) return MyAny(tmp);//短路
        }
        return MyAny(tmp);
    }

    virtual antlrcpp::Any visitNot_test(Python3Parser::Not_testContext *ctx) override {
        if(ctx->comparison()) return visitComparison(ctx->comparison());
        return !GetValue(visitNot_test(ctx->not_test()));
    }

    virtual antlrcpp::Any visitComparison(Python3Parser::ComparisonContext *ctx) override {//(四则表达式在前)
        auto Arith_Array = ctx->arith_expr();
        //无 关系运算符，只有四则运算：
        if(Arith_Array.size() == 1) return visitArith_expr(Arith_Array[0]);
        auto Op_Array = ctx->comp_op();
        int Num = Op_Array.size();//获取操作数，速度快
        MyAny a = GetValue(visitArith_expr(Arith_Array[0])), b;
        std::string tmpOp;
        for(int i = 1; i <= Num; ++i){//i-1 操作数, i 四则运算表达式
            b = GetValue(visitArith_expr(Arith_Array[i]));
            tmpOp = Op_Array[i - 1]->getText();
            //短路
            if(tmpOp == "==" && a != b) return MyAny(false);
            if(tmpOp == "!=" && a == b) return MyAny(false);
            if(tmpOp == ">" && a <= b) return MyAny(false);
            if(tmpOp == "<" && a >= b) return MyAny(false);
            if(tmpOp == ">=" && a < b) return MyAny(false);
            if(tmpOp == "<=" && a > b) return MyAny(false);
            a = b;
        }
        return MyAny(true);
    }

    virtual antlrcpp::Any visitComp_op(Python3Parser::Comp_opContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitArith_expr(Python3Parser::Arith_exprContext *ctx) override {
        auto termArray = ctx->term();
        if (termArray.size() == 1) return visitTerm(termArray[0]);
        auto opArray = ctx->addorsub_op();

        // ret = termArray[0];
        MyAny ret = visitTerm(termArray[0]);
        for (int i = 1; i < termArray.size(); ++i) {
            std::string tmpOp = opArray[i-1]->getText();
            if(tmpOp == "+") ret += visitTerm(termArray[i]);
            if(tmpOp == "-") ret -= visitTerm(termArray[i]);
        }
        return ret;
    }

    virtual antlrcpp::Any visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTerm(Python3Parser::TermContext *ctx) override {
        auto factorArray = ctx->factor();
        if (factorArray.size() == 1) return visitFactor(factorArray[0]);
        auto opArray = ctx->muldivmod_op();
        MyAny ret = visitFactor(factorArray[0]);
        for (int i = 1; i < factorArray.size(); ++i) {
            std::string tmpOp = opArray[i-1]->getText();
            if(tmpOp == "*") ret *= visitFactor(factorArray[i]);
            if(tmpOp == "//") ret = IntDiv(ret, visitFactor(factorArray[i]));
            if(tmpOp == "/") ret = FloatDiv(ret, visitFactor(factorArray[i]));
            if(tmpOp == "%") ret %= visitFactor(visitFactor(factorArray[i]));
        }
        return ret;
    }

    virtual antlrcpp::Any visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFactor(Python3Parser::FactorContext *ctx) override {////负号赋值
        if(ctx->atom_expr()) return visitAtom_expr(ctx->atom_expr());
        if(ctx->ADD()) return visitFactor(ctx->factor());
        else return MyAny((int2048)(-1)) * visitFactor(ctx->factor());
    }

    virtual antlrcpp::Any visitAtom_expr(Python3Parser::Atom_exprContext *ctx) override {
       if(!ctx->trailer()) return visitAtom(ctx->atom());//下级会return 可能为string， MyAny...
       auto functionName = ctx->atom()->getText();
       auto argsArray = visitTrailer(ctx->trailer()).as<std::vector<MyAny>>();
       if(functionName == "print"){
           std:: cout << argsArray[0] << std::endl;
           return MyAny();
       }
    }

    virtual antlrcpp::Any visitTrailer(Python3Parser::TrailerContext *ctx) override {
        if (ctx->arglist()) return visitArglist(ctx->arglist());
        return std::vector<MyAny>();
    }

    virtual antlrcpp::Any visitAtom(Python3Parser::AtomContext *ctx) override {
        if (ctx->NUMBER()) {
            std::string str = ctx->NUMBER()->getText();
            if (str.find('.') == std::string::npos)
                return MyAny(int2048(str));
            else
                return MyAny(std::stod(str));
        }
        else if (ctx->NAME()){
            MyAny result = VarScope.VarQuery(ctx->NAME()->getText());
            return result;
        }
        else if (ctx->NONE()) return MyAny();
        else if (ctx->TRUE()) return MyAny(true);
        else if (ctx->FALSE()) return MyAny(false);
        else if (ctx->test()) return visitTest(ctx->test());
        else {
            std::string ans;
            auto str_array = ctx->STRING();
            for (auto it : str_array) {
                std::string tmp = it->getText();
                tmp.pop_back(), ans += tmp.substr(1);
            }
            return MyAny(ans);
        }
    }

    virtual antlrcpp::Any visitTestlist(Python3Parser::TestlistContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitArglist(Python3Parser::ArglistContext *ctx) override {
        auto argumentArray = ctx->argument();
        std::vector<MyAny> retArray;
        for (auto ctx : argumentArray) {
            retArray.push_back(visitTest(ctx->test()[0]));
        }
        return retArray;
    }

    virtual antlrcpp::Any visitArgument(Python3Parser::ArgumentContext *ctx) override {
        return visitChildren(ctx);
    }
};


#endif //PYTHON_INTERPRETER_EVALVISITOR_H
