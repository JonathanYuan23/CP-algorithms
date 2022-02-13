#include<bits/stdc++.h>
using namespace std; using vi = vector<int>; using vii = vector<pair<int, int>>;
#define pb push_back
#define fi first
#define se second

const int MX = 1e5+5;

int N, M, dis[MX], flag[MX];
vii adj[MX];

void dijkstra(int source, int target) {
    for(int i=1; i<=N; i++) 
        dis[i] = INT_MAX;
    dis[source] = 0;
    priority_queue<int, vi, greater<int>> pq;
    pq.push(source);
    while(!pq.empty()) {
        int u = pq.top(); pq.pop();
        if(flag[u]) continue;
        flag[u] = 1;
        for(auto &v: adj[u]) {
            int d = dis[u] + v.se;
            if(dis[v.fi] > d) {
                dis[v.fi] = d;
                if(!flag[v.fi])
                    pq.push(v.fi);
            }
        }
    }
}

int main() {
    cin >> N >> M;
    for(int i=1, u, v, c; i<=M; i++) {
        cin >> u >> v >> c;
        adj[u].pb({v, c});
        adj[v].pb({u, c});
    }
    int A, B;
    cin >> A >> B;
    dijkstra(A, B);
}