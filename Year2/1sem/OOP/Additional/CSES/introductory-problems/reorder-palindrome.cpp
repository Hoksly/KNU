#include <iostream>
#include <vector>
using namespace std;

int main()
{

    vector<int> counter(28, 0);

    string s;
    cin >> s;
    for (char c : s)
        counter[c - 'A']++;
    int err = 0;
    for (int count : counter)
        if (count & 1)
            err++;

    if (err > 1)
    {
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    int position = 0;
    for (char i = 0; i < counter.size(); ++i)
    {
        while (counter[i] > 1)
        {
            s[position] = s[s.size() - position - 1] = i + 'A';
            position++;
            counter[i] -= 2;
        }
    }
    for (char i = 0; i < counter.size(); ++i)
    {
        if (counter[i])
        {
            s[s.size() / 2] = i + 'A';
        }
    }
    cout << s << endl;
    return 0;
}
