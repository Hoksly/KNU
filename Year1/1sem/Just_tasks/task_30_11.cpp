
#include <vector>
#include <iostream>

using namespace std;

template<class X>
void print_2d_vector(vector<vector<X>> A)
{
    int a = A.size();

    for(int i = 0; i < a; i++)
    {
        for(int j = 0; j < A[i].size(); ++j)
            cout << A[i][j] << ' ';
        cout << endl;
    }
    cout << endl;

}

void task_backpack()
{
    int n, W, inp;
    cin >> W >> n;
    vector <int> w;
    ++n;
    
    w.push_back(0);
    for (int i = 1; i < n; ++i)
    {
        cin >> inp;
        if (inp != 0 && inp < W)
            w.push_back(inp);
        
    }
    n = w.size() - 1;
    

    if(n == 0)
        {cout << 0 << endl; return ;}

    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    dp[0][0] = 1;
    
    for(int i = 1; i<= n; ++i)
    {
        for(int j = 0; j <= W; ++j)
        {
            if(w[i] <= j)
                {dp[i][j] = dp[i-1][j] || dp[i-1][j-w[i]];}
            else
                {dp[i][j] = dp[i-1][j];}
            
        }
    }

    print_2d_vector<int>(dp);

    for(int k = W; k > 0; --k)
        if(dp[n][k])
            {cout << k << endl; break;}
}

template<class X>
void print_res(X *mas, int pos, int new_pos, int n, int target)
{
    for(int i = 0; i < new_pos; i++)
        cout << mas[i] << ' ';
    cout << target << ' ';
    
    for(int i = new_pos; i < n; i++)
    { 
        if(i == pos)
            continue;
        cout << mas[i] << ' ';
    }
    cout << endl;

}

template<class X>
int find_new_pos(X* mas, int r, int l, int target)
{
    int mid;
    while(r - l > 1)
    {
        //cout << l << ' ' << r << endl;
        mid = (l+r) / 2;

        if(mas[mid] >= target)
            l = mid;
        else
            r = mid;
        

    }

    return (l+r) / 2 + 1;
}

template<class X>
int find_pos_of_wrong_el(X* mas, int n)
{
    int pos;
    n--;
    for(int i = 0; i < n; i++)
    {
        if(mas[i] < mas[i+1])
            {pos = i+1; 
            break;}
    }

    return pos;

}

template<class X>
void task_24(X *mas, int n)
{
    int pos, new_pos;
    
    
    
 
   
    pos = find_pos_of_wrong_el<X>(mas, n);

    new_pos = find_new_pos<X>(mas, pos-1, 0, mas[pos]);
  
    
    

    print_res<X> (mas, pos, new_pos, n, mas[pos]);
    
}

template<class X>
X* input_mas(int &n)
{
    cin >> n;

    X* mas = new X[n];

    for(int i = 0; i < n; i++)
        cin >> mas[i];
    
    return mas;
}

int main()
{
   task_backpack();
}
/*
10 6
11 11 11 11 11 11

10 6
2 3 4 4 6 9
10


*/


