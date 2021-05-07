#include "Ast.h"
// 1 bool 表达式

template<>
Value BaseExpr<bool>::eval(Runtime *rt, std::deque<Context *> ctxChain) {
    //TODO
    return 1;
}

// 2 字符 表达式
template<>
Value BaseExpr<char>::eval(Runtime *rt, std::deque<Context *> ctxChain){
    //TODO
    return 1;
}

// 4 整数 表达式
template<>
Value BaseExpr<int>::eval(Runtime *rt, std::deque<Context *> ctxChain){
    //TODO
    return 1;
}

// 5 float 表达式
template<>
Value BaseExpr<double>::eval(Runtime *rt, std::deque<Context *> ctxChain){
    //TODO
    return 1;
}
// 6 字符串 表达式
template<>
Value BaseExpr<std::string>::eval(Runtime *rt, std::deque<Context *> ctxChain){
    //TODO
    return 1;
}

// 7 数组 表达式
template<>
Value BaseExpr<std::vector<Expression*>>::eval(Runtime *rt, std::deque<Context *> ctxChain){
    //TODO
    return 1;
}

template<> std::string BaseExpr<char>::astString()                     { return "CharExpr";   };
template<> std::string BaseExpr<int>::astString()                      { return "IntExpr";    };
template<> std::string BaseExpr<double>::astString()                   { return "IntExpr";    };
template<> std::string BaseExpr<std::string>::astString()              { return "StringExpr"; };
template<> std::string BaseExpr<std::vector<Expression*>>::astString() { return "ArrayExpr";  };


// ====================================语句====================================

ExecResult BreakStmt::interpret(Runtime* rt, std::deque<Context*> ctxChain) {
    //TODO
    return 1;
}

ExecResult ContinueStmt::interpret(Runtime* rt, std::deque<Context*> ctxChain) {
    //TODO
    return 1;
}

ExecResult ExpressStmt::interpret(Runtime* rt, std::deque<Context*> ctxChain) {
    //TODO
    return 1;
}

ExecResult ReturnStmt::interpret(Runtime* rt, std::deque<Context*> ctxChain) {
    //TODO
    return 1;
}

ExecResult IfStmt::interpret(Runtime* rt, std::deque<Context*> ctxChain) {
    //TODO
    return 1;
}

ExecResult WhileStmt::interpret(Runtime* rt, std::deque<Context*> ctxChain) {
    //TODO
    return 1;
}
