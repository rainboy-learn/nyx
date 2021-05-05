#include <iostream>
#include <string>
#include <tuple>

#include "parser.h"
#include "utils.hpp"
#include "./lib/magic_enum.hpp"


std::tuple<Token,std::string> Parser::next(){
    auto c = getNextChar();

    //无用字符消去
    while( anyone(c,' ','\n','\r','\t') ) {
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

    //字符字面值
    if( c == '\''){
        std::string lexeme;
        lexeme = getNextChar();
        if( peekNextChar() !='\''){
            LOG("SynaxError: 字符应该以\'结束！");
            // TODO 
            // throw error
        }
        c = getNextChar();
        return std::make_tuple(Token::LIT_CHAR,lexeme);
    }

    //字符串字面值
    if( c == '"'){
        std::string lexeme;
        char nc = peekNextChar();
        while ( nc !='"' ) {
            c = getNextChar();
            lexeme +=c;
            nc = peekNextChar();
        }
        c = getNextChar();
        return std::make_tuple(Token::LIT_STR,lexeme);
    }

    //各种运算符号的Token
    const std::unordered_map<char, Token> char_std{
        {'[',Token::TK_LBRACKET},
        {']',Token::TK_RBRACKET},
        {'{',Token::TK_LBRACE},
        {'}',Token::TK_RBRACE},
        {'(',Token::TK_LPAREN},
        {')',Token::TK_RPAREN},
        {',',Token::TK_COMMA},
        {'+',Token::TK_PLUS},
        {'-',Token::TK_MINUS},
        {'*',Token::TK_TIMES},
        {'/',Token::TK_DIV},
        {'%',Token::TK_MOD},
        {'~',Token::TK_BITNOT},
        {'=',Token::TK_ASSIGN}, //==
        {'!',Token::TK_LOGNOT}, //!=
        {'|',Token::TK_BITOR}, 
        {'&',Token::TK_BITAND},
        {'>',Token::TK_GT}, //>=
        {'<',Token::TK_LT}, //<=
        // TODO
        // | ||
        // & &&
    };
    const std::unordered_map<std::string, Token> double_char_std {
        {"!=",Token::TK_NE},
        {"==",Token::TK_EQ},
        {">=",Token::TK_LOGAND},
        {"<=",Token::TK_LE},
        {"||",Token::TK_LOGOR},
        {"&&",Token::TK_LOGAND}
    };

    if( auto tt = char_std.find(c); tt != char_std.end() ){
        auto nc = peekNextChar();
        std::string lexeme{c};
        if( nc == '=' && anyone(c, '=','>','<','!')){
            c=getNextChar();
            lexeme += c;
            return std::make_tuple(
                    double_char_std.find(lexeme)->second
                    ,lexeme);
        }
        else if( anyone(c, '|','&') && nc == c){
            c=getNextChar();
            lexeme += c;
            return std::make_tuple(
                    double_char_std.find(lexeme)->second
                    ,lexeme);
        }
        else {
            return std::make_tuple(tt->second,lexeme);
        }
    }


    //结束
    if( c == EOF ) return std::make_tuple(Token::TK_EOF,"");


    LOG("INVALID TOKEN : ",c,static_cast<int>(c));
    return std::make_tuple(Token::INVALID,"invalid_token");
}

void Parser::printLex(const std::string & fileName){
    Parser p(fileName);
    while (1) {
      auto [token,name] = p.next();
      //std::cout << "[Token : " << magic_enum::enum_name(token)<< " <===> ";
      //std::cout << "Name : "<< name << "]"<<std::endl;
      std::cout <<"[" <<magic_enum::enum_name(token) << "," << name <<"]" << std::endl;

      if( token == Token::TK_EOF) break;
    }
}
