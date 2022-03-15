#pragma once
#include <string.h>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <iostream>
#include "functions.hpp"
#include "enums.hpp"
#include "loader.hpp"

class Lexeme
{ 
    public:
    Type _type;

    Var *variable = nullptr; // if variable
    double * value = nullptr; // if constant
    OperatorType oper = NullOPerator; //if operator 
    bool isnone = false;
    
    Lexeme* parent = nullptr;
    Lexeme* right_child = nullptr;
    Lexeme* left_child = nullptr;

    
    
    Lexeme(double);
    Lexeme(Var*);
    Lexeme(OperatorType); // optimize with pointers 
    Lexeme(OperatorType, Lexeme*);
    Lexeme(const std::string&, Lexeme*, Lexeme*); // constructor with undifined vaslue and childrens
     
    bool empty() {return isnone;}
    Type tp(){return _type;}
    
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

class Variables
{
    public:
    Variables();

    Var* give(std::string);
    void set(std::string, double);
    std::vector<Var*> give_data() {return data;};
    private:
    Var* add(std::string);
    std::vector<Var*> data;

};

class LexParser
{
    public:
    explicit LexParser(const char* input) : input(input) {}
    Lexeme* parse();
    Variables give_vars() {return Vars;}

    private:
    const char *input;
    std::string parse_token(); // Парсит один токен
    Lexeme* parse_simple_expression(); // Парсит простое выражение
    Lexeme* parse_binary_expression(int min_priority); // Парсит бинарное выражение
    
    void make_three(Lexeme, Lexeme, Lexeme);
    Lexeme * makelexeme(std::string);
    Variables Vars;


};

