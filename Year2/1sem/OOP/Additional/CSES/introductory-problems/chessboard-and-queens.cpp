#include <bits/stdc++.h>

using namespace std;

long countPlacements(int y, const vector<vector<bool>> &map, vector<bool> &position,
                     vector<bool> &leftDiag, vector<bool> &rightDiag, int mapSize = 8)
{

    if (y == 8)
    {
        return 1L;
    }
    long res = 0;

    for (int x = 0; x < mapSize; ++x)
    {
        if (!map[y][x] || position[x] || leftDiag[x + y] || rightDiag[x - y + mapSize - 1])
        {
            continue;
        }
        position[x] = leftDiag[x + y] = rightDiag[x - y + mapSize - 1] = true;
        res += countPlacements(y + 1, map, position, leftDiag, rightDiag);
        position[x] = leftDiag[x + y] = rightDiag[x - y + mapSize - 1] = false;
    }
    return res;
}

int main()
{
    vector<vector<bool>> map(8, vector<bool>(8, true));
    char c;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            cin >> c;
            if (c == '*')
                map[i][j] = false;
        }
    }

    vector<bool> left(64, false);
    vector<bool> right(64, false);
    vector<bool> position(8, false);

    cout << countPlacements(0, map, position, left, right) << endl;
}
