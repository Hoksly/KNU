#pragma once
#include "abstract-hashing.h"
#include <random>
#include "utils.h"

template <class Key>
class polynomialHashFunction : public hashFucntion<Key>
{
private:
    size_t b, p, m;

public:
    polynomialHashFunction(size_t _b, size_t _p, size_t _m) : b(_b), p(_p), m(_m) {}
    size_t getHash(Key &keyValue) const override
    {
        size_t hashValue = static_cast<size_t>(0);

        for (const auto &element : keyValue)
        {
            hashValue *= b;
            hashValue %= p;
            hashValue += static_cast<size_t>(element);
            hashValue %= p;
        }

        return hashValue % m;
    }
};

template <class Key>
class PolynomialHashingFunctionGenerator : public AbstractlHashingFunctionGenerator<Key>
{

public:
    PolynomialHashingFunctionGenerator() = default;

    std::unique_ptr<hashFucntion<Key>>
    getHashFunction(size_t p, size_t m) const override
    {
        std::random_device rd;  // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::hash<size_t> h;
        size_t seed = rd();
        size_t b = h(seed ^ reinterpret_cast<size_t>(&m));

        return std::make_unique<polynomialHashFunction<Key>>(polynomialHashFunction<Key>(b, p, m));
    }
};
