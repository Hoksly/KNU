
#include <iostream>
#include <stdlib.h>
#include <exception>

using namespace std;


struct IndexOutOfRangeException : public std::exception
{
    const char * what () const throw ()
    {
        return "List index is out of range";
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

    void push_back(X new_value);
    void remove(X value);

    X pop (int index);
    int size();
    void insert(int, X);

    void show();

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
        //cout << "HERE" << endl;
        for(register int i = 0; i < index; i++)
        {
            //cout << "HERE" << index << ' ' << i << endl;
            
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
        
        cout << "No such element for removing" << endl;
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
        cout << "Insert error with index " << index << "  No such element" << endl;
        
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

template <class X>
X& List<X>::operator[] (const int index)
{
    if (index >= _size || index < -_size)
    {
        throw IndexOutOfRangeException();  
    }
}

int main()
{
    List<int> a(0);
    

    for(int i = 0; i < 10; i++)
        a.push_back(i);
    
    try
    {a.pop(12);}
    catch (IndexOutOfRangeException &e)
    {
        cout << "Exception: " << e.what() << endl; 
    }
    a.show();
    
    


    
}