const int32_t MAX_N = 1e5;

template< typename T >
struct SegmentTree {
	int32_t treeSize;
	T data[4 * MAX_N + 5], lazy[4 * MAX_N + 5];

	void init(int32_t _treeSize) {
		treeSize = _treeSize;
	}

	void pushLazy(int32_t node, int32_t low, int32_t high) {
		data[node] += (high - low + 1) * lazy[node];

		if(low != high) {
			lazy[(node << 1)] += lazy[node];
			lazy[(node << 1) + 1] += lazy[node];
		}

		lazy[node] = 0;
	}

	void update(int32_t node, int32_t low, int32_t high, int32_t qLow, int32_t qHigh, T qVal) {
		pushLazy(node, low, high);
		
		if(low > qHigh || high < qLow) {
			return;
		}
		if(low >= qLow && high <= qHigh) {
			lazy[node] += qVal;
			pushLazy(node, low, high);
			return;
		}

		int32_t mid = ((low + high) >> 1);
		update((node << 1), low, mid, qLow, qHigh, qVal);
		update((node << 1) + 1, mid + 1, high, qLow, qHigh, qVal);

		data[node] = data[(node << 1)] + data[(node << 1) + 1];
	}

	void update(int32_t low, int32_t high, T val) {
		update(1, 1, treeSize, low, high, val);
	}

	T query(int32_t node, int32_t low, int32_t high, int32_t qLow, int32_t qHigh) {
		pushLazy(node, low, high);

		if(low > qHigh || high < qLow) {
			return 0;
		}
		if(low >= qLow && high <= qHigh) {
			return data[node];
		}

		int32_t mid = ((low + high) >> 1);
		return query((node << 1), low, mid, qLow, qHigh) + query((node << 1) + 1, mid + 1, high, qLow, qHigh);
	}

	T query(int32_t low, int32_t high) {
		return query(1, 1, treeSize, low, high);
	}
};
