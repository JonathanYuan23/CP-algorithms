#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define MAXN 100005
#define pb push_back
#define LSB(S) (S & (-S))
typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> piii;

int N, M, L, start, farthest, maxd, center, rad, dis[MAXN], pre[MAXN], vis[MAXN];
vector<pii> graph[MAXN], centers;

void dfs(int cur, int par, int mx){
    dis[cur]=mx;
    vis[cur]=1;
    if(mx>maxd){
        maxd=mx;
        farthest=cur;
    }
    for(auto x: graph[cur]){
        if(x.fi!=par){
            pre[x.fi]=cur;
            dfs(x.fi, cur, mx+x.se);
        }
    }
}

void findCenter(int node){
    maxd=INT_MIN;
    dfs(node, -1, 0);
    maxd=INT_MIN; start=farthest;
    dfs(farthest, -1, 0);
    rad=INT_MAX; 
    center=node;
    for(; farthest!=start; farthest=pre[farthest]){
        if(max(maxd-dis[farthest], dis[farthest])<rad){
            center=farthest; 
            rad=max(maxd-dis[farthest], dis[farthest]);
        }
    }
    centers.pb({rad, center});
}