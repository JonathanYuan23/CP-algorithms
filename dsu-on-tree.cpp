#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize "Ofast"
#define frein freopen("input.txt", "r", stdin)
#define freout freopen("output.txt", "w", stdout)
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define MAX 10005
#define pb push_back
#define pf push_front
#define LSB(S) (S & (-S))
#define sz(x) (int)(x.size())
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<pii, pii> piiii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<piii> viii;
typedef vector<piiii> viiii;

int n, subSize[MAX], cnt[MAX], color[MAX];
vi adj[MAX], subtreeNodes[MAX];

void getSizeOfSubtrees(int node, int par){
    subSize[node] += 1;
    for(auto to: adj[node]){
        if(to == par) continue;
        getSizeOfSubtrees(to, node);
        subSize[node] += subSize[to];
    }
}

// small to large merging, kind of based on HLD

void dfs(int node, int par, bool keep){
    int mx = -1, bigChild = -1;

    // find largest child
    for(auto to: adj[node]){
        if(to != par && mx < subSize[to]){
            mx = subSize[to];
            bigChild = to;
        }
    }

    // dfs for all the child nodes other than bigChild
    for(auto to: adj[node]) if(to != par && to != bigChild) dfs(to, node, 0);

    // because subtreeNodes[node] is empty, after dfs'ing on the bigChild, we can directly swap the two which is O(1) operation
    if(bigChild != -1){
        dfs(bigChild, node, 1);
        swap(subtreeNodes[node], subtreeNodes[bigChild]);
    }

    // add the current node to the array of subtree nodes
    subtreeNodes[node].pb(node);

    // increment the current nodes color in the count array
    cnt[color[node]]++;

    // add all the nodes from the node's subtrees into node's array of subtree nodes, increment color counts while doing this
    for(auto to: adj[node]){
        if(to != par && to != bigChild){
            for(auto x: subtreeNodes[to]){
                cnt[color[x]]++;
                subtreeNodes[node].pb(x);
            }
        }
    }

    // if the current node is a smallChild, not bigChild, all it's nodes and colours will be processed anyways by it's ancestors, so decrement all the colour counts for it's subtrees (essentially, the last for loop is useless for !keep nodes idk why :/)
    if(!keep){
        for(auto to: subtreeNodes[node]){
            cnt[color[to]]--;
        }
    }
}

int main()
{
    // ios_base::sync_with_stdio(0); cin.tie(NULL);  cout.tie(NULL);
    cin >> n;
    for(int i=0, u, v; i<n-1; i++){
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    return 0;
}