#include <chrono>
#include <fstream>
#include "matrix.hpp"
#include "hash.hpp"
#include "algo.hpp"


inline double measureTime(size_t matrixSize,const Matrix &searchPaettern, bool findCollisions = false)
{
    Matrix *toSearchIn = new Matrix(matrixSize, matrixSize, true);

    auto begin  = std::chrono::high_resolution_clock::now();

    rabinCarpSearchAll(*toSearchIn, searchPaettern);

    auto end = std::chrono::high_resolution_clock::now();

    delete toSearchIn;

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

}

inline int measureCollisions(std::vector<std::pair<size_t, size_t>> &cords, const Matrix &orig, const Matrix &pattern)
{   

    int count = 0;
    for (std::pair<size_t, size_t> pr : cords)
    {

        size_t y = pr.first;
        size_t x = pr.second;
        
        for(size_t i = 0; i < pattern.n(); ++i)
        {
            for(size_t j = 0; j < pattern.m(); ++j)
            {
                if(orig[i+x][j+y] != pattern[i][j])
                {
                    ++count;

                   goto end; 
                }
            }
        }  

        

        end : 
        ;
        if(count)
        std::cout << orig.subMatrix(x, y, x+pattern.m()-1, y+pattern.n()-1) << std::endl;
        std::cout << pattern << std::endl;
    }


    return count;
}

inline int measureExecutionCollisions(size_t matrixSize,const Matrix &searchPaettern, int &foundCount)
{
    Matrix *toSearchIn = new Matrix(matrixSize, matrixSize, true);
    std::vector<std::pair<size_t, size_t>> cords = rabinCarpSearchAll(*toSearchIn, searchPaettern);
    int result = measureCollisions(cords, *toSearchIn, searchPaettern);


    //std::cout << *toSearchIn << std::endl;
    //std::cout << searchPaettern << std::endl;
    //std::cout << cords.size() << std::endl;

    delete toSearchIn;
    foundCount = cords.size();
    
    return result;

}

void testExecutionTime(std::string fileName = "time.txt", size_t beginFrom = 100, size_t endWhen = 12000)
{
    std::vector<std::pair<size_t, double>> Results; 
    double time;
    Matrix pattern(5, 5, true);
    std::ofstream file;
    file.open(fileName);
    if(!file.is_open())
        throw std::runtime_error("File is not open");

    for(size_t curSize = beginFrom; curSize < endWhen; ++curSize)
    {
        time = measureTime(curSize, pattern);
        std::cout << curSize << std::endl;
        file << curSize << ' ' << time / 1000 << std::endl;

    }

    
}



void  testCollisions(std::string fileName = "collisions.txt", size_t beginFrom = 10, size_t endWhen = 1200)
{
    std::vector<std::pair<size_t, double>> Results; 
    int collisions, foundCount;
    Matrix pattern(3, 3, true);
    std::ofstream file;
    file.open(fileName);
    if(!file.is_open())
        throw std::runtime_error("File is not open");

    for(size_t curSize = beginFrom; curSize < endWhen; ++curSize)
    {
        std::cout << curSize << std::endl;
        collisions = measureExecutionCollisions(curSize, pattern, foundCount);
        file << curSize << ' ' << foundCount  << ' ' << collisions << std::endl;

    }


}

double testComplexity(size_t smallSize = 3000)
{
    Matrix pattern(3, 3, true);
    double timeSmall, timeBig;
    timeSmall = measureTime(smallSize, pattern);
    size_t bigSize = smallSize * 2;
    timeBig = measureTime(bigSize, pattern);

    return timeBig / timeSmall;

}


