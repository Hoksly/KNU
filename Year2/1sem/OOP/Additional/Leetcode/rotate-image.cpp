/*
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place,
which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.



Constraints:

    n == matrix.length == matrix[i].length
    1 <= n <= 20
    -1000 <= matrix[i][j] <= 1000


*/

#include <vector>
#include <iostream>

using namespace std;

class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int tmpVal, n = matrix.size();
        for (int i = 0; i < n / 2 + n % 2; ++i)
        {
            for (int j = 0; j < n / 2; ++j)
            {
                tmpVal = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - i - 1][n - j - 1];
                matrix[n - i - 1][n - j - 1] = matrix[j][n - 1 - i];
                matrix[j][n - 1 - i] = matrix[i][j];
                matrix[i][j] = tmpVal;
            }
        }
    }
};

int main()
{
    vector<vector<int>> V = {{5, 1, 9, 11},
                             {2, 4, 8, 10},
                             {13, 3, 6, 7},
                             {15, 14, 12, 16}};

    Solution s;
    s.rotate(V);
}