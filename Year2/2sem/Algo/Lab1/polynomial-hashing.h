#pragma once
#include "abstract-hashing.h"
#include <random>
#include "utils.h"

template <class Key>
class polynomialHashFucntion : hashFucntion<Key>
{
private:
    size_t b, p, m;

public:
    polynomialHashFucntion(size_t _b, size_t _p, size_t _m) : b(_b), p(_p), m(_m) {}
    size_t getHash(Key);
};

template <class Key>
size_t polynomialHashFucntion<Key>::getHash(Key keyValue)
{
    size_t hashValue = static_cast<size_t>(0);

    for (auto element = keyValue.begin(); element != keyValue.end(); element++)
    {
        hashValue *= b;
        hashValue %= p;
        hashValue += static_cast<size_t>(*element);
        hashValue %= p;
    }

    return hashValue % m;
}

template <class Key>
class PolynomyalHashingFunctionGenerator : AbstractlHashingFunctionGenerator<Key>
{
public:
    polynomialHashFucntion<Key> getHashFunction(size_t p, size_t m);
};
template <class Key>
polynomialHashFucntion<Key> PolynomyalHashingFunctionGenerator<Key>::getHashFunction(size_t p, size_t m)
{
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, p - 1);

    return polynomialHashFucntion<Key>(static_cast<size_t>(distr(gen)), p, m);
}
