#include <iostream>
#include <vector>
#include <string>
using namespace std;


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
        for(int i = dgr; i <= 0; i++)
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


mnt solo_mult(mnt a, int num, int dgr)
{
    mnt ret;
    int add_num = 0, val;
    vector<int> A;

    for(int i = a.size - 1; i >= 0; i--)
    {
        val = a.mas[i] * num + add_num;
        add_num = 0;
        add_num = val / 10;
        val = val % 10; 
        A.push_back(val);
       
    }
    if(add_num)
    {
        A.push_back(add_num);
        dgr++;
    }
    reverse(A);
    ret.dgr = dgr;
    ret.is_negative = false;
    ret.mas = A;
    ret.size = A.size(); 
    

    return ret;
}

mnt multiplication(mnt a, mnt b)
{
    mnt res, clone, val;
    vector<int> A(1, 0);
    vector<int> B;
    res.mas = A;
    res.dgr = 0;
    res.is_negative =false;
    res.size = 1;
    cout << endl;
    for(int i = b.size-1; i >= 0; i--)
    {
        val = solo_mult(a, b.mas[i], a.dgr + b.size - i);
        res = sbm2(res, val);
       
    }
    cout << endl;
    res.dgr = a.dgr + b.dgr;
    return res;
    


}

int main()
{
    /*
8834212
4
2438213
1
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
 
 
    //a3 = multiplication(a1, a2);
    //a3 = solo_mult(a1, 9, 1);
    a3 = sbm2(a1, a2);
    pr_mas(a3.mas, a3.is_negative, a3.dgr);
    cout.precision(16);
    //cout.adjustfield(16)
    //cout << 88342.12 * 24.38213 << endl;
    //cout << 82.1 * 321<< endl;
    return 0;

}