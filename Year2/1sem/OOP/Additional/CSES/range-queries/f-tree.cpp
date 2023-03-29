#include <algorithm>

#include <cassert>

#include <iostream>

#include <vector>

using std::cout;

using std::endl;

using std::vector;

/** A data structure that can answer point update & range minimum queries. */

template <class T>
class MinSegmentTree
{

private:
    /** The operation to use for combining two elements. (Must be associative)

     */

    T comb(T a, T b) { return std::min(a, b); }

    const T DEFAULT = 1e18; // Will overflow if T is an int

    vector<T> segtree;

    int len;

public:
    MinSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}

    /** Sets the value at ind to val. */

    void set(int ind, T val)
    {

        assert(0 <= ind && ind < len);

        ind += len;

        segtree[ind] = val;

        for (; ind > 1; ind /= 2)
        {

            segtree[ind >> 1] = comb(segtree[ind], segtree[ind ^ 1]);
        }
    }

    T range_min(int start, int end)
    {

        assert(0 <= start && start < len && 0 < end && end <= len);

        T sum = DEFAULT;

        for (start += len, end += len; start < end; start /= 2, end /= 2)
        {

            if ((start & 1) != 0)
            {
                sum = comb(sum, segtree[start++]);
            }

            if ((end & 1) != 0)
            {
                sum = comb(sum, segtree[--end]);
            }
        }

        return sum;
    }
};

int main()
{

    int arr_len;

    int query_num;

    std::cin >> arr_len >> query_num;

    MinSegmentTree<int> segtree(arr_len);

    for (int i = 0; i < arr_len; i++)
    {

        int n;

        std::cin >> n;

        segtree.set(i, n);
    }

    for (int q = 0; q < query_num; q++)
    {

        int type;

        std::cin >> type;

        if (type == 1)
        {

            int ind;

            int val;

            std::cin >> ind >> val;

            segtree.set(ind - 1, val);
        }
        else if (type == 2)
        {

            int start;

            int end;

            std::cin >> start >> end;

            cout << segtree.range_min(start - 1, end) << '\n';
        }
    }
}
