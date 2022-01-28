#include <iostream>

using namespace std;


int ** input_mas_2D(int &n)
{
    cin >> n;
    int **mas = new int*[n];
    
    for (int i = 0; i < n; i++)
    {   
        int *line = new int[n];
        for (int j = 0; j < n; j++)
        {
            
            cin >>  line[j];
        }
        mas[i] = line;
    }    

    return mas;
}

inline bool is_correct(const int &a11, const int &a12, const int &a21, const int &a22, const int & target)
{
    
    return a11 + a12 + a21 + a22 == target ;
}

int solve_task(int **mas,  int n, int target = 1 + 11 + 5)
{
    n--;
    int res = 0;
    
    cout << endl;
    for(int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j++)
        {//cout << i << ' ' << j << endl;
            res += (int) is_correct(mas[i][j], mas[i+1][j], mas[i][j+1], mas[i+1][j+1], target);}
    }


    
    return res;
}


int main()
{

    int n, res;
    int **mas = input_mas_2D(n);

    res = solve_task(mas, n);
    for (int i = 0; i < n; i++)
    {
        delete[] mas[i];
    }
    delete[] mas;

    cout << res << endl;

    return 0;
}
/*
1 0 5 0
5 11 11 1
1 0 1 0
5 11 11 5

5
2
1 1
1 1
*/