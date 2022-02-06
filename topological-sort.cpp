#include<bits/stdc++.h>
using namespace std;
using vi = vector<int>;

#define pb push_back

const int MX = 1e5+5;

int N, M, in[MX];
vi adj[MX];
queue<int> q;

int main() {
    cin >> N >> M;
    for(int i=0, u, v; i<M; i++) {
        cin >> u >> v;
        adj[u].pb(v);
        in[v]++;
    }
    for(int i=0; i<N; i++) 
        if(!in[i])
            q.push(i);
    int cnt = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        cnt++;
        for(auto &v: adj[u]) 
            if(--in[v] == 0)
                q.push(v);
    }
    // DAG
    if(cnt == N) {}
    // Cycle exists
    else {}
}