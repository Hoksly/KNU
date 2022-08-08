// https://leetcode.com/problems/roman-to-integer/
#include <iostream>
using namespace std;

int parseI(char *&s)
{
    int i = 0;

    while (*s)
    {
        switch (*s)
        {
        case 'I':
            i--;
            break;
        case 'V':
            s++;
            return i + 5;

        case 'X':
            s++;
            return i + 10;

        default:
            s++;
            return abs(i);
        }
        s++;
    }

    return abs(i);
}

int parseX(char *&s)
{
    int i = 0;

    while (*s)
    {

        switch (*s)
        {
        case 'X':
            i -= 10;
            break;
        case 'L':
            s++;
            return i + 50;

        case 'C':
            s++;
            return i + 100;

        default:
            s++;
            return abs(i);
        }
        s++;
    }

    return abs(i);
}

int parseC(char *&s)
{
    int i = 0;

    while (*s)
    {

        switch (*s)
        {
        case 'C':
            i -= 100;
            break;
        case 'D':
            s++;
            return i + 500;

        case 'M':
            s++;
            return i + 1000;

        default:
            s++;
            return abs(i);
        }
        s++;
    }
    return abs(i);
}

int RomanToInt(char *c)
{
    using namespace std;

    int res = 0;

    while (*c)
    {
        switch (*c)
        {
        case 'M':
            res += 1000;
            c++;

            break;
        case 'D':
            res += 500;
            c++;

            break;

        case 'C':
            res += parseC(c);

            break;

        case 'X':
            res += parseX(c);

            break;

        case 'I':
            res += parseI(c);

            break;

        case 'V':
            res += 5;

            c++;
            break;

        case 'L':
            res += 50;

            c++;
            break;
        }
    }

    return res;
}

inline char *copy(std::string s)
{
    char *c = new char[20];
    int i;
    for (i = 0; i < s.length(); ++i)
        c[i] = s[i];
    c[i + 1] = '\0';

    return c;
}

int main()
{

    std::string s;

    std::cin >> s;

    std::cout << RomanToInt(copy(s)) << '\n';
    return 0;
}