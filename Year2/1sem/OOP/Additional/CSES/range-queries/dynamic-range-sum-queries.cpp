#include <bits/stdc++.h>

using namespace std;

template <class T>
class FenwikTree
{
    T *_arr = nullptr;
    size_t n;

public:
    int getSum(int index)
    {
        T sum = 0;

        index = index + 1;

        while (index > 0)
        {

            sum += _arr[index];

            index -= index & (-index);
        }
        return sum;
    }

    void update(int index, int val)
    {

        index = index + 1;

        while (index <= n)
        {

            _arr[index] += val;

            index += index & (-index);
        }
    }
    FenwikTree(vector<T> arr)
    {

        n = arr.size();
        _arr = new T[arr.size() + 1];
        for (int i = 1; i <= arr.size(); i++)
            _arr[i] = 0;

        for (int i = 0; i < n; i++)
            update(i, arr[i]);
    }
};

int main()
{
    int n, q, t, l, r;
    cin >> n >> q;
    vector<int> nums(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    FenwikTree<int> fTree(nums);

    for (int i = 0; i < q; ++i)
    {
        cin >> t >> l >> r;

        if (t == 1)
        {
            fTree.update(l - 1, r);
            nums[l - 1] = r;
        }
        else
        {
            cout << fTree.getSum(r - 1) - fTree.getSum(l - 1) + nums[l - 1] << '\n';
        }
    }
}