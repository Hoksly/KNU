#include <iostream>
#include <cstring>

using namespace std;

void print_mas(int * A, int n)
{
    for(int i = 0; i < n; i++)
        cout << (int) A[i] << ' ';

    cout << endl;
}

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

    cout << pos_beg << ' ' << pos_end << endl;
    cout << mx << endl;
    
    delete [] mas;
}
void task_string()
{
    char a[1000];
    cin >> a;
    char res = '1';
    int len = strlen(a);

    for(int i = 0; i < len; i++)
    {
        if(!isdigit(a[i]))
        {
            if(a[i] == '.')
                res = '2';
            else
                {res = '0'; break;}
        }
    }

    cout << res << endl;


}

void task_matrix()
{
    int n, m;
    cin >> n >> m;

    int **mas = new int*[n];
    for(int i = 0; i<n; i++)
    {
        mas[i] = new int[m];
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> mas[i][j];
        }
    }

    bool *checked_similar = new bool[n];


    for(int i = 0; i < n; i++)
    {
        
        for(int j = i+1; j < n; j++)
        {
            if(!checked_similar[j])
            {
                for(int k = 0; k < m; k++)
                {
                    if(mas[i][k] != mas[j][k])
                        break;
                    if(mas[i][k] == mas[j][k] && k == m-1)
                        {checked_similar[i] = checked_similar[j] = true;}
                    
                }
            }
        }
    }
    
    //print_mas(checked_similar, n);

    int res = 0;
    for(int i = 0; i < n; i++)
    {
        res += !checked_similar[i];
    }
    cout << res << endl;


    for(int i = 0; i < n; i++)
        delete[] mas[i];
    delete[] mas;
}


void task_N()
{
    //max sum of denomiators


}
struct res
{
    int ind;
    bool res;
};

res search_in_mas(int *mas, int t, int n)
{
    res a;
    a.res = false;
    a.ind = 0;
    //cout << "Searching: " << t << endl;
    for(int i = 0; i < n; i++)
    {
        //cout << mas[i] << ' ' << t << endl;
        if(mas[i] == t)
            { a.res = true; a.ind = i; return a;}
    }
    //cout << endl;
    return a;
}

void task_M_N()
{
    int m, n;
    cin >> m >> n;
    int mas[50];
    int ost[50];
    
    int a = m%n;
    int i = 0;
    
    mas[0] = 0;    
    ost[0] = 0;
    //cout << "a: " << mas[i] << ' ' << i << endl;    
   
    res p;
    if(i != 50)
    {   
    
        
        for(int q = 0; q < 50; q++)
        {
            for(; a < n; a*= 10, i++)
            {ost[i] = a;}
                
            
            mas[i] = a/n;
            ost[i] = a;
            //cout << "a: " << mas[i] << ' ' << i << endl;
            a %= n;
            p = search_in_mas(ost, a, i);
            if (p.res)
                break;
            
            ost[i] = a;
            
        }
        
    }
    //cout <<"Index: " << p.ind << endl;
    cout << mas[0] << '.';
    for(int k = 1; k <= p.ind; k++)
        cout << mas[k];
    cout << '*';
    i++;
    for(int k = p.ind+1; k < i; k++)
    {cout << mas[k];}
    cout << '*' << endl;
    
    //print_mas(mas, i+1);
    //print_mas(ost, i+1);
    cout << endl;

}

int find_sum_del(int N)
{
    int s = 0;
    int q = N/2 + 1;
    for(int i = 1; i < q; i++)
        s += (N%i == 0)? N/i: 0;

    //cout << N << ' ' << s << endl;
    return s;
}

int find_biggest_sum()
{
    int n;
    cin >> n;

    int m_sum = 1;
    int end = n/2;
    int max_n = 1;
    int sm = 1;
    for(int i = n; i > end; i--)
    {
        sm = find_sum_del(i);
        max_n = (m_sum < sm)? i: max_n;
        m_sum = (m_sum < sm)? sm: m_sum;
    }
    
    cout << max_n << endl;
    return n;
}

int main()
{

    task_M_N();
    

/*
8
5 5 5 1 1 1 1 1 
*/

}

    
    



