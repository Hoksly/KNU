#pragma once
#include "abstract-hashing.h"
#include "utils.h"
#include "polynomial-hashing.h"
#include "linear-hashing.h"

#include <vector>

template <class Key, class Set, class PrimesGeneratorStrategy>
class idealHashSet
{
private:
    std::vector<std::vector<Key>> linksStorage;
    std::vector<hashFucntion<Key>> secondFucntions;
    hashFucntion<Key> mainHashFunction;

    size_t m, p;

public:
    idealHashSet(Set keysSet, PrimesGeneratorStrategy gen);
    ~idealHashSet();
};

template <class Key, class Set, class PrimesGeneratorStrategy>
idealHashSet<Key, Set, PrimesGeneratorStrategy>::idealHashSet(Set keysSet, PrimesGeneratorStrategy gen)
{
    m = keysSet.size();
    p = gen.getNexPrime(m);
    std::vector<size_t> calc(m, 0);
    PolynomyalHashingFunctionGenerator<Key> polGen;
    mainHashFunction = polGen.getHashFunction(p, m);

    for (auto key = keysSet.begin(); key != keysSet.end(); key++)
    {
        calc[mainHashFunction(*key)]++;
    }
}

template <class Key, class Set, class PrimesGeneratorStrategy>
idealHashSet<Key, Set, PrimesGeneratorStrategy>::~idealHashSet()
{
}