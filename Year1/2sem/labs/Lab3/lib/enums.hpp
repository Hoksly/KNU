
#pragma once
#include <string>
#include <vector>

typedef std::string token;

enum Type
{
    Variable,
    Constant,
    Operator,
    NullType
};

enum OperatorType
{
    NullOPerator,
    Plus, 
    Minus,
    Mult,
    Div,
    Pow,
    Sin, 
    Cos, 
    Mod, 
    Abs
    
};

struct Var
{
    double value;
    std::string name;
    int count = 1; // if instance crated, then at least one variable is 
    Var(std::string name) : name(name) {};
    
};

const std::vector<std::pair<std::string, OperatorType>> _Operators =   {{"-", Minus}, 
                                                                {"+", Plus}, 
                                                                {"*", Mult}, 
                                                                {"/", Div}, 
                                                                {"^", Pow}};

static const std::string TOKENS[] =
        { "+", "-", "**", "*", "/", "mod", "abs", "sin", "cos", "(", ")", "^" };

static const std::vector<OperatorType> NotEqualOperators = {Div, Pow, Mod, Minus};
static const std::vector<OperatorType> EqualOperators = {Mult, Plus};
static const std::vector<OperatorType> UnarOperators = {Sin, Cos, Abs, Minus};