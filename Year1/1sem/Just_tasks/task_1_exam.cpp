#include <iostream>
using namespace std;

void task_search_line()
{

    int n;
    cin >> n;
    int *mas = new int[n];
    for(int i = 0; i < n; i++)
        cin >> mas[i];

    int beg=0, end=0, mx = 1, cur_el;
    int pos_beg = 0, pos_end = 0;
    cur_el = mas[0];
    for(int i = 1; i<n; i++)
    {
        if(mas[i] != cur_el)
            {   
                if(mx < end-beg+1)
                {
                    pos_beg = beg;
                    pos_end = end;
                    mx = end-beg+1;
                
                }
                cur_el = mas[i];
                beg=end=i;
            }
        else
            end++;
    }
   
    if(mx < end-beg+1)
    {
        pos_beg = beg;
        pos_end = end;
        mx = end-beg+1;
    }

    cout << "Position: from " << pos_beg << " to " << pos_end << endl;
    cout << "len: " << mx << endl;
    
    delete [] mas;
}
/*
Tests:
inp:
16
1 1 1 1 2 3 2 1 2 2 2 2 2 1 8 7

out:
8 12
5


inp:
8
1 2 3 4 5 6 7 8

out:
0 0
1
*/

int main()
{
    //task_search_line();
    system("echo gg");
    return 0;
}