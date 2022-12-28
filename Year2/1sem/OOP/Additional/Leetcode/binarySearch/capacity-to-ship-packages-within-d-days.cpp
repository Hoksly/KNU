/*
A conveyor belt has packages that must be shipped from one port to another within days days.

The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship
with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.


The main idea:
    we define function that tell us can we using ship capacity of allowedCapacity transport everything that we need in weights vector
    then we use binary search to find the minimum of this capactity
    the complexity is O(n*log(n))

    Note: we can use greedy chech in function canShip because of the problem condition, in general case we need to use something
    like a backpack problem to answer the question
*/

#include <vector>

using std::vector;

class Solution

{

public:
    int shipWithinDays(vector<int> &weights, int days)

    {

        int minCapacity = 1, maxCapacity = 0, midCapacity;

        if (weights.size() > 1)

        {

            for (int i = 0; i < weights.size(); ++i)

                maxCapacity += weights[i];

            while (maxCapacity - minCapacity > 1)

            {

                midCapacity = (maxCapacity + minCapacity) / 2;

                if (canShip(weights, midCapacity, days))

                    maxCapacity = midCapacity;

                else

                    minCapacity = midCapacity;
            }

            return canShip(weights, minCapacity, days) ? minCapacity : maxCapacity;
        }

        else

            return weights[0];
    }

private:
    inline bool canShip(vector<int> &weights, int capacityAllowed, int daysAllowed)

    {

        int curWeight = 0;

        int days = 1;

        for (int weight : weights)

        {

            curWeight += weight;

            if (curWeight > capacityAllowed)

            {

                curWeight = weight;

                days += 1;

                if (days > daysAllowed || weight > capacityAllowed)

                    return false;
            }
        }

        return true;
    }
};

int main()
{
}