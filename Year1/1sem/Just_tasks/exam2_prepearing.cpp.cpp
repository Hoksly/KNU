#include <iostream>
#include <string.h>
#include <cmath>
#include <string>
#include "stdio.h"
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>



using namespace std;

const int MAX_STR_LEN = 1000;

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

void task_1_1()
{
    int n;
    int ** mas = input_mas_2D(n);
    int target = 0 + 1 + 5 + 11;
    // searching for rectangles with target sum, it's unique
    n--;
    int res = 0;
    
    cout << endl;
    for(int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j++)
        {//cout << i << ' ' << j << endl;
            res += (int) is_correct(mas[i][j], mas[i+1][j], mas[i][j+1], mas[i+1][j+1], target);}
    }

    n++;
    for (int i = 0; i < n; i++)
    {
        delete[] mas[i];
    }
    delete[] mas;
    cout<< res << endl;

/*
4
1 0 1 0
5 11 5 11
1 0 1 0
1 1 1 1
*/
}

    int* input_mas_1D(int &n)
    {
        cin >> n;
        int *mas = new int[n];
        for(int  i = 0; i < n; i++)
            cin >> mas[i];
        return mas;
    }

bool * erat(int n)
{   
    // creating a bitmam for simple(?) numbers
    n++;
    bool * map = new bool[n];
    memset(map, true, n);
    map[0] = map[1] = false;
    for (int i = 2; i < n; i++)
    {
        if(map[i])
            for(int j = i; j < n; j+= i)
                map[j] = false;
        
    }

    return map;
}

int rec_search(int *mas, long n, bool *bitmap)
{
    if (n == 0)
        return (int) bitmap[mas[0]];

    return bitmap[mas[n]] + rec_search(mas, n-1, bitmap);    
}

void task_1_2()
{
    // for el in A[n]: 0 <= el < 2**(sizeof(int)**8)
    int n;
    int *mas = input_mas_1D(n);
    bool *map = erat(pow(2L, (long) sizeof(int)*8));
    
    
    
    cout << rec_search(mas, n, map) << endl;
    delete[] mas;
    delete[] map;

}

char* input_cstring(int &n)
{
    cin >> n;
    char *str = new char[n+1];
    string s; // gets(str) is better, but it's not working for my compiler...
    getline(cin, s);
    
  
    
    strcpy(str , s.c_str());
    
    //cin.getline(str);
    
    return str;
    
}

char* input_cstring_no_len()
{
    
    char *str = new char[MAX_STR_LEN];
    string s;
    getline(cin, s);// gets(str) is better, but it's not working for my compiler...
    
    strcpy(str , s.c_str());
    
    return str;
    
}


void task_1_3()
{
    int len_str, len_mask, pos_m = 0, pos_s = 0;
    char *str = input_cstring(len_str);
    char *mask = input_cstring(len_mask);

    bool res = true;
    while (true)
    {
        
        if(pos_m >= len_mask)
        {
            res = pos_s == len_str;
            break;
        }
        if(pos_s >= len_str)
        {
            res = pos_m = len_mask;
            break;
        }

        if(mask[pos_m] == '?')
            {pos_m++; pos_s++;}
        
        else if(mask[pos_m] == '*')
        {
           
            if (pos_m != len_mask -1)
              {
                pos_m++;
                while(str[pos_s] != mask[pos_m]) // ** would means k symbols and after them symbol *
                {
                
                    if(pos_s == len_str) // this means we haven't enough symbols in string, but rest of the mask isn't empty 
                    {
                        res = false;
                        break;
                    }
                    pos_s++;
                
                }
              } 
            else
                break; 
            
        }
        else
        {
            if(mask[pos_m] != str[pos_s])
                {res = false; break;}
            pos_s++;
            pos_m++;
        }
        


    }
    string answ = (res)? "YES" :"NO";
    cout << answ << endl;


}

template<class X> //  allows point to be: (double, double) or anythig else... 
struct point_dec
{
    X x;
    X y;  
};

template <class X>
struct point_pol
{
    X r;
    double angle; //radians

};


template <class X >
void take_input_point(X &a, X &b) // allows point to be:  (double, double) or (int, int) ...
{
    cin >> a >> b;
}

template<class X> 
void convert_point(point_dec<X> &A, point_pol<X> &B, double eps)
{
    B.r = sqrt(A.x*A.x + A.y*A.y);
    B.angle = acos(A.x/B.r);
    if(fabs(sin(B.angle) - A.y/B.r) > eps)
        B.angle *= -1;
    
}

void task_2_1()
{
    const double EPS = 0.00000001;
    point_dec<double> A;
    point_pol<double> B;
    take_input_point(A.x, A.y);
    convert_point<double>(A, B, EPS);


    cout << "r: " << B.r << " angle: " << B.angle;
    


}

void task_2_3()
{
    int len;
    char *str = input_cstring_no_len();
    
    
    int counter = 0;
    int res = 0;
    bool switcher = false;
   
    while(*str != '\0')
    {
        if(isblank(*str) && switcher)
            {switcher = false; res = (counter != 0)? max(counter, res): res; counter = 0;}
        else if(!isblank(*str) && !switcher)
            {counter++; switcher = true;}

        else
        {counter++;}

        str++;            
    }
    cout << res << endl;

}

struct t_time
{
    int hours;
    int minutes;
    int seconds;

};

void take_time_input(t_time &t)
{
    cin >> t.hours >> t.minutes >> t.seconds;
    cout << t.seconds << ' ' << t.minutes << ' ' << t.seconds << endl;

}

void task_3_2()
{
    t_time t;
    take_time_input(t);

    t.seconds += 15;
    //cout << t.seconds << endl;
    if(t.seconds >= 60)
        {t.seconds -= 60; t.minutes += 1;}
    //cout << t.seconds << endl;
    if(t.minutes >= 60)
        {t.minutes -= 60; t.hours += 1;}
    
    if(t.hours >= 24)
        {t.hours -= 24;}

    cout << t.hours << ' ' << t.minutes << ' ' << t.seconds << endl;

    

}

int main()
{
    
   task_1_3();
}