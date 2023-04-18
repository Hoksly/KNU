#include <memory>
#pragma once
template <class Key>
class hashFucntion
{
public:
    virtual ~hashFucntion() = default;
    virtual size_t getHash(Key) = 0;
};

template <class Key>
class AbstractlHashingFunctionGenerator
{
public:
    virtual hashFucntion<Key> getHashFunction(size_t p, size_t m) = 0;
};
