#include <iostream>

using namespace std;

char LONG_MONTH[] = {1, 3, 5, 7, 8, 10, 12};
char SHORT_MONTH[] = {4, 6, 9, 11};
char LONG_LEN = 7;
char SHORT_LEN = 4;

template<class X, class Y>
bool search(X target, X *mas, Y len)
{
    for(Y i = 0; i < len; ++i)
    {
        if(target == mas[i])
            return true;
    }
    return false;
}

struct Time
{
    char day;
    char month;
    int year;

    Time (int a, int b, int c)
    {
        day = a;
        month = b;
        year = c;
    }

    Time()
    {
        day = month = year = 0;
    }




};



Time distance(Time a, Time b)
{
    // a < b

    
    

    int year_distance = 0;
    char day_distance = 0, month_distance = 0;
   
    day_distance = b.day - a.day;

    if (day_distance < 0)
    {   
        --month_distance;
        
        if(search<char, char> (a.month, LONG_MONTH, LONG_LEN))
        {
            day_distance += 31;
        }
        
        else if(search<char, char> (a.month, SHORT_MONTH, SHORT_LEN))
        {
            day_distance += 31;
        }
        
        else
        {
            if(a.year % 4 == 0)
                if(a.year % 100 == 0)
                    if(a.year % 400 == 0)
                        day_distance += 29;
                    else
                        day_distance += 28;
                else
                    day_distance += 28;
            else
                day_distance += 28;

        }
    }
   
    month_distance += (b.month - a.month);
    
    if(month_distance < 0)
        {month_distance += 12; --year_distance;}    

    year_distance += (b.year - a.year);
    
    
    return Time(day_distance, month_distance, year_distance);
    
    
    

}


struct point
{
    int x;
    int y;


};

bool CheckCord(point a)
{
    if (a.x > 0 && a.x < 9 && a.y > 0 && a.y < 9)
        return true;
    return false;
}

bool CheckHorse(point P, point S)
{
    if (!(CheckCord(P) && CheckCord(S)))
        return false;

    if((abs(P.x - S.x) == 1 && abs(P.y - S.y) == 2) || (abs(P.x - S.x) == 2 && abs(P.y - S.y) == 1))
    {
       

        return true;
    }
    
    return false;
    
}


char * convert(int a)
{
    int len = 1, a_cp = a;

    while(a_cp > 0)
    {a_cp /= 10; ++len;}

    char *mas = new char[len];

    for(int i = len-2; a > 0; --i, a /= 10)
    {
        mas[i] = '0' + (a % 10);
        
    }

    mas[len-1] = '\0';
    cout << mas<< endl;
    return mas;
    
}

int MAX_SIZE = 100;
char* convert_2(int a)
{
    char *mas = new char[MAX_SIZE];

    int step = 0;
    for(int i = 1; i<a; i*=10, ++step);
    cout << step << endl;

    int n, a_cp, pos = 0;
    for(int a_cp = a ; step > 0; ++pos)
    {

        for(int q = 0, s = 1; q < step; ++q, s *= 10)
            n = (a / s) % 10;
        
        cout << n << endl;
        mas[pos] = '0' + n;
        pos++;
        --step;
        for(int i = 0; i < step; ++i, ++pos)
        {
            mas[pos] = '0';
        }
        mas[pos] = '+';
        
    }

    mas[pos-1] = '\0';
    cout << mas << endl;
    return mas;

}
int main()
{

    convert_2(827);
    return 0;


}
