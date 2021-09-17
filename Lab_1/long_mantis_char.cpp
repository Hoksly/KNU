#include <iostream>
#include <string>

using namespace std;


class mnt
{   
    public:
        char mas[256];
        int dgr = 0;
        int size = 256;
        bool is_negative = false;
        bool is_zero = false;
   

    
};


mnt copy(mnt a)
{
    mnt b;

    char mas_cp[256];
    b.dgr = a.dgr;
    b.is_negative = a.is_negative;
    b.size = a.size;
    b.is_zero = a.is_zero;

    for(int i = 0; i < a.size; i++)
        b.mas[i]= a.mas[i];

    return b;
    
}

void reverse(mnt &a)
{
    for(int i = 0; i < a.size/2 + a.size % 2; i++)
    {
        int tmp = a.mas[i];
        a.mas[i] = a.mas[a.size-1-i];
        a.mas[a.size-1-i] = tmp; 
        
    }
}

mnt convert(string s, int n)
{
    bool is_negative;
    int sz;
    mnt a;
   
    if(s[0] == '-')
    {
        sz = s.size()-1;
        is_negative = true;
    }
    else if(s[0] == '0' && s.size() == 1)
    {
        a.is_zero = true;
        return a;
    }
    else
    {
        sz = s.size();
        is_negative = false;
    }


    if(!is_negative)
        a.mas[0] = s[0] - '0';

    for(int i = 1; i < s.size(); i++)
    {
        a.mas[i] = s[i] - '0';
        //cout << (int) a.mas[i] << ' ';
    }    

    
    a.dgr = n;
    a.is_negative = is_negative;
    a.size = s.size() - (int) is_negative;
    return a;

}

void print(mnt a)

{
    cout << endl;
    if(a.is_negative)
        cout << '-';

    if(a.dgr < 0)
        cout << "0.";

    for(int i = a.dgr; i < -1; i++)
    {
        cout << '0';
    }

    for(int i = 0; i <= min(a.dgr, a.size-1); i++)
        cout << (int) a.mas[i];
    
    if(a.dgr != a.size -1 && a.dgr >= 0 && a.size > a.dgr)cout << '.' ;

    for(int i = max(a.dgr+1, 0); i < a.size; i++)
        cout << (int) a.mas[i];
    
    for(int i = 0; i < a.dgr - a.size + 1; i++)
        cout << '0';

    //cout << endl << a.dgr << endl;
    cout << endl;
}

void pr_mas(char *a, int s)
{
    for(int i = 0; i < s; i++)
        cout << (int) a[i] << ' ';
    cout << endl;
}

mnt take_input()
{
    //cin.ignore(200);
    string s, k;
    int d;
    getline(cin, s);
    cin >> d;
    getline(cin, k);
    //cout << s.size() << ' ' << d << endl;
    //cout << s << endl;
    return(convert(s, d));
}

mnt sbm2(mnt a, mnt b)
{
    /*
    123.4
   +        => 124.634
    001.234
    */
    mnt ret;
    if(a.is_zero)
        return b;
    if(b.is_zero)
        return a;

    //cout << "gg123" << endl;
    int a_dgr = a.dgr, b_dgr = b.dgr, shift = 0;
    bool null_writed;
    while(a_dgr < 0 || b_dgr < 0)
    {
        a_dgr++;
        b_dgr++;
    }

    int a_sz = a.size +b_dgr, b_sz = b.size + a_dgr;
    for(int i = 0; i < a_sz - b_sz; i++, shift++)
        if(a.size - 1 -i >= 0)
            ret.mas[shift] = (a.mas[a.size - 1 -i]);
        else{
            ret.mas[shift] = (char) 0;
            null_writed = true;
        }
    
    

    for(int i = 0; i < b_sz - a_sz; i++, shift++)
    {
        if(b.size - 1 -i >= 0) 
            ret.mas[shift] = b.mas[b.size - 1 -i];
        else{
            ret.mas[shift] = (char) 0;
            null_writed = true;
        }

    }
        
    

    char add_one = 0, val;
    
    //int shift = abs(a.size - b.size + b.dgr - a.dgr);

    for(int i = 0; i < min(a.size, b.size) - abs(a_dgr - b_dgr); i++, shift++)
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
            //cout << "HERE 3" << endl;

            ret.mas[shift] = val;
            
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
            
            ret.mas[shift] = val;
            //cout << "HERE 4" << endl;
        
        }
    }

    //shift = abs(a.size - b.size - shift);
    int shift_2 = abs(a.dgr - b.dgr) - 1;

    if (a_dgr> b_dgr)
    {
        for(int i = a_dgr - b_dgr - 1; i >= 0; i--, shift++)
            {
                
                if(a.size > i)
                    val = a.mas[i] + add_one;
                
                else if(!null_writed)
                    val = 0;
                
                else{
                    shift--;
                    continue;
                }

                add_one = 0;
                //cout << "HERE " <<(int) a.mas[i] << endl;
                if(val > 9)
                {
                    val -= 10;
                    add_one = 1;
                }
                ret.mas[shift] = val;

                //cout << "HERE " << (int) val<< endl << endl;
            }
    }
    else
    {
        for(int i = b_dgr - a_dgr - 1; i >= 0; i--, shift++)
        {
            if(b.size > i)
                    val = b.mas[i] + add_one;
                
                else if(!null_writed)
                    val = 0;
                
                else{
                    shift--;
                    continue;
                }
            add_one = 0;
            if(val > 9)
            {
                val -= 10;
                add_one = 1;
            }
            ret.mas[shift] = val;
            //cout << "HERE 6" << endl;
        }
    }
    int n_dgr = max(a.dgr, b.dgr);
    
    if(add_one)
    {
        ret.mas[shift] = 1;
        n_dgr++;
        shift++;
    }

    
    

    ret.size = shift;
    ret.dgr = n_dgr;
    ret.is_negative = false;
    ret.is_zero = false;

    reverse(ret);
    return ret;
}

bool bigger (mnt a, mnt b)
{

    if(a.dgr > b.dgr)
        return true;
    else if(b.dgr > a.dgr)
        return false;

    else
    {
        for(int i = 0; i < min(a.size, b.size); i++)
        {
            if(a.mas[i] > b.mas[i])
                return true;
            if(b.mas[i] > a.mas[i])
                return false;
        }
    }    

    return false;

}


mnt substraction(mnt a, mnt b, bool is_negative = false)
{
    mnt ret;
    if(a.is_zero)
    {
        ret = copy(b);
        ret.is_negative = !b.is_negative;
    }
    if(b.is_zero)
        return copy(a);

    int remove_one = 0, val;
    bool writed_number;
    // a - b, 
    if(bigger(b, a))
        return substraction(b, a, true);


    int a_dgr = a.dgr, b_dgr = b.dgr;
    while(a_dgr < 0 || b_dgr < 0)
    {
        a_dgr++;
        b_dgr++;
    }

    int a_sz = a.size + b_dgr, b_sz = b.size + a_dgr, shift = 0;

    for(int i = 0; i < a_sz - b_sz; i++, shift++)
        ret.mas[shift] =a.mas[a.size - 1 -i];

    if (b_sz > a_sz)
    {
        for(int i = 0; i < b_sz - a_sz; i++, shift++)
        {
            if(b.size - 1 -i >= 0)
                val = 0 - remove_one - b.mas[b.size - 1 -i];
            else
                val = 0 - remove_one;
            if (val < 0)
            {
                val += 10;
                remove_one = 1;
                writed_number = true;
            }
            //cout << "HERE1 " << val << endl;
            ret.mas[shift] = val;;
        
        }
    }


    for(int i = 0; i < min(a.size, b.size) - abs(a_dgr- b_dgr); i++, shift++)
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
            ret.mas[shift] = val;
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
            //cout<< "HERE2 " << (int) val << endl;
            ret.mas[shift] = val;
        }
    }
    
    if (a.dgr > b.dgr)
    {
        for(int i = a.dgr - b.dgr - 1; i >= 0; i--, shift++)
        {
                
            if(a.size > i)
                val = a.mas[i] - remove_one;
            else if(!writed_number)
                val = 0 - remove_one;
            else
            {
                shift --;
                continue;
            }
            remove_one = 0;
            if (val < 0)
            {
                val += 10;
                remove_one = 1;
            }
            //cout << "HERE3 " << (int) val << endl;
            ret.mas[shift] = val;
        }
    }

    int i = shift-1, n_dgr = a.dgr;
    //cout << "HERE4 " << i << ' ' << (int) (ret.mas[i] == 0)<< endl;
    while(ret.mas[i] == 0)
    {
        i--;
        n_dgr--;
        shift--;
    }


    /*
    problem with zero!!!! need specific zero-number type.
    */


    ret.size = shift;
    ret.dgr = n_dgr;
    ret.is_negative = is_negative;
    reverse(ret);
    return ret;

}

mnt multipicata_one_digit(mnt &a, char d, char add_dgr)
{
    mnt b;
    if (d == 0)
    {
        b.dgr = 0;
        b.is_negative = false;
        b.size = 1;
        b.mas[0] = (char) 0;
        b.is_zero = true;
        return b;
    }
    b = copy(a);
   

    for(char i = 1; i < d; i++)
    {
        b = sbm2(b, a);
    }
    b.dgr += (int) add_dgr;

    return b;
}

mnt multipication(mnt &a, mnt &b)
{
    mnt res, q;
    res.dgr = 0;
    res.is_negative = false;
    res.size = 1;
    res.is_zero = true;
    res.mas[0] = (char) 0;
    //print(b);
    for(int i = 0; i < a.size; i++)
    {
        
        q = multipicata_one_digit(b, a.mas[a.size - i - 1], a.dgr - a.size  + i+1);
        
        
        res = sbm2(res, q);
    }

    return res;
}


class LongFloat
{
   
public:
    mnt value;
    
    LongFloat (mnt a)
    {
        value = a;
    }

    LongFloat ()
    {

    }

    int size()
    {
        return value.size;
    }
    int dgr()
    {
        return value.dgr;
    }

    char* mas()
    {
        return value.mas;
    }

    bool is_zero()
    {
        return value.is_zero;
    }

    bool is_negative()
    {
        return value.is_negative;
    }

    LongFloat operator + (LongFloat b)
    {
    
        if(value.is_negative && b.is_negative())
        {
            mnt ret = sbm2(value, b.value);
            ret.is_negative = true;
            return LongFloat(ret);
        }
            
        if(value.is_negative)
        {
            return LongFloat(substraction(b.value, value));
        }
        if(b.is_negative())
        {
            return LongFloat(substraction(value, b.value));
        }
        else
            return LongFloat(sbm2(value, b.value));
    }

    LongFloat operator- (LongFloat b)
    {
        if(value.is_negative && b.is_zero())
        {
            mnt ret = substraction(b.value, value);
            //ret.is_negative = true;
            return ret;
        }
            
        else if(value.is_negative)
        {
            mnt ret = sbm2(value, b.value);
            ret.is_negative = true;
            return substraction(b.value, value);
        }
        else if(b.is_negative())
        {
            return sbm2(value, b.value);
        }
        else
            return substraction(value, b.value);    
    }

    LongFloat& operator = (LongFloat a)
    {
        value = copy(a.value);

        return *this;
    }

    LongFloat operator* (LongFloat b)
    {
        if(value.is_negative && b.is_negative())
            return LongFloat(multipication(value, b.value));
        if(value.is_negative || b.is_negative())
        {
            mnt ret = multipication(value, b.value);
            ret.is_negative = true;
            return LongFloat(ret);
        }
        return LongFloat(multipication(value, b.value));

    }

    void print()
    {
        cout << endl;
    if(value.is_negative)
        cout << '-';

    if(value.dgr < 0)
        cout << "0.";

    for(int i = value.dgr; i < -1; i++)
    {
        cout << '0';
    }

    for(int i = 0; i <= min(value.dgr, value.size-1); i++)
        cout << (int) value.mas[i];
    
    if(value.dgr != value.size -1 && value.dgr >= 0 && value.size > value.dgr)cout << '.' ;

    for(int i = max(value.dgr+1, 0); i < value.size; i++)
        cout << (int) value.mas[i];
    
    for(int i = 0; i < value.dgr - value.size + 1; i++)
        cout << '0';

    //cout << endl << a.dgr << endl;
    cout << endl;
    }
    

};


int main()
{
    mnt a, b;
    a = take_input();
    b = take_input();
    
    
    //cout << a.dgr << ' ' << b.dgr << endl;
    LongFloat A(a);
    LongFloat B(b);
    LongFloat C;
   //mnt res = multipicata_one_digit(a, 2, 0);
   //mnt res = copy(a);
   // mnt res = sbm2(a, b);
    //pr_mas(res.mas, res.size);
    
    C = A * B;
    C.print();
    
    
   //cout << (int) res.mas[0] << endl;
   


    return 0;
}