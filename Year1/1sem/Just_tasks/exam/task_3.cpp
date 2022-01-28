#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

char* input_cstring_no_len(int &n)
{
    
    char *str = new char[n+1];
    string s; // gets(str) is better, but it's not working for my compiler... (same problem with getline, IDK why)
    getline(cin, s); // on windows evrything with gets/getline for cstrings works fine, but not on Linux 
    
  
    
    strcpy(str , s.c_str());
    n = strlen(str);
    //cin.getline(str);
    
    return str;
    
}

bool solve_task(char *str, char *mask, int len_mask, int len_str)
{
    int pos_m = 0,  pos_s = 0;

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
    //cout << (int) res << endl;
    return res;
}

void print_res(bool res)
{
    cout << ((res)? "YES": "NO") << endl;
}
template <class X>
void print_suggestion(X str)
{
    try
    {
        cout << str << ' ';
    }
    catch(const std::exception& e)
    {   
        cout << "Error occured when printing suggestion" << endl;
        std::cerr << e.what() << '\n';
    }
    
}

int main()
{
    int len_str, len_mask;
    print_suggestion("string:");
    char *str = input_cstring_no_len(len_str);
    print_suggestion("mask:");
    char *mask = input_cstring_no_len(len_mask);
    

    bool res = solve_task(str, mask, len_mask, len_str);

    print_res(res);
    delete[] str;
    delete[] mask;

    return 0;
}

/*
12345
?2*5

YES

1233456
?2*5

NO

*/