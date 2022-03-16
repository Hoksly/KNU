#include "lib/classes.hpp" 
#include "lib/functions.hpp"

using namespace std;

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <queue>
using namespace std;

std::string prtLex(Lexeme * lex)
{
    //cout << "HERE" << endl;
    switch (lex->_type)
    {
    case Variable:
        //cout << "Variable" << endl;
        if(lex->variable == nullptr)
            cout << "FUCK" << endl;
        return (lex->variable->name);
    
    case Operator:
        //cout << "Operator" << endl;
        
        switch (lex->oper)
        {
        case Plus:
            return "+";
        case Minus:
            return "-";
        case Mult:
            return "*";
        case Div:
            return "/";
        case Pow:
            return "^";
        case NullOPerator:
            return "OperNull";
        }
    case Constant:
        //cout << "Constant" << endl;
        return to_string(*(lex->value));
    
    default:
        return "BIG FUCK";
    }  
    
}

void PrintTree(Lexeme * Head)
{
    
    queue<Lexeme *> Q;
    Q.push(Head);

    Lexeme * cur;
    
    while (!Q.empty())
    {
        cur = Q.front();
        cout << prtLex(cur) << endl;
        Q.pop();
        
        if(cur->left_child != nullptr)
            Q.push(cur->left_child);
        
        if(cur->right_child != nullptr)
            Q.push(cur->right_child);

    }
    
    
}


int main()
{

    
    char str1[] = "-x^x";
    char str2[] = "-x^x";
    LexParser parser1(str1);
    LexParser parser2(str2);
    
    Lexeme * Head1 = parser1.parse();
    Lexeme * Head2 = parser2.parse();
    
   print((*Head1) == (*Head2));
    
    //PrintTree(Head1);
    
    
    return 0;
}