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

    //结束
    if( c == EOF ) return std::make_tuple(Token::TK_EOF,"");

    return std::make_tuple(Token::INVALID,"invalid_token");
}

void Parser::printLex(){
    while (1) {
      auto [token,name] = next();
      if( token == Token::TK_EOF){
          std::cout << "EOF" <<std::endl;
          return;
      }
      std::cout << "Token : " << magic_enum::enum_name(token)<< std::endl;
      std::cout << "    Name : "<< name << std::endl << std::endl;
    }
}
