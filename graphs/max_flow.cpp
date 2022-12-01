const int32_t INF = 1e9 + 5;

template<typename T>
struct MaxFlow {
	struct Edge {
		int32_t v;
		T cap;

		Edge() {}
		Edge(int32_t _v, T _cap) : v(_v), cap(_cap) {}
	};

	int32_t n;
	std::vector<int32_t> dep, ind;
	std::vector<std::vector<int32_t>> g;
	std::vector<Edge> edges;

	MaxFlow(int32_t n): n(n), dep(n), ind(n, 0), g(n) {}

	void addEdge(int32_t u, int32_t v, T cap) {
		if(cap == 0) return;

		edges.push_back(Edge(v, cap));
		g[u].push_back(edges.size() - 1);

		edges.push_back(Edge(u, 0));
		g[v].push_back(edges.size() - 1);
	}

	void bfs(int32_t source, int32_t sink) {
		std::queue<int32_t> q;
		
		for(int32_t i = 0; i < n; i++) {
			dep[i] = -1;
		}
		dep[sink] = 0;

		q.push(sink);

		while(!q.empty()) {
			int32_t u = q.front();
			int32_t d = dep[u];
			q.pop();

			if(u == source) {
				break;
			}

			for(auto e : g[u]) {
				if(edges[e ^ 1].cap != 0 && dep[edges[e].v] == -1) {
					q.push(edges[e].v);
					dep[edges[e].v] = d + 1;
				}
			}	
		}
	}

	T dfs(int32_t u, T mf) {
		if(dep[u] == 0) {
			return mf;
		}

		for(; ind[u] < g[u].size(); ind[u]++) {
			int32_t v = edges[g[u][ind[u]]].v;
			T cap = edges[g[u][ind[u]]].cap;
			
			if(dep[v] == dep[u] - 1 && cap != 0) {
				T aux = dfs(v, std::min(mf, cap));
				
				if(aux > 0) {
					edges[g[u][ind[u]]].cap -= aux;
					edges[g[u][ind[u]] ^ 1].cap += aux;
					return aux;
				}
			}
		}
		
		return 0;
	}

	T getMaxFlow(int32_t source, int32_t sink) {
		T flow = 0;
		while(1) {
			bfs(source, sink);

			if(dep[source] == -1) {
				break;
			}
			
			std::fill(ind.begin(), ind.end(), 0);
			while(1) {
				T f = dfs(source, INF);
				if(f == 0) {
					break;
				}
				
				flow += f;
			}
		}

		return flow;
	}
};

