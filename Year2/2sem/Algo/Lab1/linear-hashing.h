#pragma once
#include "abstract-hashing.h"
#include <random>

template <class Key>
class linearHashFucntion : public hashFucntion<Key>
{
    size_t a, b, m, p;

public:
    linearHashFucntion(size_t _a, size_t _b, size_t _m, size_t _p) : a(_a), b(_b), m(_m), p(_p) {}

    inline size_t getHash(Key keyValue) const override
    {
        return ((keyValue * a + b) % p) % m;
    }
};

template <class Key>
class linearHashingFunctionGenerator : public AbstractlHashingFunctionGenerator<Key>
{
    linearHashFucntion<Key> getHashFunction(size_t p, size_t m) const override
    {
        getRandomSizeT gen;

        return linearHashFucntion<Key>(gen.getNumberInRange(1, p - 1), gen.getNumberInRange(0, p - 1), m, p);
    }
};
