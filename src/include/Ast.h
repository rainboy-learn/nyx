#pragma once
#include <string>
#include <deque>
#include "token.h"

#include "nyx.hpp"

//下面的类型别名点位用，后面会改成其它的
using Value   = int;
using Runtime = int;
using Context = int;
using ExecResult = int;

/* 基类，所有表达式的基类
 * */
struct AstNode {
    explicit AstNode(int line ,int column):line(line),column(column) {}

    virtual ~AstNode() = default;

    virtual std::string astString() = 0;

    int line   = -1; //发生解析错误时，输出错误信息用
    int column = -1;
};

#define EXPRESSION_CHILD(name) explicit name(int line,int column):Expression(line,column){}
#define STATEMENT_CHILD(name) explicit name(int line,int column):Statement(line,column){}

//表达式类的 基类
struct Expression : public AstNode {
    //using AstNode::AstNode; // ???
    explicit Expression(int line, int column) : AstNode(line, column) {}
    virtual ~Expression() = default;

    // 计算表达式的值
    virtual Value eval(Runtime * rt,std::deque<Context*> ctxChain)=0; //纯虚函数

    virtual std::string astString() override { return "Expression"; };
};

/* 
 * 模板表达式， 针对 int double bool char 
 * */
template<typename T>
struct BaseExpr : public Expression {
    explicit BaseExpr(int line, int column) : Expression(line, column) {}
    T literal;
    Value eval(Runtime * rt,std::deque<Context*> ctxChain) override;
    std::string astString() override {
        return "BaseExpr";
    };
};

// 3 空值 表达式,因为空值不是一种数据类型，不能特化
struct NullExpr : public Expression {
    explicit NullExpr(int line, int column) : Expression(line, column) {}

    Value eval(Runtime* rt, std::deque<Context*> ctxChain) override {
        return 1;
    };
    std::string astString() override {
        return "NullExpr";
    };
};

using BoolExpr   = BaseExpr<bool>;
using CharExpr   = BaseExpr<char>;
using IntExpr    = BaseExpr<int>;
using DoubleExpr = BaseExpr<double>;
using StringExpr = BaseExpr<std::string>;
using ArrayExpr  = BaseExpr<std::vector<Expression *>>;


//// 8 标识符 表达式
//struct IdentExpr : public Expression {
    //EXPRESSION_CHILD(IdentExpr)

    //std::string identName;
    //Value eval(Runtime* rt, std::deque<Context*> ctxChain) override;
    //std::string astString() override;

//};

// 9 索引 表达式
struct IndexExpr : public Expression {
    EXPRESSION_CHILD(IndexExpr)

    std::string identName;
    Expression * index; //下标的表达式
    Value eval(Runtime* rt, std::deque<Context*> ctxChain) override;
    std::string astString() override;
};

// 10 二元 表达式
struct BinaryExpr : public Expression {
    EXPRESSION_CHILD(BinaryExpr)

    Expression * lhs; //表达式左
    Token opt;        //哪个操作符号
    Expression * rhs; //表达式左
    Value eval(Runtime* rt, std::deque<Context*> ctxChain) override;
    std::string astString() override;
    
};

// 11 函数调用 表达式
struct FunCallExpr : public Expression {
    EXPRESSION_CHILD(FunCallExpr)

    std::string funcName;   //函数的名字
    std::vector<Expression *> args; //参数列表

    Value eval(Runtime* rt, std::deque<Context*> ctxChain) override;
    std::string astString() override;
    
};

// 12 赋值 表达式
struct AssignExpr : public Expression {
    EXPRESSION_CHILD(AssignExpr)

    Expression * lhs; //表达式左
    Token opt;        //哪个操作符号
    Expression * rhs; //表达式左
    Value eval(Runtime* rt, std::deque<Context*> ctxChain) override;
    std::string astString() override;
};

// ====================================语句====================================

// 1 语句
struct Statement : public AstNode{

    explicit Statement(int line ,int column) : AstNode(line,column){}
    
    virtual ~Statement() = default;
    virtual ExecResult interpret(Runtime * rt,std::deque<Context *> ctxChain) = 0;

    virtual std::string astString() override{
        return "Statement";
    };
};

// 2 break 语句
struct BreakStmt : public Statement {
    STATEMENT_CHILD(BreakStmt)

    ExecResult interpret(Runtime* rt, std::deque<Context*> ctxChain) override;

    std::string astString() override { return "BreakStmt"; };
};

// 3 continue 语句
struct ContinueStmt : public Statement {
    STATEMENT_CHILD(ContinueStmt)

    ExecResult interpret(Runtime* rt, std::deque<Context*> ctxChain) override;
    std::string astString() override { return "ContinueStmt"; };
    
};

// 4 表达式 语句
struct ExpressStmt : public Statement {
    STATEMENT_CHILD(ExpressStmt)

    Expression* expr{};

    ExecResult interpret(Runtime* rt, std::deque<Context*> ctxChain) override;
    std::string astString() override { return "ExpressStmt"; };
};

// 5 返回 语句
struct ReturnStmt : public Statement {
    STATEMENT_CHILD(ReturnStmt)

    Expression* ret{};

    ExecResult interpret(Runtime* rt, std::deque<Context*> ctxChain) override;
    std::string astString() override{ return "ReturnStmt"; };
    
};

// 6 if 语句
struct IfStmt : public Statement {
    explicit IfStmt(int line ,int column) : Statement(line,column){}
    Expression* cond{}; // 判断表达式
    Block* block{};     // 语句块
    Block* elseBlock{}; // else 语句块

    ExecResult interpret(Runtime* rt, std::deque<Context*> ctxChain) override;

    //interpret //解释执行
    std::string astString() override{ return "IfStmt()"; }
};

// 7 while 语句
struct WhileStmt : public Statement {
    explicit WhileStmt(int line, int column) : Statement(line, column) {}

    Expression* cond{};
    Block* block{};

    ExecResult interpret(Runtime* rt, std::deque<Context*> ctxChain) override;
    std::string astString() override{ return "WhileStmt"; };
};
