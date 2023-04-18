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
    std::vector<std::vector<Key>> storage;
    std::vector<std::unique_ptr<hashFucntion<size_t>>> secondFucntions;
    std::unique_ptr<hashFucntion<Key>> mainHashFunction;

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
    PolynomialHashingFunctionGenerator<Key> polGen;

    linearHashingFunctionGenerator<size_t> linGen;

    mainHashFunction = polGen.getHashFunction(p, m);

    for (auto key = keysSet.begin(); key != keysSet.end(); key++)
    {
        std::string tmp = *key;

        calc[mainHashFunction->getHash(tmp)]++;
    }

    secondFucntions.resize(m);
    storage.resize(m);

    for (size_t i = 0; i < m; ++i)
    {
        storage[i].resize(calc[i] * calc[i]);

        secondFucntions[i] = linGen.getHashFunction(p, calc[i] * calc[i]);
    }
}

template <class Key, class Set, class PrimesGeneratorStrategy>
idealHashSet<Key, Set, PrimesGeneratorStrategy>::~idealHashSet()
{
}