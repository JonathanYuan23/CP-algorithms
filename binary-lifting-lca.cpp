#include <bits/stdc++.h>
using namespace std; 

const int MX = 1e5+5, LOG = 17; // LOG = ceil(log2(n))

int N, M, Q, depth[MX], ancestor[LOG][MX];
vector<int> adj[MX];

void dfs(int u, int par) {
    ancestor[0][u] = par;

    for(int k=1; k<LOG; k++) 
        ancestor[k][u] = ancestor[k-1][ancestor[k-1][u]];

    for(auto v: adj[u]) {
        if(v == par) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if(depth[u] < depth[v])
        swap(u, v);
    
    for(int k=LOG-1; k>=0; k--)
        if(ancestor[k][u] != -1 && depth[ancestor[k][u]] >= depth[v]) 
            u = ancestor[k][u];

    /*

    alternative to the above 

    for(int k=LOG-1; k>=0; k--)
        if ((depth[u] - pow(2, k)) >= depth[v])
            u = ancestor[k][u];

    */

    // the lca is one the query nodes themselves
    if(u == v)
        return u;

    for(int k=LOG-1; k>=0; k--)
        if(ancestor[k][u] != -1 && ancestor[k][u] != ancestor[k][v])
            u = ancestor[k][u], v = ancestor[k][v];

    return ancestor[0][u];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);  cout.tie(0);
    cin >> N >> M >> Q;
    // construct tree
    for(int i=0, u, v; i<M; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }   
    // initialise ancestor table
    dfs(0, -1);
    // queries
    for(int i=0, u, v; i<Q; i++) {
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }   
    return 0;
}

/*

test case

17 16 4
0 1
0 2
2 3
2 4
2 5
3 13
3 14
14 15
15 16
1 6
1 7
7 8
8 9
8 10
6 11
6 12
4 15
10 12
5 16
9 16

expected output

2
1
2
0

*/