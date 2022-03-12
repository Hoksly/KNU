#include "classes.hpp"

command::command(std::string s1, std::string s2, int num,  bool c_end)
{
    first = s1;
    second = s2;
    is_end = c_end;
    n = num;
    
}

MarkovPtr MarkovList::GiveLast()
{
    MarkovPtr ptr = FIRST;

    while (ptr->next)
        ptr = ptr->next;
    return ptr;
}

void MarkovList::CreateNewParts(int add_size)
{
    if (add_size <= 0)
        return;
   
    
    MarkovPtr ptr, new_part;        
    if(_size == 0)
    {
        ptr = new MarkovPart;
        FIRST = ptr;
        
        add_size--;
      
    }
    else
        {ptr = GiveLast();}

    ptr = FIRST; // ????????????????????? 

    for(register int i = 0; i < add_size; i++)
    {
        new_part =  new MarkovPart;
        
        ptr->next = new_part;
        
        
        ptr = new_part;

    
            
    }
    
    

}

MarkovList::MarkovList(char * s)
{

    CreateNewParts(strlen(s));
    MarkovPtr ptr = FIRST;

    while(ptr->next)
    {
        ptr->val = *s;
        ptr = ptr->next;
        s ++;
    }

}   
MarkovList::MarkovList(std::string s)
{

    int sz = s.size();
    CreateNewParts(sz);
    MarkovPtr ptr = FIRST;

    for(register int i = 0; i < sz; ++i)
    {
        ptr->val = s[i];
        ptr = ptr->next;
        
    }

}   

bool MarkovList::IsIt(MarkovPtr cur, std::string s, int pos)
{
    if(pos == s.size())
        return true;
    
    if (cur == nullptr)
        return false;

    if (cur->val == s[pos])
        return IsIt(cur->next, s, pos+1);
    
    return false;
}

MarkovPtr MarkovList::Search(MarkovPtr ptr, std::string what)
{
    //Here ptr is begigning

    int sz = what.size();
    while (ptr)
    {
        if(IsIt(ptr, what, 0))
            return ptr;
        ptr = ptr->next;
    }

    return nullptr;
    
}

MarkovPtr MarkovList::MoveTo(MarkovPtr cur, int sz)
{
    while(sz)
    {
        if(!cur->next)
            return nullptr;
        
        --sz;
        cur = cur->next;
    }

    return cur;
    
}
void MarkovList::AddParts(MarkovPtr beg, int sz)
{
    if (sz <= 0)
        return;

    MarkovPtr cur, end;
    end = beg->next;
    
    for(register int i = 0; i < sz; ++i)
    {
        cur = new MarkovPart;
        beg->next = cur;
        beg = cur;
    }

    beg->next = end;
}

void MarkovList::DeleteParts(MarkovPtr beg, int sz)
{
    //Deltes part starting from beg (beg not included)
    MarkovPtr ptr;
    ptr = beg->next;
    for(register int i = 0; i < sz; ++i)
    {
        if (!beg->next)
            {//Error
            }

        beg->next = ptr->next;
        delete ptr;
        ptr = beg->next;

    }

    
}

void MarkovList::ReplaceValue(MarkovPtr ptr, std::string s, int i = 0)
{
    if(s.size() == i)
        return;
    if(!ptr);
        //Error
    ptr->val = s[i];
    ReplaceValue(ptr->next, s, i+1);

}
void MarkovList::Replace(MarkovPtr ptr,std::string what, std::string to)
{
    int diff = what.size() - to.size();
    if(diff > 0)
    {
        MarkovPtr end = MoveTo(ptr, to.size()-1);
        DeleteParts(end, diff);
    }
    else
    {
        MarkovPtr end = MoveTo(ptr, what.size()-1);
        AddParts(end, abs(diff));

    }
    ReplaceValue(ptr, to);
    _size += (to.size() - what.size());
}

void MarkovList::show()
{
    MarkovPtr ptr = FIRST;
    while (ptr)
    {
        std::cout << ptr->val;
        ptr = ptr->next;
    }
    std::cout << '\n';

}

std::string MarkovList::data()
{
    std::string ret;
    MarkovPtr ptr = FIRST;
    while (ptr)
    {
        ret += ptr->val;
        ptr = ptr->next;
    }

    return ret;
}

int MarkovList::replace(std::string what, std::string to)
{
    int i = 0;
    MarkovPtr ptr = FIRST;
    while((ptr = Search(ptr, what)))
    {
        ++i;
        Replace(ptr, what, to);

    }

    return i;

}

char * MarkovList::data_char()
{
    char * out = new char[_size];

    MarkovPtr ptr = FIRST;
    for(int i = 0; i < _size ; i++)
    {
        if (!ptr)
            {   
                std::cout << "Error in returning data with char" << std::endl;
                break;
            }
        out[i] = ptr->val;
        ptr = ptr->next;
    }
    return out;

}