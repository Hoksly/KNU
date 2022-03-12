#include "lib/classes.hpp" 
#include "lib/functions.hpp"

using namespace std;

int main()
{

    string s = " -x^2 + 4x + 4";
    simplify(s);
    vector<string> Tokens = ToStrigns(s);

    for(int i = 0; i < Tokens.size(); i++)
    {
        //cout << Tokens[i] << endl;
    }
    char str[] = "x+2";
    Parser P(str);
    Expression Head = P.parse();

    cout << Head.token << endl;
    vector<string> V = P.give_vars();
    //cout << Head.args[0].token<<endl;
    
    for(int i = 0; i < V.size(); i++)
    {
        cout << V[i] << endl;
    }
    

    
    return 0;
}