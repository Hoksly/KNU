#include "lib/classes.hpp" 
#include "lib/functions.hpp"
#include "lib/rules.hpp"

using namespace std;

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <queue>
#include <stack>

using namespace std;

std::string prtLex(Lexeme * lex)
{
    //cout << "HERE" << endl;
    switch (lex->_type)
    {
    case Variable:
        
        if(lex->variable == nullptr)
            cout << "IDK" << endl;
        return (lex->variable->name);
    
    case Operator:

        
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
        return "BIG ERROR";
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


void PrintTreeS(Lexeme * Head, string &s)
{
    if(Head == nullptr)
        return;

   PrintTreeS(Head->left_child, s);
   s += Head->str_value();
   PrintTreeS(Head->right_child, s);   
}

int main()
{

    
   
    char str2[30] = "(2+3+4+6+7)*X";
    LexParser parser2(str2);
    

    Lexeme * Head2 = parser2.parse();

    Simplyfier S;

    S.simplify(Head2);

    string s;
    PrintTreeS(Head2, s);
    print(s);
   
    return 0;
}