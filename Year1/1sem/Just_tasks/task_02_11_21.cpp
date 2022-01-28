#include <iostream>
#include<cstring>
#include <stdio.h>

using namespace std;


bool is_pal(char * a)
{
    cout << "str: " << a << endl;
    int len = strlen(a)-1;
    int l = len / 2 + 1;
    
    for(int i = 0; i < l; i++)
    {   
        cout << a[i] << ' ' << a[len-i] << endl;
        if(a[i] != a[len - i])
            {
            
            return false;}
    }
    cout << "HR" << endl;
    return true;

}

void reverse(char *s)
{
   int length, c;
   char *begin, *end, temp;
 
   length = strlen(s);
   begin  = s;
   end    = s;
 
   for (c = 0; c < length - 1; c++)
      end++;
 
   for (c = 0; c < length/2; c++)
   {        
      temp   = *end;
      *end   = *begin;
      *begin = temp;
 
      begin++;
      end--;
   }
}


int main()
{
    const int LEN = 1000;
    char a[LEN];
    char *b = new char[LEN];
    char c[LEN];
    
    cin.getline(a, LEN);
    
    cout << a << endl;
    strcpy(b, a);
    strcpy(c, a);
    reverse(b);
    //cout << "a: " << a << endl;
    //cout << "b: " << b << endl;
    
     
    int k = strlen(a)+1, i = 0;
    int nd = strlen(a);
     
    while (is_pal(strcat(a, b)) && i <= nd)
    {
        //cout<<"str: " << strcat(a, b+i) << endl;
        b++;
        i++;
        k--;
        
        
    }
    strcpy(a, c);
    strcat(a, b);
    cout << a << endl;
    cout << k << endl;
    
    
}