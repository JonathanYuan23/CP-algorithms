#pragma GCC optimize "Ofast"
#include <bits/stdc++.h>
using namespace std; using pii = pair<int, int>;  using piii = pair<int, pii>;  using piiii = pair<pii, pii>;  using vi = vector<int>;  using vii = vector<pii>;  using viii = vector<piii>;  using viiii = vector<piiii>; using ll = long long; using ull = unsigned long long; 
#define frein freopen("input.txt", "r", stdin)
#define freout freopen("output.txt", "w", stdout)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define LSB(x) (x & (-x))
#define sz(x) (int)(x.size())
#define ms(a, b) memset(a, b, sizeof a)

const int MOD = 1e9+7, INF = 0x3f3f3f3f, MX = 1e5+5, IMX = INT_MAX, IMN = INT_MIN;
const long long LLMX = LONG_LONG_MAX, LLMN = LONG_LONG_MIN;
const char nl = '\n';

bool vis[MX];
vector<int> adj[MX];
queue<int> q;

int n, m;

bool bfs(int source, int target) {
    vis[source] = 1;
    q.push(source);

    while(!q.empty()) {
        int u = q.front(); q.pop(); 
        for(auto v: adj[u]) {
            if(v == target) return 1;

            if(!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }

    return 0;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);  cout.tie(0);
    cin >> n >> m;
    for(int i=0, a, b; i<m; i++) {
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    return 0;
}
