#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>


typedef char symb;
#ifndef _MATRIX_HPP
#define _MATRIX_HPP


class Matrix
{
    size_t _n = -1;
    size_t _m = -1;

    std::vector<std::vector<symb>> matrix;
    
    public:

    Matrix(size_t n, size_t m = 0, bool randInit = false, std::pair<symb, symb> randRange = std::make_pair(60, 90));
    Matrix(std::string filename);

    inline size_t m() const {return _m;}
    inline size_t n() const {return _n;}

    void toFile(std::string filename) const;

    inline std::vector<symb> operator[] (size_t i) const {assert (i < _n); return matrix[i];}

    ~Matrix() = default;

    std::string toStr() const;

    Matrix subMatrix(size_t x0, size_t y0, size_t x1, size_t y1) const;
    
    friend
    std::ostream& operator<< (std::ostream &out, const Matrix & outMatrix);

};



Matrix::Matrix(size_t n_sz, size_t m_sz, bool randInit, std::pair<symb, symb> randRange) 
{
    if (n_sz < 1 or m_sz < 1)
    {
        throw std::bad_array_new_length();
    }    

    _n = n_sz;
    _m = (!m_sz)? _n : m_sz;

    

    for (size_t i = 0; i < _n; ++i)
    {
        std::vector<symb> toBePushed(_m);
        matrix.push_back(toBePushed);
    }

    if (randInit)
    {
        srand(time(NULL));
        
        for (size_t i = 0; i < _n; ++i)
        {
            for (size_t j = 0; j < _m; ++j)
            {
                matrix[i][j] = (symb) (rand() % (randRange.second - randRange.first)  + randRange.first); // here is hardcode, but let it be...
            }
        }
    }
    
}

Matrix::Matrix(std::string fileName)
{
    std::ifstream file;
    file.open(fileName);
    if (not file.is_open())
        return;
    
    
    file >> _n >> _m;   

    
    for (size_t i = 0; i < _n; ++i)
    {
        std::vector<symb> toBePushed(_m);
        matrix.push_back(toBePushed);
    }

        for (size_t i = 0; i < _n; ++i )
    {
        for(size_t j = 0; j < _m; ++j)
        {
            file >> matrix[i][j];
        }
    }

    

    
}


std::ostream& operator<< (std::ostream &out, const Matrix & outMatrix)
{

    out << outMatrix._n << ' ' << outMatrix._m << std::endl;
    for (size_t i = 0; i <outMatrix._n; ++i)
    {
        for (size_t j = 0; j < outMatrix._m; ++j)
        {
            out << outMatrix.matrix[i][j] << " ";
        }
        out << "\n";
    }

    return out;
}


std::string Matrix::toStr() const
{


    std::stringstream out;

    out << *this;

    return out.str();

}

void Matrix::toFile(std::string fileName) const
{
    std::ofstream file;
    file.open(fileName);

    if(not file.is_open())
        return;

    file << _n << ' ' << _m << '\n';
    
    for (size_t i = 0; i < _n; ++i )
    {
        for(size_t j = 0; j < _m; ++j)
        {
            file << matrix[i][j] << ' ';
        }
        file << '\n';
    }

}

Matrix Matrix::subMatrix(size_t x0, size_t y0, size_t x1, size_t y1) const
{
    
    assert (x1 >= x0 && y1 >= y0);

    Matrix *subOne = new Matrix(x1-x0+1, y1-y0+1);
    std::cout << x1 - x0 + 1 << std::endl;

    for (size_t i = x0; i < x1 +1; ++i)
    {
        for (size_t j = y0; j < y1+1; ++j)
        {
            std::cout << "Here" << std::endl;
            (*subOne)[i-x0][j-y0] = matrix[i][j]; 
        }
    }
    return *subOne;
}

#endif