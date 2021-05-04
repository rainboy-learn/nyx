#pragma once
#include <map>
#include <iostream>
#include <unordered_map>
#include <filesystem>

#include "parser.h"

template<typename T,typename... ts>
bool anyone(T c,ts... tt){
    return ((c == tt) || ...);
}


template<typename... Args>
void err_log(const char * file,int line,Args... args){
    auto & os = std::cerr;
    
    os << "FILE : "<< std::filesystem::path(file).filename() << "  LINE:"<< line << std::endl;
    ((os << args), ... );
    os<< std::endl;
}

#define LOG(...) err_log(__FILE__,__LINE__,__VA_ARGS__)
