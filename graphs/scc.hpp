class SCC {
private:
	struct Vertex {
		bool vis;
		int32_t comp;
		std::vector<int32_t> oute, ine;

		Vertex(): vis(false), comp(-1) {}
	};

	void dfs1(int32_t v, std::stack<int32_t> &st) {
		g[v].vis = true;

		for(auto u : g[v].oute) {
			if(!g[u].vis) dfs1(u, st);
		}

		st.push(v);
	}

	void dfs2(int32_t v, int32_t comp) {
		g[v].comp = comp;

		for(auto u : g[v].ine) {
			if(g[u].comp == -1) dfs2(u, comp);
		}
	}

public:
	std::vector<Vertex> g;
	std::vector<std::set<int32_t>> dag;

	SCC(int32_t n, std::vector<std::pair<int32_t, int32_t>> edges): g(n) {
		for(auto e : edges) {
			g[e.first].oute.pb(e.second);
			g[e.second].ine.pb(e.first);
		}

		std::stack<int32_t> st;
		for(int32_t i = 0; i < n; i++) {
			if(!g[i].vis) {
				dfs1(i, st);
			}
		}

		int32_t comp = 0;
		while(!st.empty()) {
			auto v = st.top();
			st.pop();

			if(g[v].comp == -1) dfs2(v, comp++);
		}
		
		dag.resize(comp);
		for(auto e : edges) {
			if(g[e.first].comp != g[e.second].comp) {
				dag[g[e.first].comp].insert(g[e.second].comp);
			}
		}
	}
};
