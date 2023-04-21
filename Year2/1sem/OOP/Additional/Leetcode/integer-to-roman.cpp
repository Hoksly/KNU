#include <string>
using namespace std;

class Solution
{
public:
    string intToRoman(int num)
    {
        string s = "";
        while (num > 999)
        {
            num -= 1000;
            s += 'M';
        }

        if (num > 899)
        {
            num -= 900;
            s += "CM";
        }
        while (num > 499)
        {
            num -= 500;
            s += "D";
        }
        if (num > 399)
        {
            num -= 400;
            s += "CD";
        }

        while (num > 99)
        {
            num -= 100;
            s += "C";
        }

        if (num > 89)
        {
            num -= 90;
            s += "XC";
        }
        while (num > 49)
        {
            num -= 50;
            s += "L";
        }
        if (num > 39)
        {
            num -= 40;
            s += "XL";
        }
        while (num > 9)
        {
            num -= 10;
            s += 'X';
        }
        if (num > 8)
        {
            num -= 9;
            s += "IX";
        }
        if (num > 4)
        {
            num -= 5;
            s += "V";
        }
        if (num > 3)
        {
            num -= 4;
            s += "IV";
        }
        while (num > 0)
        {
            s += "I";
            --num;
        }

        return s;
    }
};