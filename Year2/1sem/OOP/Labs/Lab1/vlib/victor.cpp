#include "victor.hpp"
template <class T>
void victor<T>::__copy_victor(T *new_place)
{
    T *element_ptr = _base;

    for (register v_size i = 0; i < _size; ++i, element_ptr++, new_place++)
    {
        *new_place = *element_ptr;
    }
}

template <typename T>
void victor<T>::__reallocate_victor(v_size target_size)
{
    T *new_victor = new T[_size + target_size];
    this->__copy_victor(new_victor);

    _capacity += target_size;
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
        for (v_size cur_position = _size + i; cur_position > from + i; ++cur_position)
        {
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

    _size = _capacity = size;
}

template <class T>
victor<T>::victor(v_size size, T init_object) : victor(size)
{

    T *tmp = _base;
    for (long long i = 0; i < size; ++i, tmp++)
    {
        *tmp = *init_object;
    }
}

template <class T>
victor<T> &victor<T>::clear()
{
    _size = 0;
    return this;
}

template <class T>
victor<T> &victor<T>::erase(iterator position)
{
    if (position >= _size || position < 0)
        throw std::__throw_bad_function_call(); // "Postion is out of victor size"

    __move_left(position + 1, 1);

    _size--;

    return this;
}

template <class T>
iterator victor<T>::insert(const iterator &position, const T &element)
{
    if (position >= _size || position < 0)
        throw std::__throw_bad_function_call(); // "Postion is out of victor size"

    // in case we don't have enough place
    if (_size == _capacity)
        this->__reallocate_vector(_capacity * 2);

    __move_right(position, 1);
    _base[position] = element;

    _size++;

    return position;
}

template <class T>
victor<T> &victor<T>::push_back(const T &element)
{

    if (_size == _capacity)
        this->__reallocate_vector(_capacity * 2); // not a greatest formula, but let it be...

    _base[_size + 1] = element;
    _size++;
    return this;
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
T &victor<T>::operator[](v_size index)
{
    if (index > 0 && index < _size)
        return _base[index];
    throw std::out_of_range(); // "index out of victor range"
}
template <class T>
void victor<T>::print()
{
    for (v_size i = 0; i < _size; ++i)
        std::cout << _base[i] << ' ';

    std::cout << std::endl;
}
