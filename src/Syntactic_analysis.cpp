#include "Syntactic_analysis.h"
#include "Ast.h"
#include <cassert>

auto  Syntactic_analysis::getCurrentToken(){
    //return currentToken.get<0>() ;
    return std::get<0>(currentToken);
}
void Syntactic_analysis::NextToken(){
    currentToken = parser.next();
}

//解析语句
Statement * Syntactic_analysis::parseIfStmt(){
    auto [line,column] = parser.getNowParsePos();
    auto * node = new IfStmt(line,column); //If 语句

    //吃掉左括号
    NextToken();

    node->cond = parseExpression();

    //吃掉左括号
    assert(getCurrentToken() == Token::TK_RPAREN);
    NextToken();

    node->block = parseBlock();

    if( getCurrentToken() == Token::KW_ELSE){
        NextToken(); //吃掉 next
        node->elseBlock = parseBlock();
    }

    return node;
}

//表达式解析
Expression * Syntactic_analysis::parseExpression(){
    //TODO
    return nullptr;
}

Block * Syntactic_analysis::parseBlock(){
    //TODO
    return nullptr;
}



//解析
void Syntactic_analysis::parse_syn(){
    NextToken();
    if( getCurrentToken() == Token::TK_EOF)
        return;
}

Statement * Syntactic_analysis::parseStatement(){
    Statement * node;
    switch( getCurrentToken() ){
        case Token::KW_IF:
            node = parseIfStmt();
            NextToken();
            break;
        case Token::KW_WHILE:
        case Token::KW_RETURN:
        case Token::KW_BREAK:
        case Token::KW_CONTINUE:
            //TODO
            break;
        defaul:
            break;
    }
    return node;
}
