#include <vector>
#include "matrix.hpp"
#include "data.hpp"
#include <vector>
#include <stdlib.h>

#ifndef _RABIN_CARP_SEARCH_HPP
#define _RABIN_CARP_SEARCH_HPP

inline hexT pow(hexT base, hexT x, hexT simple = SIMPLEONE)
{
    if(! x)
        return 1;

    if(x % 2)
        return base * pow(base, x-1) % simple;
    return pow(base*2, x/2);
}


inline hexT getPow(hexT base_x, hexT base_y, std::vector<std::vector<hexT>> &from)
{
   
        return from[base_x][base_y];
        //return pow(BASEX, base_x) * pow(BASEY, base_y);
}

inline hexT getPow(hexT base_y, std::vector<hexT> &from)
{
   
        return from[base_y];
        //return pow(BASEY, base_y);
}

inline void recalculateHex(size_t newHexBeginY, size_t newHexBeginX, const Matrix &Orig, hexT &subMatrixHex, const size_t &subN, const size_t &subM, 
std::vector<std::vector<hexT>> &vectorTwoBases, std::vector<hexT> &vectorOneBase )
{
    // moving hex one step right
    // removing left hex
   
    for (size_t i = 0; i < subN; ++i)
    {
        subMatrixHex -=  Orig[i+newHexBeginY][newHexBeginX-1] * getPow(subM - 1, subN - 1 - i, vectorTwoBases);
        subMatrixHex %= SIMPLEONE;
    }
    subMatrixHex *= BASEX;
    subMatrixHex %= SIMPLEONE;
    for (size_t i = 0; i < subN; ++i)
    {
        subMatrixHex +=  Orig[i+newHexBeginY][newHexBeginX - 1 + subM] * getPow(subN - i-1, vectorOneBase); // pow(BASEX, 0) == 1, so not written 
        subMatrixHex %= SIMPLEONE;
    }
   
    
}


inline hexT polynomialHex(const Matrix &A,   std::vector<std::vector<hexT>> &powVector, hexT baseX = BASEX, hexT baseY = BASEY, hexT simpleOne = SIMPLEONE)
{
    size_t m, n;

    m = A.m();
    n = A.n();
    hexT totalHex = 0;

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            
            totalHex += A[i][j] * getPow(m-j-1, n-i-1, powVector);
            totalHex %= simpleOne;

        }
    
    }
    
    // add something?
    
    return totalHex;
}
inline hexT polynomialHexSubMatrix(const Matrix &target, size_t beginY, size_t beginX, size_t n, size_t m,  std::vector<std::vector<hexT>> &powVector, 
                            hexT baseX = BASEX, hexT baseY = BASEY, 
                            hexT simpleOne = SIMPLEONE)
{

    hexT totalHex = 0;

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            
            totalHex += target[i+beginY][j+beginX] * getPow(m-j-1, n-i-1, powVector);
            totalHex %= simpleOne;
            
        }
    
    }
    
    // add something?

    return totalHex;
}


inline void initVector(std::vector<std::vector<hexT>> &exactVector, size_t from, size_t end)
{
    
    for(size_t i = from; i < end; ++i)
    {
        std::vector<hexT> newV;
        exactVector.push_back(newV);
        for(size_t j = from; j < end; ++j)
        {
            exactVector[i].push_back(pow(BASEX, i) * pow(BASEY, j));
           
            
        }
    }
}

inline void initVector( std::vector<hexT> &exactVector, size_t from, size_t end)
{
    
    for(size_t i = from; i < end; ++i)
    {
        
            exactVector.push_back(pow(BASEY, i));
           
            
        
    }
}



std::vector<std::pair<size_t, size_t>> rabinCarpSearchAll(Matrix target, Matrix example)
{
    std::vector<std::vector<hexT>> powVectorTwoArgs;
    std::vector<hexT> powVectorOneArg;

    initVector(powVectorTwoArgs, 0, std::max(example.m(), example.n()));
    initVector(powVectorOneArg, 0, std::max(example.m(), example.n()));
    
    
    

    std::vector<std::pair<size_t, size_t>> allAnswers;
    if(example.m() > target.m() || example.n() > target.n())
        return allAnswers;

    hexT exampleHex = polynomialHex(example, powVectorTwoArgs);
    hexT subMatrixHex = 0;
    
    for (size_t i = 0, j = 0; i < target.n() - example.n() + 1; ++i)
    {
        j = 0;
        subMatrixHex = polynomialHexSubMatrix(target, i, 0, example.n(), example.m(), powVectorTwoArgs);
        
        do
        { 
             
            if(subMatrixHex == exampleHex)
                allAnswers.push_back(std::make_pair(i, j));
            ++j;

            if(j < target.m() - example.m() + 1)
                recalculateHex(i, j, target, subMatrixHex, example.n(), example.m(), powVectorTwoArgs, powVectorOneArg);
            else
                break;

        } while (j < target.m() - example.m() + 1);
        
    }

    return allAnswers;
}


#endif