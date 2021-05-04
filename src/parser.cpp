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

    //结束
    if( c == EOF ) return std::make_tuple(Token::TK_EOF,"");

    return std::make_tuple(Token::INVALID,"invalid_token");
}

void Parser::printLex(){
    while (1) {
      auto [token,name] = next();
      std::cout << "Token : " << magic_enum::enum_name(token)<< std::endl;
      std::cout << "    Name : "<< name << std::endl << std::endl;

      if( token == Token::TK_EOF) break;
    }
}
