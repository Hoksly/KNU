#include <iostream>
#include "matrix.hpp"
#include "algo.hpp"
#include "test.hpp"

using namespace std;
void printV(vector<pair<size_t, size_t>> V)
{
    for(pair<size_t, size_t> pr : V)
        cout << pr.first << ' ' << pr.second << endl;
}
int main()
{
    testCollisions();
  
}