
#include <iostream>
#include <stdlib.h>
#include <exception>
//#include "lib/exceptions.hpp"

using namespace std;


struct IndexOutOfRangeException : public std::exception
{
    const char * what () const throw ()
    {
        return "No such index in List";
    }
};



struct NoSuchElementException : public std::exception
{
    const char * what () const throw ()
    {
        return "Element is not in list";
    }
};


template<class X>
struct PART
{
    X value;
    PART<X> *next;
    PART<X> *prev;
    PART()
    {
        next = NULL;
        prev = NULL;
    }
    PART(X val)
    {
        value = val;
        next = NULL;
        prev = NULL;
    }
    
}; 


template <class X>
class List
{
    private:
    int _size = 0;
    PART<X> * FIRST = nullptr;
    PART<X> * LAST = nullptr;


    PART<X> * give_last();
    PART<X> * give_element_by_index(int);
    void chsize(int);

    void create_new_parts(int);
    int give_index_by_value(X);
    public:
    List(void)
    {}

    List(int size)
    {    
        create_new_parts(size);
       
        _size = size;
   

    }

    X& operator[] (const int);
     List<X> operator + (List<X>);
    List<X> operator= (List<X>);

    void push_back(X new_value);
    void remove(X value);

    X pop (int index);
    int size();
    void insert(int, X);

    void show();
    List<X> copy();

};

template<class X>
void List<X>::push_back(X new_value)
{
    PART<X> *ptr, *new_part;
    if (_size != 0)
        ptr = give_last();
    else
    {
        ptr = new PART<X>;
        this->FIRST = ptr;
        ptr->value = new_value;
        LAST = ptr;

        _size = 1; // If we here - size is == 0 and after appending must be 1
        return;
        
    }
   
    new_part = new PART<X>;
    new_part->value = new_value;
    ptr->next = new_part;
    new_part->prev = ptr;
    
    
    LAST = new_part;
    _size++;

}


template <class X>
PART<X>* List<X>::give_last()
{

    return this->LAST;
}

template <class X>
PART<X>* List<X>::give_element_by_index(int index)
{
    if (index > 0)
    {
        PART<X> *ptr = this->FIRST;
       
        for(register int i = 0; i < index; ++i)
        {
         
            
            if(ptr->next)
               { ptr = ptr->next;}
            else
                {return NULL;}
            
                
            

        }
        return ptr;
    }
    else if(index == 0)
    {
        return FIRST;
    }
    else if (index < 0)
    {
        PART<X> *ptr = this->LAST;
        for (register int i = -1; i > index; --i)
        {
            if(ptr->prev)
               {ptr = ptr->prev;}
            else
                {return NULL;}
        }
        return ptr;

    }
    return NULL;
}
template<class X>
int List<X>::give_index_by_value(X value)
{
    PART<X> *ptr = FIRST;
    
    for(int i; ptr; i++)
    {
        if(ptr->value == value)
            return i;
        ptr = ptr->next;
    }

    return -1;
}

template<class X>
void List<X>::remove(X value)
{
    PART<X> *ptr, *prev, *next;
    
    ptr = give_element_by_index(give_index_by_value(value));
    if (ptr)
    {
        next = ptr->next;
        prev = ptr->prev;
        if (next)
            next->prev = prev;
        if (prev)
            prev->next = next;
        
        delete ptr;

    }
    else
    {
        
        
    }
}





template<class X>
void List<X>::create_new_parts(int add_size)
{ 

    if (add_size <= 0)
        return;
   
    
    PART<X> *ptr, *new_part;        
    if(_size == 0)
    {
        PART<X> *ptr = new PART<X>;
        FIRST = ptr;
        LAST = ptr; 
        
        add_size--;
      
    }
    else
        {PART<X> *ptr = give_last();}

    ptr = FIRST; // ????????????????????? 

    for(register int i = 0; i < add_size; i++)
    {
        new_part =  new PART<X>;
        
        ptr->next = new_part;

        new_part->prev = ptr;
        
        
        ptr = new_part;

    
            
    }
    this->LAST = ptr;
    
}

template<class X>
int List<X>::size()
{
    return _size;
}

template<class X>
void List<X>::chsize(int sz)
{
   _size = sz;
}


template<class X>

void List<X>::show()
{
    PART<X> *ptr = FIRST;

    while (ptr)
    {
    
        cout << ptr->value << ' ';
        ptr = ptr->next;
    }
    cout << endl;
    


}

template<class X>
void List<X>::insert(int index, X value)
{
    PART<X> *ptr, *prev, *next;
    ptr = new PART<X>(value);

    prev = give_element_by_index(index);
    if(prev)
    {
        next = prev->next;
        if (next)
            next->prev = ptr;
        ptr->prev = prev;
        ptr->next = next;
    }
    else
    {
         throw IndexOutOfRangeException();        
    }

    return;

}

template <class X>
X List<X>::pop(int index)
{
    PART<X> *ptr, *prev, *next;

    ptr = give_element_by_index(index);
   if (ptr)
    {
        next = ptr->next;
        prev = ptr->prev;
        if (next)
            next->prev = prev;
        if (prev)
            prev->next = next;
        
        X val = ptr->value;
        delete ptr;
        return val;

    }
    else
    {
        
       throw IndexOutOfRangeException();  
    }
   
}

template<class X>
List<X> List<X>::operator=(List <X> Right)
{
    this->FIRST = Right.FIRST;
    this->LAST = Right.LAST;
    this->_size = Right._size;

    return *this;
}

template <class X>
X& List<X>::operator[] (const int index)
{
    if (index >= _size || index < -_size)
    {
        throw IndexOutOfRangeException();  
    }
    return give_element_by_index(index)->value; 
}

template<class X>
List<X> List<X>::copy()
{
    PART<X> *ptr, *mover, *prev;
    mover = this->FIRST;
    
    List<X> NewList(this->_size);
    mover = this->FIRST;
    ptr = NewList.FIRST;


    for(register int i = 0; i < this->_size; i++)
    {

        ptr->value = mover->value;
        ptr = ptr->next;
        mover = mover->next;
    }
    NewList._size = this->_size;

    
    return NewList;    

}

template <class X>
List<X> List<X>::operator+ (List<X> added)
{
    List<X> Part1, Part2;
   
    Part1 = this->copy();
    Part2 = added.copy();


    Part1.LAST->next = Part2.FIRST;
    Part2.FIRST->prev = Part1.LAST;

    
    Part1.chsize(added.size() + this->size());
    
   
    return Part1;
    
    

}

int main()
{
    List<int> a(0);
    List<int> b, c;

    for(int i = 0; i < 10; i++)
        a.push_back(i);
    
    try
    {a.pop(12);}
    catch (IndexOutOfRangeException &e)
    {   
        cout << "Exception: " << e.what() << endl; 
    }


    //a.show();
    b = a.copy();
    a[3] = 100;
    //b.show();
    
    c = a + b;
    //c[12] = 10;
    c.show();
    cout << c.size() << endl;

    
}