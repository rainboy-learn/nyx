#pragma once
#include <vector>

//#include "Ast.h"
//#include "Syntactic_analysis.h"

struct Statement;

struct Block {
    std::vector<Statement * > stmts; //语句流
};
