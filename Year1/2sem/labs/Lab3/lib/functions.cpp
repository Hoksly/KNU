#include "functions.hpp"

using namespace std;

void simplify(string &str)
{
    int l;
    l = str.length();
    string out_str;

    for(int i = 0; i < l; ++i)
    {
        if(str[i] != ' ')
        {
            out_str += str[i];
            
        }
    }
   
    str.clear();
    str = out_str;

}
inline bool isoperator(char i)
{
    return i == '+' || i == '-' || i == '*' || i == '^' || i == '/' ;
}

void parse_digit(string &part, const string &s, int &i, const int &l)
{
    while(isdigit(s[i]) && i < l)
        {
            part += s[i];
            ++i; 
        }
        if(s[i] == '.')
        {
            part += '.';
            ++i;
            if(!isdigit(s[i]))
                throw runtime_error("Must be a digit after '.'");
            while(isdigit(s[i]))
            {
                part += s[i];
                ++i;
              
            }
           
        }

}
inline bool isvar(char c)
{
    return islower(c) || isupper(c);
}

void parse_digit_or_var(string &part, const string &s, int &i, const int &l)
{
    if(isdigit(s[i]))
        parse_digit(part, s, i, l);
    if(isvar(s[i]))
    {
        part += s[i];
        ++i;
    }
}


vector<string> ToStrigns(const string &s)
{
    vector<string> out;
    string part;
    
    bool previous_was_operator, previous_was_digit, previous_was_closing_bracket, previous_was_var;
    previous_was_operator = false;
    previous_was_digit = false;
    previous_was_closing_bracket = false; // second is for unar minus
    previous_was_var = false;

    int l = s.length();

    for(int i = 0; i < l;)
    {   
        part = "";
        
        //parsing numbers and variables
        
        if(isvar(s[i]))
        {
            part += s[i];
            ++i;
            
            if(previous_was_digit || previous_was_var)
                out.push_back("*");
            
            previous_was_digit = false;
            previous_was_operator = false;
            previous_was_closing_bracket = false;
            previous_was_var = true;
            out.push_back(part);
            continue;

        }

        if(isdigit(s[i]))
            {
            parse_digit(part, s, i, l);
            previous_was_digit = true;
            previous_was_operator = false;
            previous_was_closing_bracket = false;
            out.push_back(part);
            
            continue;

            }
        

        //parisng operators
        if(isoperator(s[i]))
        {

            
            if(s[i] != '-' || previous_was_digit || previous_was_closing_bracket)
            {
                part += s[i];
                out.push_back(part);
                
                ++i;
                
                previous_was_digit = false;
                previous_was_operator = true;
                previous_was_closing_bracket = false;
                continue;
            }
            else //unar minus
            {   
                if(i+1 < l && isdigit(s[i+1]))
                {
                    part += s[i];
                    parse_digit(part, s, ++i, l);
                    out.push_back(part);
                }
                
                else if (isvar(s[i+1]))
                {
                    part += s[i+1];
                    i += 2;

                    //out.push_back("(");
                    out.push_back("-1");
                    out.push_back("*");
                    out.push_back(part);
                    //out.push_back(")");
                }
                
                else
                    throw runtime_error("Unar minus detected in input, but without following it digits");
                
                
                previous_was_digit = true;
                previous_was_operator = false;
                previous_was_closing_bracket = false;
            
            }
            continue;
        }
        //parsing '(' and ')'

        if(s[i] == ')' || s[i] == '(')
        {
            part += s[i];
            out.push_back(part);
            ++i;
            previous_was_digit = false;
            previous_was_operator = false;
            previous_was_closing_bracket = s[i-1] == ')';
            continue;
        }
        
        throw runtime_error("Usage of not allowed symbol in input detected, please chaeck your input");



    }
    
    return out;

}

int give_priority(string s)
{
    if (s == "+") return 4;
    if (s == "-") return 4;
    if (s == "/") return 3;
    if (s == "*") return 3;
    if (s == "^") return 2;
    return 0;

}

void BuildThree(Lexeme *Parent, Lexeme *RightChild, Lexeme *LeftChild)
{

    
}