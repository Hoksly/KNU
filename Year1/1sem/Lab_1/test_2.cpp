#include <bits/stdc++.h>
using namespace std;
int main ()
{
    string s;
    cin >> s;
    int k = 0;
    vector<char> v;
    for(int i=s.size()-1;i>=0;i--){
        k++;
        v.push_back(s[i]);
        if (k==3){
            v.push_back(',');
            k = 0;
        }
    }
    if (s.size()%3==0){
        v.pop_back();
    }
    reverse(v.begin(),v.end());
    for(int i=0;i<v.size();i++){
        cout<<v[i];
    }
    int a = 5;
    int *pa = &a;
    cout << pa << endl;
}