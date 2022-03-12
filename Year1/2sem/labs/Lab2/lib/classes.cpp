#include "classes.h"

char String::operator[] (int i)
{
    return mas[i];
}

int String::len()
{
    return _len;
}

template<class X>
bool Cherpak<X>::is_empty()
{
    return (bool) last;

}
String::String()
{

}

template<class X>
void Cherpak<X>::push(X val)
{
    Node<X> *lst = new Node<X>;
    lst->val = val;
    
    lst->next = last->next;
    last->next = lst;
    last = lst;
}

template<class X>
X Cherpak<X>::get()
{
    X ret;
    if (!last)
    {//trow exception
    }

    if(last->next == last)
    {
        ret = last->val;
        last = nullptr;
        return ret;
    }

    Node<X> *first;
    X val = last->next->val;
    first = last->next;
    
    last->next = first->next;
    
    delete first;

    return val;
}



template<class X>
void Cherpak<X>::push_front(X val)
{
    Node<X> *frst = new Node<X>;
    frst->val = val;
    
    frst->next = last->next;
    last->next = frst;
}






