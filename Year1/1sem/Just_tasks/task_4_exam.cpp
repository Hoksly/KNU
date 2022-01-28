#include <iostream>
using namespace std;


void task_check_mas(int *pos, int *val)
{
    int n, inp; 
    cin >> n;

    bool *mas = new bool[n+1];
    *pos = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> inp;
        if(inp > n || mas[inp])
        {
            *pos = i+1;
            *val = inp;
            return;
        }

        else
        {
            mas[inp] = true;
        }
    }
    


}
/*
Tests:
inp:
9
1 2 3 9 6 4 5 8 7

out:
OK

inp:
8 
1 2 5 4 3 2 1 4

out:
Error: position: 6 value: 2

inp:
5 
1 2 7 3 2

out:
Error: position: 3 value: 7

*/

int main()
{
    int *pos = new int;
    int *val = new int;

    task_check_mas(pos, val);
    if(*pos != 0)
    {
        cout << "Error at position: " << *pos << " with value: " << *val << endl; 
    }
    else
        cout << "Evrything is alright" << endl;  

    return 0;
}