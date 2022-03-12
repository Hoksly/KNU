#pragma once
#include <string.h>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <iostream>
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
    Plus, 
    Minus,
    Mult,
    Div,
    Pow,
    NullOPerator
};

class Lexeme
{
    bool is_const;
    Type _type;

    char * variable = nullptr;
    double * value = nullptr;
    OperatorType oper = NullOPerator;
    
    Lexeme* parent = nullptr;
    Lexeme* right_child = nullptr;
    Lexeme* left_child = nullptr;

    public:
    Lexeme(Type what, Lexeme* Parent, Lexeme* LeftChild, Lexeme *RightChild, void * value, OperatorType);
    
    void change_left(Lexeme *);
    void change_right(Lexeme *);
    void change_parent(Lexeme *);


};    

struct Expression {
    Expression(std::string token) : token(token) {} 
    Expression(std::string token, Expression a) : token(token), args{a} {} 
    Expression(std::string token, Expression a, Expression b) : token(token), args{a, b} {}

    std::string token; 
    std::vector<Expression> args;
};

class Parser {
public:
    explicit Parser(const char* input) : input(input) {} // Конструктор, принимает строку с выражением
    Expression parse(); // Основная функция парсинга
    std::vector<std::string> give_vars();
    
private:
    
    std::vector<std::string> variables;
    std::string parse_token(); // Парсит один токен
    Expression parse_simple_expression(); // Парсит простое выражение
    Expression parse_binary_expression(int min_priority); // Парсит бинарное выражение

    const char* input; // Кусок строки, который еще не распарсили
};
