#pragma once
#include <random>
#include <iostream>

template <class keyType>
class getNumberStrategy
{
public:
    keyType getNumberInRange(keyType, keyType);
};

template <class rangeType = size_t>
class getRandomSizeT : getNumberStrategy<rangeType>
{
public:
    rangeType getNumberInRange(rangeType beg, rangeType end)
    {
        std::random_device rd;  // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(beg, end);

        return static_cast<rangeType>(distr(gen));
    }
};

template <class keyType = size_t>
class PrimesGeneratorStrategy
{
public:
    keyType getNexPrime(keyType beg);
};

template <class keyType = size_t>
class LazyPrimesGenerator : PrimesGeneratorStrategy<keyType>
{
private:
    bool isPrime(keyType n)
    {

        if (n <= 1)
            return false;
        if (n <= 3)
            return true;

        if (n % 2 == 0 || n % 3 == 0)
            return false;

        for (keyType i = 5; i * i <= n; i = i + 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;

        return true;
    }

public:
    keyType getNexPrime(keyType beg)
    {

        if (beg <= 1)
            return 2;

        keyType prime = beg;
        bool found = false;

        while (!found)
        {
            prime++;

            if (isPrime(prime))
                found = true;
        }

        return prime;
    }
};

template <typename T>
void print(T t)
{
    std::cout << t << std::endl;
}

template <typename T, typename... Args>
void print(T t, Args... args)
{
    std::cout << t << ' ';

    print(args...);
}