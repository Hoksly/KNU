#include <vector>
#include "matrix.hpp"
#include "data.hpp"
#include <map>
#include <hash_map>
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


inline hexT getPow(hexT base_x, hexT base_y, std::map<std::pair<size_t, size_t>, hexT> &from)
{
   
        return from[std::make_pair(base_x, base_y)];
        //return pow(BASEX, base_x) * pow(BASEY, base_y);
}

inline hexT getPow(hexT base_y, std::map<size_t, hexT> &from)
{
   
        return from[base_y];
        //return pow(BASEY, base_y);
}

inline void recalculateHex(size_t newHexBeginY, size_t newHexBeginX, const Matrix &Orig, hexT &subMatrixHex, const size_t &subN, const size_t &subM, 
std::map<std::pair<size_t, size_t>, hexT> &powMapTwoBase, std::map<size_t, hexT> &powMapOneBase )
{
    // moving hex one step right
    // removing left hex
   
    for (size_t i = 0; i < subN; ++i)
    {
        subMatrixHex -=  Orig[i+newHexBeginY][newHexBeginX-1] * getPow(subM - 1, subN - 1 - i, powMapTwoBase);
        subMatrixHex %= SIMPLEONE;
    }
    subMatrixHex *= BASEX;
    subMatrixHex %= SIMPLEONE;
    for (size_t i = 0; i < subN; ++i)
    {
        subMatrixHex +=  Orig[i+newHexBeginY][newHexBeginX - 1 + subM] * getPow(subN - i-1, powMapOneBase); // pow(BASEX, 0) == 1, so not written 
        subMatrixHex %= SIMPLEONE;
    }
   
    
}


inline hexT polynomialHex(const Matrix &A,   std::map<std::pair<size_t, size_t>, hexT> &powMap, hexT baseX = BASEX, hexT baseY = BASEY, hexT simpleOne = SIMPLEONE)
{
    size_t m, n;

    m = A.m();
    n = A.n();
    hexT totalHex = 0;

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            
            totalHex += A[i][j] * getPow(m-j-1, n-i-1, powMap);
            totalHex %= simpleOne;

        }
    
    }
    
    // add something?
    
    return totalHex;
}
inline hexT polynomialHexSubMatrix(const Matrix &target, size_t beginY, size_t beginX, size_t n, size_t m,  std::map<std::pair<size_t, size_t>, hexT> &powMap, 
                            hexT baseX = BASEX, hexT baseY = BASEY, 
                            hexT simpleOne = SIMPLEONE)
{

    hexT totalHex = 0;

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            
            totalHex += target[i+beginY][j+beginX] * getPow(m-j-1, n-i-1, powMap);
            totalHex %= simpleOne;
            
        }
    
    }
    
    // add something?

    return totalHex;
}


inline void initMap(std::map<std::pair<size_t, size_t>, hexT> &exactMap, size_t from, size_t end)
{
    
    for(size_t i = from; i < end; ++i)
    {
        for(size_t j = from; j < end; ++j)
        {
            exactMap.insert({std::make_pair(i, j), pow(BASEX, i) * pow(BASEY, j)});
           
            
        }
    }
}

inline void initMap(std::map<size_t, hexT> &exactMap, size_t from, size_t end)
{
    
    for(size_t i = from; i < end; ++i)
    {
   
            exactMap.insert({i, pow(BASEY, i) });
           
            
        
    }
}



std::vector<std::pair<size_t, size_t>> rabinCarpSearchAll(Matrix target, Matrix example)
{
    std::map<std::pair<size_t, size_t>, hexT> powMapTwoArgs;
    std::map<size_t, hexT> powMapOneArg;

    initMap(powMapTwoArgs, 0, std::max(example.m(), example.n()));
    initMap(powMapOneArg, 0, std::max(example.m(), example.n()));
    
    
    

    std::vector<std::pair<size_t, size_t>> allAnswers;
    if(example.m() > target.m() || example.n() > target.n())
        return allAnswers;

    hexT exampleHex = polynomialHex(example, powMapTwoArgs);
    hexT subMatrixHex = 0;
    
    for (size_t i = 0, j = 0; i < target.n() - example.n() + 1; ++i)
    {
        j = 0;
        subMatrixHex = polynomialHexSubMatrix(target, i, 0, example.n(), example.m(), powMapTwoArgs);
        
        do
        { 
             
            if(subMatrixHex == exampleHex)
                allAnswers.push_back(std::make_pair(i, j));
            ++j;

            if(j < target.m() - example.m() + 1)
                recalculateHex(i, j, target, subMatrixHex, example.n(), example.m(), powMapTwoArgs, powMapOneArg);
            else
                break;

        } while (j < target.m() - example.m() + 1);
        
    }

    return allAnswers;
}


#endif