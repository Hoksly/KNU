#include <stdio.h>
#include <iostream>
#include <cstring>


using namespace std;


int main()
{
    char a[10] = "gggg";
    char b[10] =  "gggg";
    int i;
    i = (int) (strcmp(a, b));
    cout << i << endl;
}