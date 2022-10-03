
#include <iostream>
#include <string.h>
#include "universalsort.hpp"
#include "def.hpp"

#ifndef VICTOR_H
#define VICTOR_H

template <class T>
class victor
{
private:
    int _size = 0;
    int _capacity = 0;

    T *_base = nullptr;

    T __get_element(const _iterator index);
    void __copy_victor(T *new_place);
    void __move_left(v_size from, v_size n_of_positions);
    void __move_right(v_size from, v_size n_of_positions);
    void __reallocate_victor(v_size target_size);

public:
    victor(v_size size);
    victor(v_size size, T init_item);
    victor();

    ~victor();

    inline v_size size() { return _size; }
    inline v_size capacity() { return _capacity; }

    victor &clear();
    victor &erase(const _iterator position);
    victor &erase(const _iterator first, const _iterator last); // removes elements in range [first, last]

    _iterator insert(const _iterator &position, const T &element);
    victor &push_back(const T &);
    T pop_back();

    victor &resize(const _iterator target_size);
    victor &reserve(const v_size additional_space);
    victor &shrink_to_fit();

    victor copy();

    void swap(const _iterator first, const _iterator second);
    v_size search(const T &value);

    T &operator[](v_size index);
    victor operator=(const victor &other_victor);

    // output
    void print();
    std::string str();
    template <typename C>
    friend std::ostream &operator<<(std::ostream &out, const victor<C> &v);

    // friends from std

    // sotring
    void sort(); // implementing regular quick sort

    void sort(void (*sort_function)(victor<T> &container));
};

template <class T>
void victor<T>::__copy_victor(T *new_place)
{
    T *element_ptr = _base;

    for (v_size i = 0; i < _size; ++i, element_ptr++, new_place++)
    {
        *new_place = *element_ptr;
    }
}

template <typename T>
void victor<T>::__reallocate_victor(v_size additional_size)
{
    T *new_victor = new T[_capacity + additional_size];
    this->__copy_victor(new_victor);
    delete _base;

    _base = new_victor;

    _capacity += additional_size;
}

template <class T>
void victor<T>::__move_left(v_size position, v_size n_of_positions)
{
    // ACHTUNG
    // This will overwrite element with positions [position-n_of_positions, position-1]

    v_size tmp_var;
    for (v_size i = 0; i < n_of_positions; ++i)
    {
        for (v_size cur_position = position; cur_position < _size - i; cur_position++)
        {
            _base[cur_position - 1] = _base[cur_position];
        }
    }
}
template <class T>
void victor<T>::__move_right(v_size from, v_size n_of_positions)
{
    for (v_size i = 0; i < n_of_positions; ++i)
    {
        for (v_size cur_position = _size + i; cur_position > from + i; --cur_position)
        {
            std::cout << cur_position << std::endl;
            _base[cur_position] = _base[cur_position - 1];
        }
    }
}

template <class T>
victor<T>::victor(v_size size)
{
    if (size < 0)
    {
        throw std::bad_alloc(); // "size can not be less than zero"
    }

    _base = new T[size];

    _size = size;
    _capacity = size;
}

template <class T>
victor<T>::victor(v_size size, T init_object) : victor(size)
{

    T *tmp = _base;
    for (long long i = 0; i < size; ++i, tmp++)
    {
        *tmp = init_object;
    }
}

template <class T>
victor<T>::~victor()
{
    delete _base;
}

template <class T>
victor<T>::victor()
{
}
template <class T>
victor<T> &victor<T>::clear()
{
    _size = 0;
    return *this;
}

template <class T>
victor<T> &victor<T>::erase(const _iterator position)
{
    if (position >= _size || position < 0)
        throw std::__throw_bad_function_call(); // "Postion is out of victor size"

    __move_left(position + 1, 1);

    _size--;

    return *this;
}

template <class T>
_iterator victor<T>::insert(const _iterator &position, const T &element)
{
    if (position > _size || position < 0)
        throw std::__throw_bad_function_call; // "Postion is out of victor size"
    if (position == _size)
    {
        this->push_back(element);
        return position;
    }
    // in case we don't have enough place
    if (_size == _capacity)
        this->__reallocate_victor(_capacity + 1);

    __move_right(position, 1);
    _base[position] = element;

    _size++;

    return position;
}

template <class T>
victor<T> &victor<T>::push_back(const T &element)
{

    if (_size == _capacity)
        this->__reallocate_victor(_capacity + 1); // not a greatest formula, but let it be...

    _base[_size] = element; // index of last element is size-1

    _size++;
    return *this;
}

template <class T>
T victor<T>::pop_back()
{
    if (_size > 0)
    {
        T poped_element = _base[size];
        _size--;
    }
    else
    {
        throw std::out_of_range(); //"Can't pop empty victor"
    }
}

template <class T>
victor<T> &victor<T>::reserve(const v_size additional_space)
{
    this->__reallocate_victor(additional_space);
    return *this;
}

template <class T>
victor<T> &victor<T>::shrink_to_fit()
{
    if (_size != _capacity)
    {
        T new_victor = new T[_size];
        this->__copy_victor(new_victor);
        delete _base;
        _base = new_victor;

        _capacity = _size;
    }
}

template <class T>
T &victor<T>::operator[](v_size index)
{
    if (index > -1 && index < _size)
        return _base[index];

    throw std::out_of_range("Index is out of victor range"); // "index out of victor range"
}

template <class T>
void victor<T>::print()
{

    for (v_size i = 0; i < _size; ++i)
        std::cout << _base[i] << ' ';

    std::cout << std::endl;
}

template <class T>
std::string victor<T>::str()
{
    std::string s;
    // in case it can't convert objects to string it will thrvictor<T>::vicow an error ?

    for (v_size i = 0; i < _size; ++i)
        s += to_string(_base[i]) + ' ';

    return s;
}
template <class Y>
std::ostream &operator<<(std::ostream &os, const victor<Y> &v)
{

    for (v_size i = 0; i < v._size; ++i)
        os << v._base[i] << ' ';

    return os;
}

template <typename T>
void victor<T>::sort()
{
    quick_sort(*this, 0, _size - 1);
}

template <typename T>
void victor<T>::sort(void (*sort_function)(victor<T> &container))
{
    sort_function(*this);
}
#endif
