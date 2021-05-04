#pragma once
#include <map>
#include <unordered_map>

#include "parser.h"

template<typename T,typename... ts>
bool anyone(T c,ts... tt){
    return ((c == tt) || ...);
}


