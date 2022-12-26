double recPow(double x, int n)
{
    if (n == 0)
        return 1;
    if (n % 2)
        return x * recPow(x, n-1);
    return recPow(x*x, n/2);
}

class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0 || x == 1)
            return x;

        if (n > 0)
            return recPow(x, n);
        return recPow(1/x, -n);
    }
};