#include "lib/classes.hpp" 
#include "lib/functions.hpp"

using namespace std;

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <queue>
using namespace std;
/*
int maxchild = 2;
int nn = -1;

struct node
{
    int val;
    vector <node> v;
};

void print (Expression& bg, int cells)
{
    vector < vector <string> > vals;
    queue < pair <int, Expression*> > q;
    int currow = -1;
    bool anyadd = true;

    q.push ({0, &bg});
    while (!q.empty ())
    {
        int level = q.front ().first;
        Expression* nd = q.front ().second;
        q.pop ();

        if (level != currow)
        {
            if (!anyadd) {break;}
            vals.push_back (vector<string>());
            vals.back ().reserve (pow (maxchild, level));
            currow ++;
            anyadd = false;
        }

        if (nd != nullptr)
        {
            anyadd = true;
            vals [currow].push_back (nd -> token);
            for (int i = 0; i < maxchild; i ++)
            {
                if (nd -> args.size () > i) {q.push ({level + 1, &nd -> args [i]});}
                else {q.push ({level + 1, nullptr});}
            }
        }
        else
        {
            vals [currow].push_back ("");
            for (int i = 0; i < maxchild; i ++) {q.push ({level + 1, nullptr});}
        }
    }
    while (!q.empty ()) {q.pop ();}
    //vals.pop_back ();

    int lps = 0;
    while (pow (maxchild, lps) < cells) {lps ++;}
    cells = pow (maxchild, lps - 1);
    for (int i = 0; i < vals.size (); i ++)
    {
        int delta = cells / pow (maxchild, i);
        for (auto& j : vals [i])
        {
            cout << j;
            for (int u = 0; u < delta; u ++) {cout << "  ";}
        }
        cout << endl;
    }
}
*/

std::string prtLex(Lexeme * lex)
{
    //cout << "HERE" << endl;
    switch (lex->tp())
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
            return "Small Fuck";
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
    //cout << Head << endl;
    queue<Lexeme *> Q;
    Q.push(Head);

    Lexeme * cur;
    
    while (!Q.empty())
    {
        //cout << "Q.front()" << endl;
        
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

    string s = "";
    simplify(s);
    //vector<string> Tokens = ToStrigns(s);
    //"x - (x + 2)" -> "2"
    //for(int i = 0; i < Tokens.size(); i++)
    //{
        //cout << Tokens[i] << endl;
    //}
    char str[] = "x+3";
    Parser P(str);
    //Expression Head = P.parse();

    LexParser parser(str);
    //cout << Head.token << endl;
    //vector<string> V = P.give_vars();
    //cout << Head.args[0].token<<endl;
    
    Lexeme * Head = parser.parse();
    //cout << prtLex(Head->right_child) << endl;
    //cout << Head << endl;
    
    PrintTree(Head);
    //cout << parser.give_vars().give_data()[0]->name << endl;
    
    //print(Head, 100);
    
    //cout << Head.args[0].args[0].token << endl;

    
    return 0;
}