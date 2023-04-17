#include <memory>
#pragma once
template <class Key>
class hashFucntion
{
    size_t getHash(Key);
};

template <class Key>
class AbstractlHashingFunctionGenerator
{
    hashFucntion<Key> getHashFunction(size_t p, size_t m);
};
