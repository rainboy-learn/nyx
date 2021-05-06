//语法分析器
#pragma once
#include <map>
#include <string>
#include <tuple>

#include "parser.h"
#include "Ast.h"

class Syntactic_analysis {

    public:
        explicit Syntactic_analysis(const std::string & fileName)
            :parser(fileName){}

        void parse_syn(/* Runtime rt*/); //根据Token解析成语法树
        auto getCurrentToken();
        void NextToken();
    private:
        //const std::map<std::string,Token> keywords;
        std::tuple<Token, std::string> currentToken;
        Parser parser;  //语法分析器

        Statement  * parseStatement();  //解析语句

        Statement  * parseIfStmt(); //if语句解析
        Expression * parseExpression(); // 表达式解析
        Block      * parseBlock();
};
