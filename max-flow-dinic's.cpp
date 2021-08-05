#include <bits/stdc++.h>
using namespace std;

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, next;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        next.resize(n);
    }

    void addEdge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int edge : adj[v]) {
                if (edges[edge].cap - edges[edge].flow < 1 || level[edges[edge].u] != -1) continue;
                level[edges[edge].u] = level[v] + 1;
                q.push(edges[edge].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (v == t) return pushed;

        for (; next[v] < (int)adj[v].size(); next[v]++) {
            int edge = adj[v][next[v]];
            int u = edges[edge].u;
            if (level[v] + 1 != level[u] || edges[edge].cap - edges[edge].flow < 1) continue;
            long long bottleneck = dfs(u, min(pushed, edges[edge].cap - edges[edge].flow));
            if (bottleneck == 0) continue;
            edges[edge].flow += bottleneck;
            edges[edge ^ 1].flow -= bottleneck;
            return bottleneck;
        }
        return 0;
    }

    long long flow() {
        long long maxFlow = 0;
        while (bfs()) {
            
            // When running dfs, we may encounter a blocking flow, and may need to backtrack in order to find another path to the sink. The next array ensures that we can directly skip edges from a node that we know lead to a blocking flow. To do this we can keep an array of pointers which points to the next edge that can be used from a specific node

            fill(next.begin(), next.end(), 0);
            for (long long pushed = dfs(s, flow_inf); pushed!=0; pushed=dfs(s, flow_inf)) {
                maxFlow += pushed;
            }
        }
        return maxFlow;
    }
};

int main() {

    int n=6;
    int s=n-1;
    int t=n-2;

    Dinic maxFlow(n, s, t);

    // Source edges
    maxFlow.addEdge(s, 0, 10);
    maxFlow.addEdge(s, 1, 10);

    // Sink edges
    maxFlow.addEdge(2, t, 10);
    maxFlow.addEdge(3, t, 10);

    // Middle edges
    maxFlow.addEdge(0, 1, 2);
    maxFlow.addEdge(0, 2, 4);
    maxFlow.addEdge(0, 3, 8);
    maxFlow.addEdge(1, 3, 9);
    maxFlow.addEdge(3, 2, 6);

    cout << maxFlow.flow() << "\n";

    n=11;
    s=n-1;
    t=n-2;

    Dinic maxFlow2(n, s, t);

        // Source edges
    maxFlow2.addEdge(s, 0, 5);
    maxFlow2.addEdge(s, 1, 10);
    maxFlow2.addEdge(s, 2, 15);

    // Middle edges
    maxFlow2.addEdge(0, 3, 10);
    maxFlow2.addEdge(1, 0, 15);
    maxFlow2.addEdge(1, 4, 20);
    maxFlow2.addEdge(2, 5, 25);
    maxFlow2.addEdge(3, 4, 25);
    maxFlow2.addEdge(3, 6, 10);
    maxFlow2.addEdge(3, 7, 20);
    maxFlow2.addEdge(4, 2, 5);
    maxFlow2.addEdge(4, 7, 30);
    maxFlow2.addEdge(5, 7, 20);
    maxFlow2.addEdge(5, 8, 10);
    maxFlow2.addEdge(7, 8, 15);

    // Sink edges
    maxFlow2.addEdge(6, t, 5);
    maxFlow2.addEdge(7, t, 15);
    maxFlow2.addEdge(8, t, 10);

    cout << maxFlow2.flow() << "\n";
  
    return 0;
}