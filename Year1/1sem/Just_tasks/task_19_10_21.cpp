#include <iostream>
#include <cstring>
using namespace std;

int min_3(int a, int b, int c)
{
    return min(a, min(b, c));
}


void pritnt_matrix(int **A, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << A[i][j] << ' ';
        cout << endl;
    }
    
}

void task_triangle_matrix()
{
    int n;
    cin >> n;
    int **A = new int *[n];
    int **B = new int *[n];

    for(int i = 0; i < n; i++)
    {
        A[i] = new int[n];
        B[i] = new int[n];
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cin >> A[i][j];
    }
 

    for(int i = 0; i < n; i++)
    {
        B[i][i] = A[i][i];
    }

    int i_cp, j;
   
    for(int i = 1; i < n; i++)
    {
        i_cp = i;
        j = 0;
        while(i_cp < n && j < n)
        {
  
            //cout << A[i_cp][j] << B[i_cp][j+1] << B[i_cp-1][j] << endl;
            B[i_cp][j] = min_3(A[i_cp][j], B[i_cp][j+1], B[i_cp-1][j]);
           
            i_cp++;
            j++;
        }
    }
    

    for(int i = n-2; i > -1; i--)
    {
        i_cp = i;
        j = n-1;

        while(i_cp > -1 && j > -1)
        {
            B[i_cp][j] = min_3(A[i_cp][j], B[i_cp+1][j], B[i_cp][j-1]);
            j--;
            i_cp--;
        }


    }
    

    pritnt_matrix(B, n);
}
int main()
{
    //task_triangle_matrix();

    char n_str[10];
    int n = 25;

    sprintf(n_str, "%d", n);
    cout << n_str << endl;
    return 0;
/*
4
1 2 3 3
4 5 6 4
7 8 9 5
5 6 7 9
*/



}