#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int MX = 1e5+5;

bool vis[MX];
vector<int> adj[MX];
queue<int> q;

int n, m;

bool bfs(int source, int target) {
    vis[source] = 1;
    q.push(source);

    while(!q.empty()) {
        int u = q.front(); q.pop(); 
        for(auto v: adj[u]) {
            if(v == target) return 1;

            if(!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }

    return 0;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);  cout.tie(0);
    cin >> n >> m;
    for(int i=0, a, b; i<m; i++) {
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    return 0;
}
