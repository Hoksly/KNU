#include <vector>
#include "matrix.hpp"
#include "data.hpp"
#include <cmath>
#include <stdlib.h>



std::pair<size_t, size_t> lineSearch(Matrix Target, Matrix Linear)
{
    assert (Linear.n() != 1);
}


void recalculateHex(size_t newHexBeginY, size_t newHexBeginX, const Matrix &Orig, hexT &subMatrixHex, const size_t &subN, const size_t &subM)
{
    // moving hex one step right
    // removing left hex
    std::cout << subMatrixHex << std::endl;
    for (size_t i = 0; i < subN; ++i)
    {
        subMatrixHex -=  Orig[i+newHexBeginY][newHexBeginX-1] * pow(BASEY, subN-1-i) * pow(BASEX, subM-1);
        subMatrixHex %= SIMPLEONE;
    }
    subMatrixHex *= BASEX;
    subMatrixHex %= SIMPLEONE;
    for (size_t i = 0; i < subN; ++i)
    {
        subMatrixHex +=  Orig[i+newHexBeginY][newHexBeginX - 1 + subM] * pow(BASEY, subN - i-1); // pow(BASEX, 0) == 1, so not written 
        subMatrixHex %= SIMPLEONE;
    }
    
}


hexT polynomialHex(const Matrix &A, hexT baseX = BASEX, hexT baseY = BASEY, hexT simpleOne = SIMPLEONE)
{
    size_t m, n;

    m = A.m();
    n = A.n();
    hexT totalHex = 0;

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            
            totalHex += A[i][j] * pow(baseY, n-i-1) * pow(baseX, m-j-1);
            totalHex %= simpleOne;
        }
    
    }
    
    // add something?

    return totalHex;
}
hexT polynomialHexSubMatrix(const Matrix &target, size_t beginY, size_t beginX, size_t n, size_t m, hexT baseX = BASEX, hexT baseY = BASEY, hexT simpleOne = SIMPLEONE)
{

    hexT totalHex = 0;

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            
            totalHex += target[i+beginY][j+beginX] * pow(baseY, n-i-1) * pow(baseX, m-j-1);
            totalHex %= simpleOne;
        }
    
    }
    
    // add something?

    return totalHex;
}

std::pair<size_t, size_t> rabinCarpSearchOne(Matrix Target, Matrix example)
{

}

std::vector<std::pair<size_t, size_t>> rabinCarpSearchAll(Matrix target, Matrix example)
{
    std::vector<std::pair<size_t, size_t>> allAnswers;
    if(example.m() > target.m() || example.n() > target.n())
        return allAnswers;

    hexT exampleHex = polynomialHex(example);
    hexT subMatrixHex = 0;
    
    for (size_t i = 0, j = 0; i < target.n() - example.n() + 1; ++i)
    {
        j = 0;
        subMatrixHex = polynomialHexSubMatrix(target, i, 0, example.n(), example.m());
        std::cout << i << std::endl;
        do
        {   
            if(subMatrixHex == exampleHex)
                allAnswers.push_back(std::make_pair(i, j));
            ++j;

            if(j < target.m() - example.n() + 1)
                recalculateHex(i, j, target, subMatrixHex, example.n(), example.m());
            else
                break;

        } while (j < target.m() - example.n() + 1);
        
    }

    return allAnswers;
}