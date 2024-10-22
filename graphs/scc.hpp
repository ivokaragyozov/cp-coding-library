/* -------------------------- SCC -------------------------- */
#include <set>
#include <stack>
#include <vector>

using namespace std;

class SCC {
  private:
    struct vertex_t {
        bool vis;
        int comp;
        vector<int> oute, ine;

        vertex_t() : vis(false), comp(-1) {}
    };

    void dfs(int v, stack<int> &st) {
        g[v].vis = true;

        for (auto u : g[v].oute) {
            if (!g[u].vis)
                dfs(u, st);
        }

        st.push(v);
    }

    void dfs_rev(int v, int comp) {
        g[v].comp = comp;

        for (auto u : g[v].ine) {
            if (g[u].comp == -1)
                dfs_rev(u, comp);
        }
    }

  public:
    vector<vertex_t> g;
    vector<set<int>> dag;

    SCC(int n, vector<pair<int, int>> edges) : g(n) {
        for (auto e : edges) {
            g[e.first].oute.push_back(e.second);
            g[e.second].ine.push_back(e.first);
        }

        stack<int> st;
        for (int i = 0; i < n; i++) {
            if (!g[i].vis) {
                dfs(i, st);
            }
        }

        int comp = 0;
        while (!st.empty()) {
            auto v = st.top();
            st.pop();

            if (g[v].comp == -1)
                dfs_rev(v, comp++);
        }

        dag.resize(comp);
        for (auto e : edges) {
            if (g[e.first].comp != g[e.second].comp) {
                dag[g[e.first].comp].insert(g[e.second].comp);
            }
        }
    }
};
/* -------------------------- SCC -------------------------- */
