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

OperatorType give_operator(string s)
{
    for(auto t = _Operators.begin(); t!= _Operators.end(); t++)
        if(t->first == s)
            return t->second;
    return NullOPerator;
}



bool XOR (void *p1, void *p2)
{
    return ((bool) p1) ^ ((bool) p2);
}

bool NotNULL(void *p1, void *p2)
{
    return p1 != nullptr && p2 != nullptr;
}
bool NotNULL(void *p)
{
    return p != nullptr;
}


bool deq(double *d1, double *d2)
{
    if(NotNULL(d1, d2))
        {
            return *d1 == *d2;
            //return fabs(*d1 - *d2) < EPS;
        }
    
    return d1 == d2; // both are nullptr
    

}

bool isin(OperatorType op, std::vector<OperatorType> V)
{
    for(auto t = V.begin(); t != V.end(); t++)
    {
        if(*t == op)
            return true;
    }
    return false;
}

void print(string s )
{
    std::cout << s << endl;

}

void print(int s )
{
    std::cout << s << endl;

}

void print(long s )
{
    std::cout << s << endl;

}


void printb(bool b)
{
    if(b)
        std::cout << "YES" << endl;
    else
        std::cout << "NO" << endl;
}

bool vareq(Var* v1, Var* v2)
{
    if(NotNULL(v1, v2))
        return v1->name == v2->name;
    
    return v1 == v2;
}
bool IsNull(void *p1)
{
    return p1 == nullptr;
}

bool IsNull(void *p1, void *p2)
{
    return IsNull(p1) && IsNull(p2);
}


bool IsPorM(OperatorType p)
{
    return p == Minus || p == Plus;
}

bool isMinus(OperatorType p)
{
    return p == Minus;
}

