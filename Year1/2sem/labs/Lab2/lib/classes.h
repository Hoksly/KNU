#pragma once

struct String
{
    int _len;
    char * mas;

    String();

    char operator[] (int i);
    int len();

};

template<class X>
struct Node
{
    X val;
    Node * next;
};

template<class X>
class Cherpak
{
    Node<X> *last = nullptr;
    
    
    public:
    
    void push(X);
    X get();
    bool is_empty();
    void push_front(X);

};

