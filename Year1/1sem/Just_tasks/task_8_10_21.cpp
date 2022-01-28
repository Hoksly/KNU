#include<iostream>
using namespace std;
const int MAX_SIZE = 1000;

void Merge(int* MAS, int beg, int end)
{
    int middle, start, final, j;
    int *mas = new int[MAX_SIZE/2];
    middle = (beg + end) / 2;

    start = beg;
    final = middle+1;
    
    for(int j = beg; j <= end; j++) 
    {
        if((start <= middle) && (final > end) || (MAS[start] < MAS[final]))
        {
            mas[j] = MAS[start];
            start++;
        }
        else
        {
            mas[j] = MAS[final];
            final++;
        }
          
    }

    for(int j = beg; j<=end;j++)
        {
            MAS[j] = mas[j];

            
        }
        delete [] mas;

} 


void MergeSort(int *MAS, int beg, int end)
{
    if(beg < end)
    {
        int m = (beg+end)/2;
        MergeSort(MAS, beg, m);
            for(int i = beg; i <= m; i++)
                cout << MAS[i] << ' ';
            cout << endl;
        MergeSort(MAS, m+1, end);
        for(int i = m+1; i <= end; i++)
                cout << MAS[i] << ' ';
            cout << endl;
        Merge(MAS, beg, end);
    }
}

int main()
{
    
    int mas[MAX_SIZE];
    int n; 
    cin >> n;

    for(int i = 0; i < n; ++i)
        cin >> mas[i];
    
    //MergeSort(mas, 0, n-1);
    
    int j = 0;
    int new_mas[MAX_SIZE];
    for(int i = 0; i < n; i++)
    {
        if(mas[i] < 0)
            {new_mas[j] = mas[i]; j++;}
        
    }

    for(int i = 0; i < n; i++)
    {
        if(mas[i] >= 0)
            {new_mas[j] = mas[i]; j++;}
        
    }
    


    for(int i = 0; i < n; i++)
    {
        cout << new_mas[i] << ' ';
    }

    cout << endl;

}
