#include <iostream>
#include "matrix.hpp"
#include "algo.hpp"
using namespace std;
/**/
void printV(vector<pair<size_t, size_t>> V)
{
    for(pair<size_t, size_t> pr : V)
        cout << pr.first << ' ' << pr.second << endl;
}
int main()
{
    Matrix A("out.txt");
    cout << A << endl;
    Matrix B("big.txt");

   
    printV(rabinCarpSearchAll(B, A));
    
}