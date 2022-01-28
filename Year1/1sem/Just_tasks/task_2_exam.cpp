#include <iostream>
#include <cstring>
using namespace std;

void task_search_in_matrix()
{
    int n, m, count = 0;
    cin >> n >> m;
    char inp;
    bool * in_first = new bool[100];
    bool * in_first_checked = new bool[100];

    for(int i = 0; i < m; i++)
    {
        cin >> inp;
        in_first[inp] = true;
    }

    n--;
    bool is_similar;
    for(int i = 0; i < n; i++)
    {
        is_similar = true;
        memcpy(in_first_checked, in_first, 100);
        for(int j = 0; j < m; j++)
        {
            cin >> inp;
            in_first_checked[inp] = false;
            if(!in_first[inp])
                is_similar = false;
        }
        for(int i = 0; i < 100; i++)
        {
            if(in_first_checked[i])
                is_similar = false;
        }
        if(is_similar)
            {count++;}
    }
    
    cout <<"Similar: "<< count << endl;
}

/*
Tests:

4 3
1 1 1
2 2 2
3 3 3
4 4 4

out: 0

8 5
1 2 3 4 1
2 1 2 3 1
1 1 1 1 1
2 4 0 8 1 
1 2 3 4 4
4 4 4 2 1
1 1 2 3 4
1 2 3 4 1

out: 3



*/

int main()
{
    task_search_in_matrix();
    return 0;
}