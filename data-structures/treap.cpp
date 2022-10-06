const int32_t MAX_N = 2e5;
std::mt19937 mt(69);

template< typename T >
struct Treap {
	struct Node {
		T key;
		int32_t prior, subsize;
		Node *l, *r;	
		
		Node() {}
		Node(T _key) : key(_key) {
			prior = mt();
			subsize = 1;

			l = nullptr;
			r = nullptr;
		}
	};
	
	int32_t nxtNode;
	Node *root, nodes[MAX_N + 5];

	Treap() {
		nxtNode = 0;
		root = nullptr;
	}
	
	int32_t get_size(Node *t) {
		return (t == nullptr ? 0 : t->subsize);
	}

	void pull(Node *t) {
		if(t == nullptr) {
			return;
		}

		t->subsize = get_size(t->l) + 1 + get_size(t->r);
	}

	std::pair< Node*, Node* > split(Node *t, T key) {
		if(t == nullptr) {
			return { nullptr, nullptr };
		}

		if(t->key <= key) {
			auto aux = split(t->r, key);
			t->r = aux.first;
			
			pull(t);

			return { t, aux.second };
		}
		else {
			auto aux = split(t->l, key);
			t->l = aux.second;
			
			pull(t);

			return { aux.first, t };
		}
	}

	Node* merge(Node *sm, Node *bg) {
		if(sm == nullptr) {
			return bg;
		}
		if(bg == nullptr) {
			return sm;
		}

		if(sm->prior > bg->prior) {
			sm->r = merge(sm->r, bg);
			pull(sm);
			return sm;
		}
		else {
			bg->l = merge(sm, bg->l);
			pull(bg);
			return bg;
		}
	}

	void insert_val(T x) {
		nodes[nxtNode] = Node(x);

		auto aux1 = split(root, x);
		aux1.first = merge(aux1.first, &nodes[nxtNode]);
		root = merge(aux1.first, aux1.second);

		nxtNode++;
	}

	void delete_all(T x) {	
		auto aux1 = split(root, x);
		auto aux2 = split(aux1.first, x - 1);
		root = merge(aux2.first, aux1.second);
	}

	void delete_single(T x) {
		auto aux1 = split(root, x);
		auto aux2 = split(aux1.first, x - 1);

		aux2.second = merge(aux2.second->l, aux2.second->r);
		aux1.first = merge(aux2.first, aux2.second);
		root = merge(aux1.first, aux1.second);	
	}
	
	Node* find_kth(Node *t, int32_t k) {
		if(t == nullptr) {
			return nullptr;
		}

		if(get_size(t->l) == k - 1) {
			return t;
		}
		else if(get_size(t->l) < k - 1) {
			return find_kth(t->r, k - get_size(t->l) - 1);
		}
		else {
			return find_kth(t->l, k);
		}
	}

	T find_kth(int32_t k) {
		auto aux = find_kth(root, k);

		if(aux == nullptr) {
			return -1;
		}

		return aux->key;
	}
	
	int32_t find_order(T x) {
		auto aux = split(root, x - 1);
		int32_t ans = get_size(aux.first);
		root = merge(aux.first, aux.second);
		return ans;
	}
	
	void print_treap(Node *t) {
		if(t == nullptr) {
			return;
		}

		print_treap(t->l);
		std::cout << t->key << " ";
		print_treap(t->r);
	}

	void print() {
		print_treap(root);
		std::cout << '\n';
	}
};

