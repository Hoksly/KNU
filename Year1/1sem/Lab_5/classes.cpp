#include "globals.hpp"
#include "classes.hpp"


char str_with_pos::get_ch()
{
    
    return s[pos++];
}
char str_with_pos::get_ch_nm()
{
    //cout << s[pos] << endl;
    return s[pos];
}
void str_with_pos::clear()
{
    pos = 0;
    s = "";
}

