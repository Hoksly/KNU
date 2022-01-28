#include <iostream>
using namespace std;


struct rat
{
    int a;
    int b;
};

struct mas_with_n
{
    rat * mas;
    int n;
};

bool bigger(rat fr, rat sc)
{
    return fr.a*sc.b > sc.a*fr.b;
}

int mx(rat *mas, int n)
{
    
    int mx = 0;
    for(int i = 1; i < n; i++)
        if(bigger(mas[i], mas[mx]))
            mx = i;
    return mx;

}


mas_with_n take_input()
{
    mas_with_n ret;
    int n;
    cin >> n;
    ret.n = n;
    rat *mas = new rat[n];
    
    for(int i = 0; i < n; i++)
        cin >> mas[i].a >> mas[i].b;
    ret.mas = mas;
    return ret;
}

int main()
{

    //rat * mas = take_input();
    
    mas_with_n mas = take_input();
    int ind = mx(mas.mas, mas.n);
    cout << ind << endl;
    
    return 0;
    
}
