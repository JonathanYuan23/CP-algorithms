/*

heavy-light decomposition to find the sum of the heights of all nodes on the path between a-b, uses 0-based indexing for nodes

https://www.youtube.com/watch?v=1PvT2d9lgqY
https://ideone.com/EeDdrA

testcase: #nodes, edges = nodes-1, #queries, query(nodeA, nodeB)

input:
15
1 2
1 3
2 4
2 5
3 6
3 7
6 8
6 9
7 10
7 11
4 12
4 13
5 14
5 15
7
2 3
14 15
8 14
3 10
1 9
10 15
9 10

output:
2
8
12
6
6
12
11

*/

#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize "Ofast"
#define fre freopen("input.txt", "r", stdin)
#define ll long long
#define ull unsigned long long
#define MOD 998244353
#define fi first
#define se second
#define INF 0x3f3f3f3f3f3f3f3f
#define MAX 300005
#define pb push_back
#define LSB(S) (S & (-S))
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<piii> viii;

int parent[MAX], logt[2*MAX], dp[20][2*MAX], idx[20][2*MAX], subSize[MAX], chain[MAX], chainHead[MAX], position[MAX], arr[MAX], st[4*MAX], nodes, n, mnIndx, chainId = 0, pos = 0;
vi graph[MAX], height, last, euler;

void construct(){
    int P=floor(log2(n));
    for(int i=0; i<n; i++){
        dp[0][i] = height[i];
        idx[0][i] = i;
    }
    for(int i=2; i<=n; i++) logt[i] = logt[i/2]+1;
    long long leftInterval, rightInterval;
    for(int i=1; i<=P; i++){
        for(int j=0; j+(1<<i)<=n; j++){
            leftInterval=dp[i-1][j]; rightInterval=dp[i-1][j+(1<<(i-1))];
            dp[i][j]=min(leftInterval, rightInterval);
            idx[i][j]=(leftInterval<=rightInterval) ? idx[i-1][j] : idx[i-1][j+(1<<(i-1))];
        }
    }
}

void rmq(int l, int r){
    int len = r-l+1, P=logt[len];
    long long leftInterval = dp[P][l], rightInterval = dp[P][r-(1<<P)+1];
    mnIndx=(leftInterval<=rightInterval) ? idx[P][l] : idx[P][r-(1<<P)+1];
}

void visit(int node, int depth){
    last[node]=euler.size();
    euler.push_back(node);
    height.push_back(depth);
}

void process(int node, int par, int h){
    parent[node] = par;
    subSize[node] += 1;
    visit(node, h);
    for(auto to: graph[node]){
        if(to!=par){
            process(to, node, h+1);
            visit(node, h);
            subSize[node] += subSize[to];
        }
    }
}

int lca(int u, int v){
    int l = min(last[u], last[v]);
    int r = max(last[u], last[v]);
    rmq(l, r);
    return euler[mnIndx];
}

void build(int i, int l, int r){
    if(l==r){
        st[i] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(i*2, l, mid);
    build(i*2+1, mid+1, r);
    st[i] = st[i*2] + st[i*2+1];
}

void update(int i, int l, int r, int pos, int val){
    if(l==r){
        st[i] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(pos<=mid) update(i*2, l, mid, pos, val);
    else update(i*2+1, mid+1, r, pos, val);
    st[i] = st[i*2] + st[i*2+1];
}

int rsq(int i, int ql, int qr, int l, int r){
    if(l>=ql && r<=qr) return st[i];
    int mid = (l + r) / 2;
    if(qr<=mid) return rsq(i*2, ql, qr, l, mid);
    if(ql>mid) return rsq(i*2+1, ql, qr, mid+1, r);
    return rsq(i*2, ql, qr, l, mid) + rsq(i*2+1, ql, qr, mid+1, r);
}

void HLD(int node, int par, int h){
    int heavyChild = -1, heavySize = -1;
    chain[node] = chainId;
    arr[pos] = h;
    position[node] = pos++;
    for(auto to: graph[node]){
        if(to!=par){
            if(subSize[to] > heavySize){
                heavySize = subSize[to];
                heavyChild = to;
            }
        }
    }
    if(heavyChild!=-1) HLD(heavyChild, node, h+1);
    for(auto to: graph[node]){
        if(to!=par && to!=heavyChild){
            chainId++;
            chainHead[chainId] = to;
            HLD(to, node, h+1);
        }
    }
}

int query(int from, int to){
    int curr = from, ans = 0;
    while(chain[curr] != chain[to]){
        ans = ans + rsq(1, position[chainHead[chain[curr]]], position[curr], 0, nodes-1);
        curr = parent[chainHead[chain[curr]]];
    }
    ans = ans + rsq(1, position[to], position[curr], 0, nodes-1);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);  cout.tie(NULL);
    cin >> nodes;
    last.resize(nodes);
    for(int i=0, u, v; i<nodes-1; i++){
        cin >> u >> v;
        u--; v--;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    process(0, -1, 0);
    n = height.size();
    construct();
    chainHead[0] = 0;
    // alwyas set the root chainHead to 0 as it is skipped in the dfs
    HLD(0, -1, 0);
    build(1, 0, nodes-1);
    int q; 
    cin >> q;
    for(int i=0, u, v; i<q; i++){
        cin >> u >> v;
        u--; v--;
        int LCA = lca(u, v);
        int ans = query(u, LCA) + query(v, LCA) - arr[position[LCA]];
        cout << ans << '\n';
    }

    return 0;
}