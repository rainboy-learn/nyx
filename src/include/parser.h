#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <tuple>


//Token的定义
enum class Token {
    INVALID = 0,  // <invalid>

    TK_IDENT,    // <identifier>
    TK_EOF,      // <eof>
    LIT_INT,     // <integer>
    LIT_STR,     // <string>
    LIT_DOUBLE,  // <decimal>
    LIT_CHAR,    // <character>

    TK_BITAND,  // &
    TK_BITOR,   // |
    TK_BITNOT,  // ~
    TK_LOGAND,  // &&
    TK_LOGOR,   // ||
    TK_LOGNOT,  // !

    TK_PLUS,   // +
    TK_MINUS,  // -
    TK_TIMES,  // *
    TK_DIV,    // /
    TK_MOD,    // %

    TK_EQ,  // ==
    TK_NE,  // !=
    TK_GT,  // >
    TK_GE,  // >=
    TK_LT,  // <
    TK_LE,  // <=

    TK_ASSIGN,     // =
    TK_PLUS_AGN,   // +=
    TK_MINUS_AGN,  // -=
    TK_TIMES_AGN,  // *=
    TK_DIV_AGN,    // /=
    TK_MOD_AGN,    // %=
    TK_COMMA,      // ,
    TK_LPAREN,     // (
    TK_RPAREN,     // )
    TK_LBRACE,     // {
    TK_RBRACE,     // }
    TK_LBRACKET,   // [
    TK_RBRACKET,   // ]

    KW_IF,        // if
    KW_ELSE,      // else
    KW_TRUE,      // true
    KW_FALSE,     // false
    KW_WHILE,     // while
    KW_FOR,       // for
    KW_NULL,      // null
    KW_FUNC,      // func
    KW_RETURN,    // return
    KW_BREAK,     // break
    KW_CONTINUE,  // continue
};



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
