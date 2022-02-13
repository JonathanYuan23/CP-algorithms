#include<bits/stdc++.h>
using namespace std; using pii = pair<int, int>; using vi = vector<int>; using vii = vector<pii>;
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

    priority_queue<pii, vii, greater<pii>> pq;
    pq.push({0, source});
    
    while(!pq.empty()) {
        int u = pq.top().se; pq.pop();
        if(flag[u]) continue;
        flag[u] = 1;
        for(auto &v: adj[u]) {
            int d = dis[u] + v.se;
            if(dis[v.fi] > d) {
                dis[v.fi] = d;
                if(!flag[v.fi])
                    pq.push({dis[v.fi], v.fi});
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