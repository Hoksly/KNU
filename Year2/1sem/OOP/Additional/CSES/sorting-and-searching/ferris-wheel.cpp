#include <bits/stdc++.h>

using namespace std;

int countGondolas(const vector<int> &weights, int maxWeight)
{
    int leftPtr = 0, rightPtr = weights.size() - 1, totalGandolas = 0;
    vector<bool> haveGondola(weights.size(), false);

    while (leftPtr < rightPtr)
    {
        if (weights[leftPtr] + weights[rightPtr] <= maxWeight)
        {

            haveGondola[rightPtr] = haveGondola[leftPtr] = true;
            leftPtr++;
            rightPtr--;
            ++totalGandolas;
        }
        else
        {
            --rightPtr;
        }
    }

    for (int i = 0; i < weights.size(); ++i)
    {

        totalGandolas += ((int)!haveGondola[i]);
    }
    return totalGandolas;
}

int main()
{
    int n, maxWeight;

    cin >> n >> maxWeight;
    vector<int> weights(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> weights[i];
    }

    sort(weights.begin(), weights.end());

    cout << countGondolas(weights, maxWeight) << '\n';
}