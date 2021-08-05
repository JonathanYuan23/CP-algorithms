#include <bits/stdc++.h>
using namespace std; using ll = long long;
const int MAXN=32, MAXM=1005, INF=0x3f3f3f3f;

ll dp[MAXN+1][MAXM], idx[MAXN+1][MAXM], logt[MAXM], mn, mnIndx, nodes=17, n;
vector<int> graph[MAXM], height, last, euler, vis;

void construct(){
    int P=floor(log2(n));
    for(int i=0; i<n; i++){
        dp[0][i] = height[i];
        idx[0][i] = i;
    }
    for(int i=2; i<=n; i++) logt[i] = logt[i/2]+1;
    ll leftInterval, rightInterval;
    for(int i=1; i<=P; i++){
        for(int j=0; j+(1<<i)<=n; j++){
            leftInterval=dp[i-1][j];
            rightInterval=dp[i-1][j+(1<<(i-1))];
            dp[i][j]=min(leftInterval, rightInterval);
            // idx array holds indexes of min values
            idx[i][j]=(leftInterval<=rightInterval) ? idx[i-1][j] : idx[i-1][j+(1<<(i-1))];
        }
    }
}

void rmq(int l, int r){
    int len = r-l+1, P=logt[len];
    long long leftInterval = dp[P][l], rightInterval = dp[P][r-(1<<P)+1];
    mn=(leftInterval<=rightInterval) ? dp[P][l] : dp[P][r-(1<<P)+1];
    mnIndx=(leftInterval<=rightInterval) ? idx[P][l] : idx[P][r-(1<<P)+1];
}

void addEdge(int u, int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void visit(int node, int depth){
    // last keeps the index of the node in the euler tour (index of last occurrence)
    last[node]=euler.size();
    // euler tour nodes
    euler.push_back(node);
    // heights of euler tour nodes
    height.push_back(depth);
}

void dfs(int node, int h){
    vis[node]=1;
    visit(node, h);
    for(auto to: graph[node]){
        if(!vis[to]){
            dfs(to, h+1);
            visit(node, h);
        }
    }
}

int lca(int u, int v){
    int l = min(last[u], last[v]);
    int r = max(last[u], last[v]);
    rmq(l, r);
    return euler[mnIndx];
}

int main() {

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 5);
    addEdge(2, 6);
    addEdge(2, 7);
    addEdge(3, 8);
    addEdge(3, 9);
    addEdge(5, 10);
    addEdge(5, 11);
    addEdge(7, 12);
    addEdge(7, 13);
    addEdge(11, 14);
    addEdge(11, 15);
    addEdge(11, 16);

    last.resize(nodes);
    vis.assign(nodes, 0);

    dfs(0, 0);
    n=height.size();
    construct();
    cout << lca(13, 14) << "\n" << lca(9, 11) << "\n" << lca(12, 12) << "\n";

    return 0;
}