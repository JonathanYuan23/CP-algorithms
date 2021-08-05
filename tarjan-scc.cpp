// https://iq.opengenus.org/tarjans-algorithm/
// https://www.youtube.com/watch?v=TyWtx7q2D7Y
#include <bits/stdc++.h>
using namespace std;

const int MX = 500;

int n, m, disc[MX], low[MX], Time = 0;
vector<int> adj[MX];
stack<int> st;
bool onstack[MX];

void dfs(int u){
    disc[u] = low[u] = ++Time;
    st.push(u); 
    onstack[u] = 1;
    for(auto v: adj[u]){
        if(disc[v] == -1){
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(onstack[v]){
            low[u] = min(low[u], disc[v]);
        }
    }
    if(low[u] == disc[u]){
        while(1){
            int v = st.top();
            st.pop(); onstack[v] = 0;
            cout << v << ' ';
            if(u == v) break;
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);  cout.tie(NULL); 
    cin >> n >> m;
    for(int i=1, u, v; i<=m; i++){
        cin >> u >> v;
        adj[u].push_back(v);
    }
    memset(onstack, 0, sizeof onstack); 
    memset(disc, -1, sizeof disc); 
    memset(low, -1, sizeof low);
    for(int i=1; i<=n; i++) if(disc[i] == -1) dfs(i);
    return 0;
}

/*
8 13
1 2
4 2
2 3
3 1
4 6
6 5
5 4
5 3
8 6
7 5
8 7
7 8
4 3
*/