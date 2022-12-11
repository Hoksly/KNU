#include <iostream>

int MAXPOSITIVE =  2147483647;
int MAXNEGATIVE =  -2147483648;

class Solution {
public:
    int reverse(int x) {
        bool isNegative = false;
        if (x < 0)
        {
            isNegative = true;
            if (x == MAXNEGATIVE)
                return 0;
            x = -x;
            
        }
        int res = 0;

        while (x > 0)
        {
            if ((MAXPOSITIVE - x % 10) / 10 < res)
            {
                return 0;
            }
            
            res = res * 10 + x % 10;
            x /= 10;
        }

        return (isNegative)? -res: res ;
        
    }
    
};

int main()
{
    Solution s;
    std::cout << s.reverse(2147483647) << std::endl;

}