#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <tuple>
#include "token.h"


/* @desc: 词法分析器的类声明
 *
 * */

class Parser {
    public:
        explicit Parser(const std::string fileName):
            keywords(
                    { {"if",Token::KW_IF},
                    {"else",Token::KW_ELSE},
                    {"while",Token::KW_WHILE},
                    {"null",Token::KW_NULL},
                    {"true",Token::KW_TRUE},
                    {"false",Token::KW_FALSE},
                    {"for",Token::KW_FOR},
                    {"func",Token::KW_FUNC},
                    {"return",Token::KW_RETURN},
                    {"break",Token::KW_BREAK},
                    {"continue",Token::KW_CONTINUE} }
                    ) 
        {
            fs.open(fileName);
        }
        ~Parser(){
            fs.close();
        }
    public:
        //输出lex 用于调试
        static void printLex(const std::string & fileName);
        
        std::tuple<int,int> getNowParsePos() const;

        // 不停的得到下一个Token
        std::tuple<Token,std::string> next();
    private:

        //关键字
        std::unordered_map<std::string,Token> keywords ;

        int line   = 1;
        int column = 0;

        std::fstream fs;

        //读取下一个字符
        inline char getNextChar(){
            column++;
            return static_cast<char>(fs.get());
        }

        //读取下一个字符
        inline char peekNextChar(){
            return static_cast<char>(fs.peek());
        }
};
