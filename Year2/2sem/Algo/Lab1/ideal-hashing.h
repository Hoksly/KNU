#pragma once
#include <memory>
#include "abstract-hashing.h"
#include "utils.h"
#include "polynomial-hashing.h"
#include "linear-hashing.h"
#define __IDEALHASH_DEBUG
#include <vector>

template <class Key, class Set, class PrimesGeneratorStrategy>
class idealHashSet
{
private:
    std::vector<std::vector<std::unique_ptr<Key>>> storage;
    std::vector<std::unique_ptr<hashFucntion<Key>>> secondFucntions;
    std::unique_ptr<hashFucntion<Key>> mainHashFunction;

    std::unique_ptr<Set> allowedElements;

    size_t m, p;

    size_t size;

public:
    /**
     *  @brief  Default constructor creates no elements.
     *  @param keysSet Set of elements that will be stored in container
     *  @param gen  A primes generator object
     */
    idealHashSet(const Set &keysSet, PrimesGeneratorStrategy gen, bool debug = false)
    {
        {
            m = keysSet.size();
            p = gen.getNexPrime(m);
            std::vector<size_t> calc(m, 0);
            PolynomialHashingFunctionGenerator<Key> polGen;

#ifdef __IDEALHASH_DEBUG
            allowedElements = std::make_unique<Set>(keysSet);
#endif

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
                if (calc[i])
                {
                    storage[i].resize(calc[i] * calc[i]);

                    secondFucntions[i] = polGen.getHashFunction(p, calc[i] * calc[i]);
                }
            }
        }
    }
    /**
     *  @brief Attempts to insert an element into the %idealHashSet.
     *  @param  __x  Element to be inserted.
     *
     *
     *  This function attempts to insert an element into the %idealHashSet.
     *  An %idealHashSet relies on unique keys and thus an element is only
     *  inserted if it is not already present in the %idealHashSet.
     *
     *  Insertion requires constant time.
     */

    void insert(Key __x)
    {
        size_t firstLevelHash, secondLevelHash;

#ifdef __IDEALHASH_DEBUG
        if (allowedElements->find(__x) == allowedElements->end())
            throw std::invalid_argument("Such element is not allowed");
#endif

        firstLevelHash = mainHashFunction->getHash(__x);
        secondLevelHash = secondFucntions[firstLevelHash]->getHash(__x);

        if (!storage[firstLevelHash][secondLevelHash])
        {
            storage[firstLevelHash][secondLevelHash] = std::make_unique<Key>(__x); // or without it ...?
        }

#ifdef __IDEALHASH_DEBUG
        else
        {
            if (*storage[firstLevelHash][secondLevelHash] == __x)
            {
                throw std::overflow_error("Two different elements in one cell");
            }
        }
#endif
    }

    bool contains(Key __x)
    {

#ifdef __IDEALHASH_DEBUG
        if (allowedElements->find(__x) == allowedElements->end())
            throw std::invalid_argument("Such element is not allowed");
#endif
        size_t firstLevelHash, secondLevelHash;

        firstLevelHash = mainHashFunction->getHash(__x);
        secondLevelHash = secondFucntions[firstLevelHash]->getHash(__x);

        return (bool)storage[firstLevelHash][secondLevelHash];
    }

    /**
     *  @brief Erases an element from an %idealHashSet.
     *  @param  __x  Element to be erased.
     *
     *  This function erases an element,
     *  from an %idealHashSet.  Note that this function only erases the
     *  element, and that if the element is itself a pointer, the pointed-to
     *  memory is not touched in any way. Managing the pointer is the user's
     *  responsibility.
     *
     * Erasion requires constant time.
     */
    void erase(Key __x)
    {

#ifdef __IDEALHASH_DEBUG
        if (allowedElements->find(__x) == allowedElements->end())
            throw std::invalid_argument("Such element is not allowed");
#endif
        size_t firstLevelHash, secondLevelHash;

        firstLevelHash = mainHashFunction->getHash(__x);
        secondLevelHash = secondFucntions[firstLevelHash]->getHash(__x);

        if (storage[firstLevelHash][secondLevelHash])
        {
            storage[firstLevelHash][secondLevelHash] = std::unique_ptr<Key>();
        }
    }

    ~idealHashSet() = default;
};
