#include<bits/stdc++.h>
using namespace std;

int n,m; // число вершин
const int MAXN = 10000;
vector<int> g[MAXN]; // граф
bool used[MAXN];
vector<int> ans;
pair <int,int> p[MAXN];
 
void dfs (int v) {
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
			dfs (to);
	}
	ans.push_back (v);
}
 
void topological_sort() {
	for (int i=0; i<n; ++i)
		used[i] = false;
	ans.clear();
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs (i);
	reverse (ans.begin(), ans.end());
}

int main (){
    cin >> n >> m;
    int x,y;
    for (int i=1;i<=m;i++){
        cin >> x >> y;
        p[i] = make_pair(x,y);
        g[x-1].push_back(y-1);
    }
    topological_sort();
    bool l = 1;
    for (int i=1;i<=m;i++){
        x = p[i].first;
        y = p[i].second;
        int ind1 = 0;
        int ind2 = 0;
        for (int j=0;j<ans.size();j++){
            if (ans[j] == x-1){
                ind1 = j;
            }
            if (ans[j] == y-1){
                ind2 = j;
            }
        }
        if (ind2<ind1){
            l = 0;
        }
    }
    if (!l){
        cout << "No" << endl;
    }
    else {
        cout << "Yes" << endl;
        for (int i=0;i<ans.size();i++){
         cout << ans[i]+1 << " ";
        } 
    } 
}