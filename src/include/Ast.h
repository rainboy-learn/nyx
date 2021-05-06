#pragma once
#include <string>
#include "nyx.hpp"

struct AstNode {
    explicit AstNode(int line ,int column):line(line),column(column) {}

    virtual ~AstNode() = default;

    virtual std::string astString(){
        return "AstNode()";
    }

    int line   = -1;
    int column = -1;
    
};

//表达式
struct Expression : public AstNode {
    //using AstNode::AstNode; // ???
    
    virtual ~Expression() = default;
    
    //virtual Value eval ()
    std::string astString() override;
};

// 1 bool 表达式
struct BoolExpr : public Expression {
    
};

// 2 字符 表达式
struct CharExpr : public Expression {
    
};

// 3 空值 表达式
struct NullExpr : public Expression {
    
};

// 4 整数 表达式
struct IntExpr : public Expression {
    
};

// 5 float 表达式
struct DoubleExpr : public Expression {
    
};

// 6 字符串 表达式
struct StringExpr : public Expression {
    
};

// 7 数组 表达式
struct ArrayExpr : public Expression {
    
};

// 8 标识符 表达式
struct IdentExpr : public Expression {
    
};

// 9 索引 表达式
struct IndexExpr : public Expression {
    
};

// 10 二元 表达式
struct BinaryExpr : public Expression {
    
};

// 11 函数调用 表达式
struct FunCallExpr : public Expression {
    
};

// 12 赋值 表达式
struct AssignExpr : public Expression {
    
};

// 1 语句
struct Statement : public AstNode{

    explicit Statement(int line ,int column) : AstNode(line,column){}
    
};

// 2 break 语句
struct BreakStmt : public Statement {
    
};

// 3 continue 语句
struct ContinueStmt : public Statement {
    
};

// 4 表达式 语句
struct ExpressStmt : public Statement {
    
};

// 5 返回 语句
struct ReturnStmt : public Statement {
    
};

// 6 if 语句
struct IfStmt : public Statement {
    explicit IfStmt(int line ,int column) : Statement(line,column){}
    Expression* cond{}; // 判断表达式
    Block* block{};     // 语句块
    Block* elseBlock{}; // else 语句块

    //interpret //解释执行
    std::string astString() override{
        return "IfStmt()";
    }
};

// 7 if 语句
struct WhileStmt : public Statement {
    
};
