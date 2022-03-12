#include "utils.h"
using namespace std;




bool is_smallerM(char * mas1, char *mas2)
{
    while(*mas1 != '\0' && *mas2 != '\0')
    {
        if (*mas1 != (*mas2))
            return *mas1 < *mas2;
        mas1++;
        mas2++;
    }
    return false;
}   

vector<vector<char>> ToNotEmpty(const vector<vector<String *>> &Strings)
{
    vector<vector<char>> ret(STR_LEN, vector<char>());
    bool mas[LEN];
    memset(mas, false, LEN);
    for(unsigned char i = 0; i < STR_LEN; ++i)
    {
        for(auto v = Strings[i].begin(); v != Strings[i].end(); v++)
        {
            for(unsigned char c = 0; c < (*v)->_len; c++)
                mas[(*v)->mas[c]] = true;
        }   

        for(unsigned char m = 0; m < LEN-1; ++m)
        {
            if(mas[m])
                ret[i].push_back((char) m);   
        }
    }

    return ret;


    
}

vector<vector<String *>> ToLenStrings(char **mas, int n)
{
    vector<vector<String *>> ret (STR_LEN, vector<String*>());

    for(int i = 0; i < n; ++i)
    {
        String * tmp = new String();
        tmp->_len = strlen(mas[i]);
        tmp->mas = mas[i];
        
        ret[tmp->_len - 1].push_back(tmp);
    }

    return ret;

}

