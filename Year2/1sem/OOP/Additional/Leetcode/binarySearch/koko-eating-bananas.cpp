/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile.
If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.


Main idea:
    create a criteria, then minimize it parameter using binary seaerch

*/

#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::vector;

class Solution
{
public:
    int minEatingSpeed(vector<int> &piles, int h)
    {
        long minSpeed = piles.size(), maxSpeed = *std::max_element(piles.begin(), piles.end()), midSpeed;

        while (maxSpeed - minSpeed > 1)
        {
            midSpeed = (maxSpeed + minSpeed) / 2;
            cout << midSpeed << ' ' << canEatAllWithSpeed(piles, h, midSpeed) << endl;

            if (canEatAllWithSpeed(piles, h, midSpeed))
                maxSpeed = midSpeed;
            else
                minSpeed = midSpeed;
        }

        return (canEatAllWithSpeed(piles, h, minSpeed) ? minSpeed : maxSpeed);
    }

private:
    bool canEatAllWithSpeed(vector<int> &piles, int h, int eatingSpeed)
    {
        int hoursSpent = 0, n = piles.size();
        for (int i = 0; i < n; ++i)
        {
            hoursSpent += piles[i] / eatingSpeed + ((piles[i] % eatingSpeed) ? 1 : 0);
            if (hoursSpent > h)
                return false;
        }

        return true;
    }
};

int main()
{
    vector<int> V = {332484035,
                     524908576,
                     855865114,
                     632922376,
                     222257295,
                     690155293,
                     112677673,
                     679580077,
                     337406589,
                     290818316,
                     877337160,
                     901728858,
                     679284947,
                     688210097,
                     692137887,
                     718203285,
                     629455728,
                     941802184};
    Solution s;
    s.minEatingSpeed(V, 823855818);
}