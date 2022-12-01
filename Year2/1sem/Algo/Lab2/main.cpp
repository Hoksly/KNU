#include <iostream>
#include "matrix.hpp"
#include "algo.hpp"
#include "test.hpp"

using namespace std;
void printV(vector<pair<size_t, size_t>> V)
{   
    cout << "SIZE: " << V.size() << endl;
    for(pair<size_t, size_t> pr : V)
        cout << pr.first << ' ' << pr.second << endl;
}
int main()
{
   cout << testComplexity() << endl;
   // testExecutionTime();
}