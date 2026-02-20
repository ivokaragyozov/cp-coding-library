/* -------------------------- MaxFlow -------------------------- */
#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class MaxFlow {
public:
    MaxFlow(int n) : n(n), dep(n), ind(n, 0), g(n) {
    }

    void add_edge(int u, int v, T cap) {
        if (cap == 0) {
            return;
        }

        edges.push_back(edge_t(v, cap));
        g[u].push_back(edges.size() - 1);

        edges.push_back(edge_t(u, 0));
        g[v].push_back(edges.size() - 1);
    }

    T get_max_flow(int source, int sink) {
        T flow = 0;
        while (1) {
            bfs(source, sink);

            if (dep[source] == -1) {
                break;
            }

            fill(ind.begin(), ind.end(), 0);
            while (1) {
                T f = dfs(source, INT64_MAX);
                if (f == 0) {
                    break;
                }

                flow += f;
            }
        }

        return flow;
    }

private:
    struct edge_t {
        int v;
        T cap;

        edge_t() {
        }

        edge_t(int _v, T _cap) : v(_v), cap(_cap) {
        }
    };

    void bfs(int source, int sink) {
        queue<int> q;

        for (int i = 0; i < n; i++) {
            dep[i] = -1;
        }
        dep[sink] = 0;

        q.push(sink);

        while (!q.empty()) {
            int u = q.front();
            int d = dep[u];
            q.pop();

            if (u == source) {
                break;
            }

            for (auto e : g[u]) {
                if (edges[e ^ 1].cap != 0 && dep[edges[e].v] == -1) {
                    q.push(edges[e].v);
                    dep[edges[e].v] = d + 1;
                }
            }
        }
    }

    T dfs(int u, T mf) {
        if (dep[u] == 0) {
            return mf;
        }

        for (; ind[u] < g[u].size(); ind[u]++) {
            int v = edges[g[u][ind[u]]].v;
            T cap = edges[g[u][ind[u]]].cap;

            if (dep[v] == dep[u] - 1 && cap != 0) {
                T aux = dfs(v, min(mf, cap));

                if (aux > 0) {
                    edges[g[u][ind[u]]].cap -= aux;
                    edges[g[u][ind[u]] ^ 1].cap += aux;
                    return aux;
                }
            }
        }

        return 0;
    }

    int n;
    vector<int> dep, ind;
    vector<vector<int>> g;
    vector<edge_t> edges;
};

/* -------------------------- MaxFlow -------------------------- */
