#include <iostream>
#include <tuple>

#include "parser.h"
#include "utils.hpp"
#include "./lib/magic_enum.hpp"


std::tuple<Token,std::string> Parser::next(){
    auto c = getNextChar();

    //无用字符消去
    if( anyone(c,' ','\n','\r','\t') ) {
        if( c == '\n')
            line++,column=0;
        c = getNextChar();
    }

    //注释的消去
    if( c == '#'){
another_commnet:
        while ( c!='\n' && c !=EOF ) {
            c = getNextChar();
        }

        //注释后面的空行
        while ( c == '\n' ) {
            line++;
            column = 0;
            c = getNextChar();
        }

        //又是一行注释
        if( c == '#')
            goto another_commnet;
    }

    //整数 小数 字面值
    if( c>='0' && c <='9' ) {
        std::string lexeme{c};
        bool isDouble = 0;
        char nc = peekNextChar();

        while ( (nc >='0' && nc <='9') || (!isDouble && nc =='.')) {
            if( nc == '.') 
                isDouble = 1;

            c = getNextChar();
            nc = peekNextChar();
            lexeme += c;
        }

        return  make_tuple(!isDouble ? Token::LIT_INT : Token::LIT_DOUBLE,lexeme);
    }

    //标记符 + 关键字
    if( std::isalpha(c) || c == '_'){
        std::string lexeme{c};
        char nc = peekNextChar();
        while ( std::isalpha(nc) || std::isalnum(nc) || nc == '_' ) {
            c = getNextChar();
            lexeme += c;
            nc = peekNextChar();
        }

        auto result = keywords.find(lexeme);

        return result != keywords.end()
                ? std::make_tuple(result->second,lexeme)
                : std::make_tuple(Token::TK_IDENT,lexeme);
    }

    if( c == '\''){
        std::string lexeme;
        lexeme = getNextChar();
        if( peekNextChar() !='\''){

        }

    }

    //结束
    if( c == EOF ) return std::make_tuple(Token::TK_EOF,"");

    return std::make_tuple(Token::INVALID,"invalid_token");
}

void Parser::printLex(){
    while (1) {
      auto [token,name] = next();
      std::cout << "Token : " << magic_enum::enum_name(token)<< "\t\t\t";
      std::cout << "Name : "<< name << std::endl;

      if( token == Token::TK_EOF) break;
    }
}
