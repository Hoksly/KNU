#include <string>
#include <cmath>
#include <iostream>
#include <string.h>
using namespace std;

const int INT_MAX = 0;
const int INT_MIN = 0;

class Solution
{
public:
    int myAtoi(string s)
    {
        int len = s.size();
        int i = 0;
        while (i < len && s[i] == ' ')
            i++;
       
        int x = 0;
        bool pos_sign = true;
       
        if (s[i] == '-')
        {
            pos_sign = false;
            i++;
        }
       
        else if (s[i] == '+')
            i++;

        while (i < len && isdigit(s[i]))
        {
            if (pos_sign && x > INT_MAX / 10)
                return INT_MAX;

            else if (!pos_sign && x < INT_MIN / 10)
                return INT_MIN;
            
            x = x * 10;
            int curr = s[i] - '0';
            
            if (pos_sign)
            {
                if (x <= INT_MAX - curr)
                    x += s[i] - '0';
                else
                    return INT_MAX;
            }
            else
            {
                if (x >= INT_MIN + curr)
                    x -= s[i] - '0';
                else
                    return INT_MIN;
            }
            i++;
        }
        return x;
    }
};

int main()
{
    Solution s;

    cout << s.myAtoi(
                "-91283472332")
         << endl;
}