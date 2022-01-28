#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

string s[1000000];
string b[1000000];
map <string,int> m;
map <string,int> m1;
map <string,int> m2;

int main ()
{
    int n;
    cin >> n;
    vector <string> v1;
    for (int i=1;i<=n;i++){
        cin >> s[i] >> b[i];
        m[b[i]]++;
        if (!m1[s[i]]){
            m1[s[i]] = 1;
            v1.push_back(s[i]);
        }
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        if (!m2[b[i]]){
            cout << b[i] << " " << m[b[i]] << endl;
            m2[b[i]] = 1;
        }
    }
    sort(v1.begin(),v1.end());
    for (int i=0;i<v1.size()-1;i++){
        cout << v1[i] << ",";
    }
    cout << v1[v1.size()-1] << endl;
    return 0;
}