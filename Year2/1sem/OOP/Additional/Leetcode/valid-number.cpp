#include <string>
#include <string.h>
using namespace std;

bool check_integer(string s, int beg)
{
    int n = s.length();
    for (int i = beg; i < n; ++i)
    {
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}

bool check_decimal(string s, int beg)
{
}

bool check_e(string s, int beg)
{

    if (s[beg] == 'e' or s[beg] == 'E')
    {
    }
}

bool check_digits(string s, int &beg)
{
    while (isdigit(s[beg]))
    {
        beg++;
    }
}

bool check(string s, int &beg)
{
    if (beg == 0 && (s[0] == '+' or s[0] == '-'))
        return check(s, ++beg);

    return check_decimal(s, beg) or check_integer(s, beg) or check_e(s, beg);
}

class Solution
{
public:
    bool isNumber(string s)
    {
    }
};