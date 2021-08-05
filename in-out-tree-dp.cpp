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
#define MAX 100005
#define pb push_back
#define pf push_front
#define LSB(x) (x & (-x))
#define sz(x) (int)(x.size())
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<pii, pii> piiii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<piii> viii;
typedef vector<piiii> viiii;

/*

height of tree rooted at each node
https://www.youtube.com/watch?v=Xng1Od_v6Ug

As with general dynamic programming, we're required to think of 3 things.

The DP state information you will keep.
The solution to the base case.
How to go from a smaller solution to a larger solution.

in-out tree dp is typically only used when we have to answer queries about each node

*/

vi adj[MAX];
int n, in[MAX], out[MAX], dp[MAX];

/*

    dfs1 gets the in values for each node
    the in value of a node is the maximum height going down it's subtree

*/

void dfs1(int node, int par){
    in[node] = 0;
    for(auto to: adj[node]){
        if(to == par) continue;
        dfs1(to, node);
        in[node] = max(in[node], in[to] + 1);
    }
}

/*

    dfs2 gets the out values for each node
    the out value of a node is the maximum height ignoring it's own subtree, but including everything above it

                1
               / \
              /   \
             2     5
            / \   / \
           /   \ 6   7
          3     4

    in this tree, the in value of node 2 would consider the nodes 3 and 4
    the out value of node 2 would consider  nodes 1, 5, 6, 7

    the formula for the out value of a node is out[node] = 1 + max(out[parent], max(in[siblings of node]) + 1)
    why do we have to consider out[parent], let's just say that 1 had a parent, we would also have to consider the nodes above 1

    but dfs2 doesn't get the out value from the parent of each node, rather, at each node, it evaluates the out values of it's children

    notice that max(in[siblings of node]) is always the maximum sibling, or the second largest sibling, thus we only need to find these two values

*/

void dfs2(int node, int par){
    int mx1(-1), mx2(-1);

    // find the two maximum values of in[children]
    for(auto to: adj[node]){
        if(to == par) continue;
        if(in[to] >= mx1){
            mx2 = mx1; 
            mx1 = in[to];
        }
        else if(in[to] > mx2) mx2 = in[to];
    }

	for(int to: adj[node]){
		if (to == par) continue;
		int use = mx1;
		
		if(mx1 == in[to]) 
			use = mx2;
		
        // push maximum height above child to out[child]
		out[to] = max(1+out[node], 2+use);
		
		dfs2(to, node);
	}
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(NULL);  cout.tie(NULL);
    frein;
    cin >> n;
    for(int i=0, u, v; i<n-1; i++){
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    for(int i=1; i<=n; i++) dp[i] = max(in[i], out[i]);

    return 0;
}