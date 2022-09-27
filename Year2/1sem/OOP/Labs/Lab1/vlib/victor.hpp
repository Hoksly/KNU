
#include <iostream>
#include <string.h>
#include "doctest.h"

#ifndef VICTOR_H
#define VICTOR_H

typedef int iterator; // maybe i will write it later
typedef long long v_size;

template <class T>
class victor
{
private:
    int _size = 0;
    int _capacity = 0;

    T *_base = nullptr;

    T __get_element(const iterator index);
    void __copy_victor(T *new_place);
    void __reallocate_victor(v_size target_size);
    void __move_left(v_size from, v_size n_of_positions);
    void __move_right(v_size from, v_size n_of_positions);

public:
    victor(v_size size);
    victor(v_size size, T init_item);

    inline bool size() { return _size; }

    victor &clear();
    victor &erase(const iterator position);
    victor &erase(const iterator first, const iterator last); // removes elements in range [first, last]

    iterator insert(const iterator &position, const T &element);
    victor &push_back(const T &);
    T pop_back();

    victor &resize(const iterator target_size);
    victor &reserve(const iterator additional_space);
    victor &shrink_to_fit();

    victor copy();

    void swap(const iterator first, const iterator second);
    v_size search(const T &value);

    T &operator[](v_size index);

    // debuging
    void print();
};

#endif
