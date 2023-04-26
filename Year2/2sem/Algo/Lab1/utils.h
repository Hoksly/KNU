#pragma once
#include <random>
#include <iostream>
#include <limits>
template <class keyType>
class getNumber
{
public:
    virtual keyType getNumberInRange(keyType, keyType) = 0;
};

template <class rangeType = size_t>
class getRandomSizeT : getNumber<rangeType>
{
public:
    rangeType getNumberInRange(rangeType beg, rangeType end) override
    {
        std::random_device rd;  // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(beg, end);

        return static_cast<rangeType>(distr(gen));
    }
};

class getRandomString
{

public:
    std::string getStringInRange(size_t beg, size_t end)
    {
        constexpr size_t kMaxChar = static_cast<char>(std::numeric_limits<char>::max());

        std::random_device rd;  // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(beg, end);

        size_t stringSize = distr(gen);

        std::string s;
        s.resize(stringSize);

        std::uniform_int_distribution<> distr2(static_cast<char>(std::numeric_limits<char>::min()), static_cast<char>(std::numeric_limits<char>::max()));

        for (size_t i = 0; i < stringSize; ++i)
        {
            s[i] = distr2(gen);
        }
        return s;
    }
};

template <class keyType = size_t>
class PrimesGenerator
{
public:
    keyType getNexPrime(keyType beg);
};

template <class keyType = size_t>
class LazyPrimesGenerator : public PrimesGenerator<keyType>
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