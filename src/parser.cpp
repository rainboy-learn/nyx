#include "parser.h"
#include "utils.hpp"
#include <tuple>


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
