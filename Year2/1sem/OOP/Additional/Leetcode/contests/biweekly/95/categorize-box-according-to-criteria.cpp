#include <string>
using std::string;

class Solution
{
    int bulkyDim = 10000;
    int bulkyVol = 1000000000;

public:
    string categorizeBox(int length, int width, int height, int mass)
    {
        bool isBulky = false, isHeavy = false;
        isBulky = (length >= bulkyDim) || (width >= bulkyDim) || (height >= bulkyDim);
        isBulky |= (long)length * (long)width * (long)height >= (long)bulkyVol;

        isHeavy = mass >= 100;

        if (isBulky && isHeavy)
            return "Both";

        else if (isBulky)
            return "Bulky";

        else if (isHeavy)
            return "Heavy";

        return "Neither";
    }
};