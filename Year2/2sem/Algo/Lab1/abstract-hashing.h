#include <memory>
#pragma once
template <class Key>
class hashFucntion
{
public:
    virtual size_t getHash(Key &) const = 0;
};

template <class Key>
class AbstractlHashingFunctionGenerator
{
public:
    virtual std::unique_ptr<hashFucntion<Key>> getHashFunction(size_t p, size_t m) const = 0;
};
