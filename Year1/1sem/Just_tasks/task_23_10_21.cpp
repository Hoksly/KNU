#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int MAX_LINE_LEN = 150;
const int MAX_INT_LEN = 20;

void take_input(char *inp)
{
    cin.getline(inp, MAX_LINE_LEN);

}

void add_substr(char **str, char s, int n)
{   

    **str = s;
    (*str)++;
    **str = '(';
    (*str)++;
    char *n_str = new char[MAX_INT_LEN];
    sprintf(n_str, "%d", n);
    //cout << s << ' ' << n << endl;
    strcat((*str), n_str);
    
    (*str)++;
    **str = ')';  
    
    (*str)++;

    delete[] n_str;     
}


void solve_task(char *inp, char *out)
{
    char s = *inp++;
    int n = 1;
    char **ptr = &out;

    int len = strlen(inp);
    for(int i = 1; i <= len; i++, inp++)
    {
        if(s == *inp)
            n++;
        else
        {
            //cout << s << ' ' << n << endl;
            add_substr(ptr, s, n);
            n = 1;
            s = *inp;
        }
    }
    //cout << "HERE: " << s << ' ' << n << endl;
    add_substr(ptr, s, n);
    *out = '\0';

}


void write_out(char *out)
{
    cout << out << endl;
}

// 11122333
int main()
{
    char *inp = new char[MAX_LINE_LEN];
    char *out = new char[MAX_LINE_LEN];
    
    take_input(inp);
    solve_task(inp, out);
    write_out(out);

    delete [] inp;
    delete [] out;

    return 0;

}


