#include <bits/stdc++.h>

using namespace std;

inline int countSwaps(string s, string order, const vector<int> &count)
{
    int notInRightPlace = 0;

    int first, second, third;
    first = order[0] - '0';
    second = order[1] - '0';
    third = order[2] - '0';
    int arr[3] = {first, second, third};

    vector<vector<int>> V(3, vector<int>(3, 0));

    for (int i = 0; i < count[first]; ++i)
    {
        V[first][s[i] - '0']++;
    }

    for (int i = count[first]; i < count[first] + count[second]; ++i)
    {
        V[second][s[i] - '0']++;
    }

    for (int i = count[first] + count[second]; i < s.size(); ++i)
    {
        V[third][s[i] - '0']++;
    }
    /*
        for (int i = 0; i < 3; ++i)
        {
            for (int c : V[i])
                cout << c << ' ';
            cout << endl;
        }
        cout << endl;
    */
    // 1 2 0

    sort(arr, arr + 3);
    do
    {
        int mn = min(V[arr[0]][arr[1]], V[arr[1]][arr[0]]);
        V[arr[0]][arr[1]] -= mn;
        V[arr[1]][arr[0]] -= mn;
        notInRightPlace += mn;

        mn = min(V[arr[2]][arr[1]], V[arr[1]][arr[0]]);
        V[arr[2]][arr[1]] -= mn;
        V[arr[1]][arr[0]] -= mn;
        notInRightPlace += mn;
        V[arr[2]][arr[0]] += mn;

    } while (next_permutation(arr, arr + 3));

    // cout << endl;
    return notInRightPlace;
}
inline vector<int> countDigits(const string &s)
{
    vector<int> counter(3, 0);
    for (char c : s)
    {
        counter[c - '0']++;
    }
    return counter;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio();
    freopen("input.txt", "r", stdin);
    int t;
    int res1, res2, res3, res4, res5, res6;
    string s;
    cin >> t;
    vector<string> perm = {"012", "021", "102", "120", "201", "210"};
    // vector<string> perm = {"012"};

    int mn = 1000000000;

    while (t--)
    {
        mn = 1000000000;
        cin >> s;
        vector<int> counter = countDigits(s);
        // cout << counter[0] << ' ' << counter[1] << ' ' << counter[2] << endl;
        // cout << s << endl;
        for (string pr : perm)
        {
            // cout << pr << endl;
            int res = countSwaps(s, pr, counter);
            // cout << "res: " << res << endl;

            mn = min(res, mn);
        }
        cout << mn << endl;
    }
}

/*
   int mn = min(V[first][second], V[second][first]);
    notInRightPlace += mn;
    V[first][second] -= mn;
    V[second][first] -= mn;

    mn = min(V[first][third], V[third][first]);
    notInRightPlace += mn;
    V[first][third] -= mn;
    V[third][first] -= mn;

    mn = min(V[third][second], V[second][third]);
    notInRightPlace += mn;
    V[third][second] -= mn;
    V[second][third] -= mn;

    mn = min(V[third][first], V[second][first]);
    notInRightPlace += mn;
    V[third][first] -= mn;
    V[second][first] -= mn;
    V[third][first] += mn;


*/

// 00101212
/*
4
000
2010112
1011210
2120201

*/