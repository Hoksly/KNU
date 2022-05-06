#include "functions.hpp"

int **input_matrix(uchar n)
{
    int **res = new int *[n], a, x, y;
    std::pair<int, int> *V = new std::pair<int, int>[n];

    for (uchar i = 0; i < n; ++i)
    {
        std::cin >> a >> x >> y;
        // std::cin >> x >> y;
        V[i].first = x;
        V[i].second = y;
    }

    calculate_distance(res, V, n);
    // print_i(res, n);
    delete V;

    return res;
}

int **input(uchar &n)
{
    int p;
    std::cin >> p;

    n = p;

    return input_matrix(n);
}
// DEBUG
void print_mas(bool *mas, int n)
{
    char c;
    for (int i = 0; i < n; ++i)
    {
        c = (mas[i]) ? '1' : '0';
        std::cout << c << ' ';
    }
    std::cout << '\n';
}

void print_d(double **mas, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {

            if ((i != j))
                std::cout << give_feromon(mas, i, j) << ' ';
            else
                std::cout << '0' << ' ';
        }
        std::cout << '\n';
    }
}

void print_i(int **mas, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i != j))
                std::cout << give_distance(mas, i, j) << ' ';
            else
                std::cout << '0' << ' ';
        }
        std::cout << '\n';
    }
}

void print_dd(double *mas, int n)
{

    for (int i = 0; i < n; ++i)
    {
        std::cout << mas[i] << ' ';
    }
    std::cout << '\n';
}

void set(double *mas, double what, int n)
{
    for (int i = 0; i < n; ++i)
        mas[i] = what;
}

void set(bool *mas, bool what, int n)
{
    for (int i = 0; i < n; ++i)
    {

        mas[i] = what;
        // std::cout << "SET " << (int)mas[i] << '\n';
    }
}