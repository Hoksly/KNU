#include <iostream>
#include <string.h>
#include <vector>
#include <stack>

using namespace std;

bool IsStrike(int x1, int y1, int x2, int y2, int N)
{
    // 1. Горизонталь, вертикаль
    // Ферзі б'ють один одного, якщо якісь 2 значення-параметри співпадають
    if ((x1 == x2) || (y1 == y2))
        return true;

    // 2. Головна діагональ
    int tx, ty; // додаткові змінні

    // 2.1. Вліво-вверх
    tx = x1 - 1;
    ty = y1 - 1;
    while ((tx >= 1) && (ty >= 1))
    {
        if ((tx == x2) && (ty == y2))
            return true;
        tx--;
        ty--;
    }

    // 2.2. Вправо-вниз
    tx = x1 + 1;
    ty = y1 + 1;
    while ((tx <= N) && (ty <= N))
    {
        if ((tx == x2) && (ty == y2))
            return true;
        tx++;
        ty++;
    }

    // 3. Допоміжна діагональ
    // 3.1. Вправо-вверх
    tx = x1 + 1;
    ty = y1 - 1;
    while ((tx <= N) && (ty >= 1))
    {
        if ((tx == x2) && (ty == y2))
            return true;
        tx++;
        ty--;
    }

    // 3.2. Вліво-вниз
    tx = x1 - 1;
    ty = y1 + 1;
    while ((tx >= 1) && (ty <= N))
    {
        if ((tx == x2) && (ty == y2))
            return true;
        tx--;
        ty++;
    }
    return false;
}

bool Strike(int M[], int p, int n)
{
    int px, py, x, y;
    int i;

    px = M[p];
    py = p;

    for (i = 1; i <= p - 1; i++)
    {
        x = M[i];
        y = i;
        if (IsStrike(x, y, px, py, n))
            return true;
    }
    return false;
}

bool **create_map(int n)
{
    bool **map = new bool *[n];
    for (int i = 0; i < n; ++i)
    {
        map[i] = new bool[n];
        memset(map[i], true, n);
    }
}

void gg()
{
}

inline int *copy(int *mas, int n)
{
    int *new_mas = new int[n];
    for (int i = 0; i < n; ++i)
        new_mas[i] = mas[i];
    return new_mas;
}

void add_mas(int *mas, int n, vector<int *> &V)
{
    V.push_back(copy(mas, n));
}

vector<int *> find_all(int N)
{
    int p, k;
    int *M = new int[N];
    p = 1;
    M[p] = 0;
    M[0] = 0;
    k = 0;

    // цикл формування розміщення
    while (p > 0) // якщо p==0, то вихід з циклу
    {
        M[p] = M[p] + 1;
        if (p == N) // останній елемент
        {
            if (M[p] > N)
            {
                while (M[p] > N)
                    p--; // перемотати назад
            }
            else
            {
                if (!Strike(M, p))
                {
                    // зафіксувати розміщення
                    AddToListBox(M, N);
                    k++;
                    p--;
                }
            }
        }
        else // не останній елемент
        {
            if (M[p] > N)
            {
                while (M[p] > N)
                    p--; // перемотати назад
            }
            else
            {
                if (!Strike(M, p)) // Якщо M[p] не накладається з попередніми M[1],M[2], ..., M[p-1]
                {
                    p++; // перейти на розміщення наступного ферзя
                    M[p] = 0;
                }
            }
        }
    }
}

int main()
{
}