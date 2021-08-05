#include <bits/stdc++.h>
using namespace std;

const int MX = 50;

int n, m, disc[MX], low[MX], vis[MX], timer;
vector<int> adj[MX]; vector<pair<int, int>> bridges;

void dfs(int u, int p){
    vis[u] = 1, low[u] = disc[u] = ++timer;
    for(auto v: adj[u]){
        if(v == p) continue;
        if(vis[v]) low[u] = min(low[u], disc[v]);
        else{
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > disc[u]){
                cout << u << ' ' << v << '\n';
                bridges.push_back({u, v});
            }
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i=0, u, v; i<m; i++){
        cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    memset(vis, 0, sizeof vis); memset(disc, -1, sizeof disc); memset(low, -1, sizeof low);
    for(int i=1; i<=n; i++) if(!vis[i]) dfs(i, -1);
    return 0;
}