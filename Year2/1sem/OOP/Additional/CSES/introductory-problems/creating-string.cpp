#include <bits/stdc++.h>
using namespace std;

set<string> generateAllPermutations(string s)
{
    if (s.size() == 1)
        return {s};

    set<string> res;
    for (int i = 0; i < s.size(); ++i)
    {
        char toRemove = s[i];
        s.erase(s.begin() + i);
        set<string> generatedStrings = generateAllPermutations(s);
        for (string newString : generatedStrings)
        {
            for (int i = 0; i < newString.size(); ++i)
            {
                newString.insert(newString.begin() + i, toRemove);
                res.insert(newString);
                newString.erase(newString.begin() + i);
            }
        }
        s.insert(s.begin() + i, toRemove);
    }
    return res;
}

int main()
{
    string s;
    cin >> s;
    set<string> per = generateAllPermutations(s);
    cout << per.size() << '\n';
    for (string s : per)
    {
        cout << s << '\n';
    }
}