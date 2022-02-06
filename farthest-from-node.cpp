#include <bits/stdc++.h>
using namespace std;

#define MAXN 500005
#define pb push_back

int n, a, b, ans, v, dist[MAXN], dist2[MAXN];
vector<int> tree[MAXN];

void dfs(int node, int prev, int mx){
    dist[node]=mx;
    if(dist[node]>ans){
        ans=mx;  v=node;
    }
    for(auto x: tree[node]){
        if(x!=prev){
            dfs(x, node, mx+1);
        }
    }
}
void dfs2(int node, int prev, int mx){
    dist2[node]=mx;
    if(dist2[node]>ans){
        ans=mx;  v=node;
    }
    for(auto x: tree[node]){
        if(x!=prev){
            dfs2(x, node, mx+1);
        }
    }
}

int main()
{
    cin >> n;
    for(int i=1; i<n; i++){
        cin >> a >> b;
        tree[a].pb(b);
        tree[b].pb(a);
    }
    ans=INT_MIN; 
    dfs(1, -1, 1);
    ans=INT_MIN;
    dfs(v, -1, 1);
    dfs2(v, -1, 1);
    for(int i=1; i<=n; i++) cout << max(dist[i], dist2[i]) << "\n";
    
    return 0;
}