// https://leetcode.com/problems/roman-to-integer/
#include <iostream>
using namespace std;

class Solution
{
public:
    int romanToInt(string s)
    {
        int val = 0;

        size_t sz = s.size();

        for (size_t i = 0; i < sz; ++i)
        {
            if (s[i] == 'M')
                val += 1000;

            else if (s[i] == 'D')
                val += 500;

            else if (s[i] == 'C')
            {
                if (i < sz - 1)
                {
                    if (s[i + 1] == 'M')
                    {
                        val -= 100;
                        continue;
                    }
                    if (s[i + 1] == 'D')
                    {
                        val -= 100;
                        continue;
                    }
                }
                val += 100;
            }

            else if (s[i] == 'L')
            {
                val += 50;
            }

            else if (s[i] == 'X')
            {
                if (i < sz - 1)
                {
                    if (s[i + 1] == 'L')
                    {
                        val -= 10;
                        continue;
                    }
                    if (s[i + 1] == 'C')
                    {
                        val -= 10;
                        continue;
                    }
                }
                val += 10;
            }
            else if (s[i] == 'V')
                val += 5;
            else
            {
                if (i < sz - 1)
                {
                    if (s[i + 1] == 'V')
                    {
                        val -= 1;
                        continue;
                    }
                    if (s[i + 1] == 'X')
                    {
                        val -= 1;
                        continue;
                    }
                }
                val += 1;
            }
        }

        return val;
    }
};

int main()
{
    Solution s;
    s.romanToInt("MCMXCIV");
}