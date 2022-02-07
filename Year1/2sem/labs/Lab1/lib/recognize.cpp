#include "recognize.hpp"
#include<iostream>
using namespace std;
void clear_spaces_and_lines(char **ch)
{
    while (**ch == ' ' || **ch == '\n')
    {
        (*ch)++;
    }
    
}

bool is_command(char *str)
{
    while(*str != '\n' && *str != '\0')
    {
        if(*str == '=')
            return true;
    }
    return false;

}

void clear_spaces(char **ch)
{
    while (**ch == ' ')
    {
        (*ch)++;
    }
    

}

bool is_operator(char *str)
{
    return (*str == '-' && *(str+1) == '>');
}

bool is_symbol(char *str, char target)
{
    return *str == target;
}

char extract_symbol(char **ch)
{
    clear_spaces(ch);
   
    char c = **ch;
    clear_spaces(ch);
    if(*(++(*ch)) == ',')
        (*ch)++;

    return c;
}

int extract_mas(char **ch, char * mas)
{
    while(**ch != '}' && **ch != '\0')
    {
     
        clear_spaces(ch);
        char c = extract_symbol(ch);
    
        *mas = c;
        mas++;
        
        
    }

    *mas = '\0';
    std::sort(mas, mas+strlen(mas));
    if(**ch != '\0')
        {(*ch)++; return 0;}
    
    return 1;
}

int move_to(char **ch, char symbol)
{
    while (**ch != symbol && **ch != '\0')
    {
        (*ch)++;
    }
    if(**ch == symbol)
        return 0;
    return 1;
    
}

int extract_tuple(char **ch, char *tuple)
{
    move_to(ch, '{');
    (*ch)++;
    return extract_mas(ch, tuple);
}

int extract_alphabet(char **ch, char * alp)
{
    move_to(ch, '{');
    (*ch)++;
    return extract_mas(ch, alp);
}

int one_command(char **ch,  std::vector<command> &V, int n)
{
    std::string s1 = "", s2 = "";
    bool is_end = false;
    clear_spaces(ch);
  
    while(isprint(**ch))
    {   
        //cout << **ch << endl;
        if(**ch == ' ')
        {
            if((*((*ch) + 1)) == '-' && (*((*ch) + 2)) == '>')
        {
            *ch += 3;
            if(**ch == '.')
            {(*ch)++ ; is_end = true;}
            break;
        }
            
        }
        if(**ch == '-' && (*((*ch) + 1)) == '>')
        {
            *ch += 2;
            if(**ch == '.')
            {(*ch)++ ; is_end = true;}
            break;
        }
        s1 += **ch;
        (*ch)++;

    }
    //cout << **ch << endl;
    clear_spaces(ch);
    while (isprint(**ch))
    {
       
        s2 += **ch;
        (*ch)++;
    }

    command cm(s1, s2, n, is_end);

    V.push_back(cm);


    clear_spaces_and_lines(ch);


    return (int) (**ch == '\0');
}

int extract(char **ch, char *alphabet, char *tuple, vector<command> &V)
{
/*
T = {} // Tuple to work with
A = {} //Alphabet to input

...
//commands
...

*/
    clear_spaces_and_lines(ch);

    for(int i = 0; i < 2; i++)
    {
        
        clear_spaces_and_lines(ch);
        if(**ch == 'T')
            extract_tuple(ch, tuple);
        else if(**ch == 'A')
            extract_alphabet(ch, alphabet);
    }

    clear_spaces_and_lines(ch);
    int n = 0;
    while(!one_command(ch, V, n))
    {n++;}

    return 0;
}
