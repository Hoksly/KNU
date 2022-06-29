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
    std::cin >> n;

    return input_matrix(n);
}

int **file_input(uchar &n, std::string filename)
{
    std::ifstream file(filename);
    file >> n;

    int **res = new int *[n], a, x, y;
    std::pair<int, int> *V = new std::pair<int, int>[n];

    for (uchar i = 0; i < n; ++i)
    {
        file >> a >> x >> y;
        // std::cin >> x >> y;
        V[i].first = x;
        V[i].second = y;
    }

    calculate_distance(res, V, n);
    // print_i(res, n);
    delete V;

    return res;
}

// DEBUG
void print_s(std::string s)
{
    std::cout << s << std::endl;
}
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
char *substr(char *src, int beg, int end)
{
    char *str = new char[end - beg + 1];
    end++;
    for (int i = beg; i < end + 1; ++i)
    {
        str[i - beg] = src[i];
    }
    return str;
}
char **split(int n, char **what)
{
    char **ret, *str = *what;
    ret = new char *[n];
    int len, pos = 0, cur = 0;
    for (int i = 0; i < n; ++i)
    {
        len = 0;
        while (str[pos] == ' ')
        {
            pos++;
        }

        while (str[pos] != ' ' && str[pos] != '\n')
        {
            pos++;
            len++;
        }

        if (len != 0)
        {
            ret[cur] = substr(str, pos - len + 1, pos);
            cur++;
        }
    }
    return ret;
}
char *search_key(char *target, int n, char **arr)
{
    for (int i = 0; i < n; ++i)
    {

        if (!strcmp(target, arr[i]))
        {

            return arr[i];
        }
    }
    return nullptr;
}

char *search_value(char *target, int n, char **arr)
{
    for (int i = 0; i < n; ++i)
    {

        if (!strcmp(target, arr[i]))
        {

            if (i != n - 1)
                return arr[i + 1];
            else
                return nullptr;
        }
    }
    return nullptr;
}

void display_help()
{
    std::cout << "Usage:" << '\n';
    std::cout << "-h show help" << '\n';
    std::cout << "-c - console input" << '\n';
    std::cout << "-f filename - file input" << '\n';
    std::cout << "-p alpha beta - alpha and beta constants" << '\n';
    std::cout << "-i init feromon" << '\n';
    std::cout << "-r - feromon per ant" << '\n';
    std::cout << "-e evaporation constant: from 0 to 1" << '\n';
    std::cout << "-g - generations count" << '\n';
    std::cout << "-a ants count" << '\n';
    std::cout << "-s silent mode" << '\n';
    std::cout << "-n spicial mode for neural network" << '\n';
}