#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*
struct mnt{

    char* mas;
    int dgr;
    bool is_negative;

};
*/
class mnt
{   
    public:
        vector<int> mas;
        int dgr;
        int size;
        bool is_negative;
   
};

int pow(int a, int step)
{
    if (step == 0)
        return 1;
    if(step % 2 == 1)
        return a*pow(a, step-1);
    return pow(a*a, step/2);
}

/*
void rv (vector<int> A)
{
    int tmp, sz;
    sz = A.size();

    for (int i = 0; i < sz/2 + sz% 1; i++)
    {
        tmp = A[sz-1-i];
        A[sz-1-i] = A[i];
        A[i] = tmp;

    }

}


mnt sum(mnt a, mnt b)
{
    if (a.dgr > b.dgr)
    {
        for (int i = 0; i < a.dgr-b.dgr; i++)
        {
            b.A.insert(b.A.begin(), 0);
        }
    }

    else
    {
        for(int i = 0; i < b.dgr - a.dgr; i++)
        {
            a.A.insert(a.A.begin(), 0);
        }
    }
    rv(a.A);
    rv(b.A);
    // now they are both reversed, starting summing
   
    bool add_one = false;

    mnt ret;
    ret.dgr = a.dgr;
    ret.A = vector<int> (a.A.size());


    for(int i = 0; i < a.A.size(); i++)
    {

    }



}
*/





void pr_mas(vector<int> &a, bool is_negative, int dgr)
{   
    if(is_negative)
        cout << '-';
    if(dgr > 0)
    {
        for(int i = 0; i < dgr+1; i++)
        cout << a[i];
        cout << '.';
        for(int i = dgr+1; i < a.size(); i++)
        cout << a[i];
    }
    else
    {
        for(int i = dgr; i < 0; i++)
            cout << '0';
        cout << '.';
        for(int i = 0; i < a.size(); i++)
            cout << a[i];
    }

    cout << endl;
}



void reverse(vector<int> &A)
{
    for(int i = 0; i < A.size()/2 + A.size() % 2; i++)
    {
        int tmp = A[i];
        A[i] = A[A.size()-1-i];
        A[A.size()-1-i] = tmp; 
    }
}

int sum_eq(mnt a, mnt b, vector<int> &ret)
{
    
    int add_one = 0, val;
    int pb = a.size - b.size;
    for(int i = a.mas.size() -1; i >= 0; i--)
    {
        val = a.mas[i] + b.mas[i-pb] + add_one;
        cout << a.mas[i] << ' ' << b.mas[i-pb] << ' ' << val << endl;
        
        add_one = 0;
        if (val > 9)
            {
                add_one = 1;
                val -= 10;
            }
        ret.push_back(val);
        
    }

    int new_dg = max(a.dgr, b.dgr);
    if (add_one)
    {
        ret.push_back(1);
        new_dg++;
    }
    //pr_mas(ret);
    reverse(ret);
    return new_dg;

}


int str_int(string s)
{
    int ret = 0;
    int is_negative = 1;

    if(s[0] == '-')
        is_negative = -1;
    else
        ret += (s[0] - '0') * pow(10, s.size()-0-1);


    for(int i = 1; i < s.size(); i++)
    {
        ret += (s[i] - '0') * pow(10, s.size()-i-1);
    }
    return ret * is_negative;
}


mnt cnv(string s, int sz, int dgr, bool is_negative)
{
    vector<int> ret;
    //sz--;

    if (!is_negative)
    {
        
        ret.push_back(s[0] - '0');
    }
    
    for(int i = 1; i < s.size(); i++)
    {
        
        ret.push_back(s[i] -'0');
    }

    mnt rr;
    rr.mas = ret;
    rr.dgr = dgr;
    rr.is_negative = is_negative;
    rr.size = ret.size();

    return rr;   
}



bool bigger(mnt a, mnt b)
{

    if(a.dgr != b.dgr)
    {
        if (a.dgr > b.dgr)
            return true;
        return false;
    }
        
    for(int i = 0; i < min(a.size, b.size); i++)
    {
        if(a.mas[i] > b.mas[i])
            return true;
        else if(a.mas[i] < b.mas[i])
            return false;

    }
    return false;


}


mnt sbm2(mnt a, mnt b)
{
    /*
    123.4
   +        => 124.634
    001.234
    */
    vector<int> A;
    int a_dgr = a.dgr, b_dgr = b.dgr;
    while(a_dgr < 0 || b_dgr < 0)
    {
        a_dgr++;
        b_dgr++;
    }

    int a_sz = a.size +b_dgr, b_sz = b.size + a_dgr;
    for(int i = 0; i < a_sz - b_sz; i++)
        A.push_back(a.mas[a.size - 1 -i]);

    for(int i = 0; i < b_sz - a_sz; i++)
        A.push_back(b.mas[b.size - 1 -i]);

    int add_one = 0, val;
    for(int i = 0; i < min(a.size, b.size) - abs(a_dgr - b_dgr); i++)
    {
        if(a_sz > b_sz)
        {
            val = a.mas[a.size - i - 1 - (a_sz - b_sz)] + b.mas[b.size - i - 1] + add_one;
            add_one = 0; 
            if(val > 9)
            {
                val -= 10;
                add_one = 1;
            }
            A.push_back(val);
        }
        else
        {
            val = a.mas[a.size - i - 1] + b.mas[b.size - i - 1 - (b_sz - a_sz)] + add_one;
            add_one = 0; 
            if(val > 9)
            {
                val -= 10;
                add_one = 1;
            }
            A.push_back(val);
        }
    }

    if (a_dgr> b_dgr)
    {
        for(int i = a_dgr - b_dgr - 1; i >= 0; i--)
            {
                
                val = a.mas[i] + add_one;
                add_one = 0;
                if(val > 9)
                {
                    val -= 10;
                    add_one = 1;
                }
                A.push_back(val);
            }
    }
    else
    {
        for(int i = b_dgr - a_dgr - 1; i >= 0; i--)
        {
            val = b.mas[i] + add_one;
            add_one = 0;
            if(val > 9)
            {
                val -= 10;
                add_one = 1;
            }
            A.push_back(val);
        }
    }
    int n_dgr = max(a.dgr, b.dgr);
    if(add_one)
    {
        A.push_back(1);
        n_dgr++;
    }

    reverse(A);
    mnt ret;

    ret.mas = A;
    ret.size = A.size();
    ret.dgr = n_dgr;
    ret.is_negative = false;
    return ret;
}


mnt substraction(mnt a, mnt b, bool is_negative = false)
{
    vector <int> A;
    int remove_one = 0, val;
    // a - b, 
    if(bigger(b, a))
        return substraction(b, a, true);


    int a_dgr = a.dgr, b_dgr = b.dgr;
    while(a_dgr < 0 || b_dgr < 0)
    {
        a_dgr++;
        b_dgr++;
    }

    int a_sz = a.size + b_dgr, b_sz = b.size + a_dgr;
    for(int i = 0; i < a_sz - b_sz; i++)
        A.push_back(a.mas[a.size - 1 -i]);

    if (b_sz > a_sz)
    {
        for(int i = 0; i < b_sz - a_sz; i++)
        {
            val = 0 - remove_one - b.mas[b.size - 1 -i];
            if (val < 0)
            {
                val += 10;
                remove_one = 1;
            }
            A.push_back(val);
        
        }
    }


    for(int i = 0; i < min(a.size, b.size) - abs(a_dgr- b_dgr); i++)
    {
        if(a_sz > b_sz)
        {
            val = a.mas[a.size - i - 1 - (a_sz - b_sz)] - b.mas[b.size - i - 1] - remove_one;
            remove_one = 0; 
            if (val < 0)
            {
                val += 10;
                remove_one = 1;
            }
            A.push_back(val);
        }
        else
        {
            val = a.mas[a.size - i - 1] - b.mas[b.size - i - 1 - (b_sz - a_sz)] - remove_one;
            remove_one = 0; 
            if (val < 0)
            {
                val += 10;
                remove_one = 1;
            }
            A.push_back(val);
        }
    }
    
    if (a_dgr > b_dgr)
    {
        for(int i = a_dgr - b_dgr - 1; i >= 0; i--)
            {
                
                val = a.mas[i] - remove_one;
                remove_one = 0;
                if (val < 0)
            {
                val += 10;
                remove_one = 1;
            }
                A.push_back(val);
            }
    }

    int i = A.size() - 1, n_dgr = a.dgr;
    while(A[i] == 0)
    {
        A.erase(A.end());
        i--;
        n_dgr--;
    }

    
    reverse(A);
    if(A.size() == 0)
        A.push_back(0);
    
    mnt ret;

    ret.mas = A;
    ret.size = A.size();
    ret.dgr = n_dgr;
    ret.is_negative = is_negative;
    return ret;

}


int main()
{
    /*
    121341224124123
    5
    54474731812
    8
    */

    

    string s1, s2;
    string dg1, dg2;
    
    getline(cin, s1);
    getline(cin, dg1);
    getline(cin, s2);
    getline(cin, dg2);

    mnt a1, a2, a3;

    a1 = cnv(s1, s1.size(), str_int(dg1), s1[0] == '-');
    a2 = cnv(s2, s2.size(), str_int(dg2), s2[0] == '-');
 
 
    a3 = substraction(a1, a2);
    pr_mas(a3.mas, a3.is_negative, a3.dgr);
    cout << a3.dgr << endl;
     


}