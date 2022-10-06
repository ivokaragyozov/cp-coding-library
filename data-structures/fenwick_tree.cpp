const int32_t MAX_N = 1e5;

template< typename T >
struct FenwickTree {
	int32_t treeSize;
	T data[MAX_N + 5];	

	void init(int32_t _treeSize) {
		treeSize = _treeSize;
	}

	void update(int32_t ind, T val) {
		while(ind <= treeSize) {
			data[ind] += val;
			ind += (ind & (-ind));
		}
	}

	T get(int32_t ind) {
		T ans{};
		while(ind > 0) {
			ans += data[ind];
			ind -= (ind & (-ind));
		}
		return ans;
	}

	T getInterval(int32_t low, int32_t high) {
		return get(high) - get(low - 1);
	}
};
