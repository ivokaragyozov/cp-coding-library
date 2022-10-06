const int32_t MAX_N = 6e5;
std::mt19937 mt(69);

template< typename T >
struct ImplicitTreap {
	struct Node {
		bool rev;
		int prior, subtree;
		T val, total;
		Node *l, *r, *par;
		
		Node() {}
		Node(T _val) : val(_val), total(_val) {
			rev = false;
			prior = mt();
			subtree = 1;

			l = nullptr;
			r = nullptr;
		}

		static int32_t getSubtree(Node *x) {
			return (x != nullptr ? x->subtree : 0);
		}
		
		static T getVal(Node *x) {
			if(x == nullptr) {
				return T();
			}

			return x->val;
		}

		static T getTotal(Node *x) {
			if(x == nullptr) {
				return T();
			}

			return x->total;
		}

		static void push(Node *x) {
			if(x == nullptr) {
				return;
			}
			
			if(x->rev) {
				std::swap(x->l, x->r);
				x->rev = false;

				if(x->l != nullptr) {
					x->l->rev ^= 1;
				}
				if(x->r != nullptr) {
					x->r->rev ^= 1;
				}
			}
		}
		
		static void pull(Node *x) {
			if(x == nullptr) {
				return;
			}
			
			push(x->l);
			push(x->r);

			x->subtree = getSubtree(x->l) + 1 + getSubtree(x->r);
			x->total = getTotal(x->l) + x->val + getTotal(x->r);
		}
	
		static void updateParent(Node *x) {
			if(x == nullptr) {
				return;
			}

			if(x->l != nullptr) {
				x->l->par = x;
			}
			if(x->r != nullptr) {
				x->r->par = x;
			}
		}

		static std::pair< Node*, Node* > split(Node *t, int32_t key, int32_t add = 0) {
			if(t == nullptr) {
				return { nullptr, nullptr };
			}

			push(t);

			int32_t curr = add + Node::getSubtree(t->l) + 1;
			if(curr <= key) {
				auto aux = split(t->r, key, curr);
				
				if(t->r != nullptr) {
					t->r->par = nullptr;
				}

				t->r = aux.first;
				updateParent(t);
				pull(t);
				return { t, aux.second };
			}
			else {
				auto aux = split(t->l, key, add);
				
				if(t->l != nullptr) {
					t->l->par = nullptr;	
				}

				t->l = aux.second;
				updateParent(t);
				pull(t);
				return { aux.first, t };
			}
		}

		static Node* merge(Node *sm, Node *bg) {
			push(sm);
			push(bg);

            if(sm == nullptr) {
				return bg;
			}
			if(bg == nullptr) {
				return sm;
			}

	    	if(sm->prior > bg->prior) {
				if(sm->r != nullptr) {
					sm->r->par = nullptr;
				}

				sm->r = merge(sm->r, bg);
				updateParent(sm);
				pull(sm);
				return sm;
			}
			else {
				if(bg->l != nullptr) {
					bg->l->par = nullptr;
				}

				bg->l = merge(sm, bg->l);
				updateParent(bg);
				pull(bg);
				return bg;
			}
		}
	};

	int32_t nxtNode;
	Node nodes[MAX_N + 5], *root;

	Node* getNode(T val) {
		nodes[nxtNode] = Node(val);
		return &nodes[nxtNode++];
	}

	void insertAtInd(int32_t ind, Node *t) {
		auto aux = Node::split(root, ind - 1);
		aux.first = Node::merge(aux.first, t);
		root = Node::merge(aux.first, aux.second);
	}
	
	std::vector< Node* > splitInterval(int32_t low, int32_t high) {
		auto aux1 = Node::split(root, low - 1);
		auto aux2 = Node::split(aux1.second, high - low + 1);

		std::vector< Node* > ans = { aux1.first, aux2.first, aux2.second };
		return ans;
	}

	void mergeIntervals(const std::vector< Node* > &v) {
		root = nullptr;
		for(auto &t : v) {
			root = Node::merge(root, t);
		}
	}

	void reverseInterval(int32_t low, int32_t high) {
		auto aux = splitInterval(low, high);
		if(aux[1] != nullptr) {
			aux[1]->rev = true;
		}
		mergeIntervals(aux);
	}

	void printTreap(Node *t) {
		if(t == nullptr) {
			return;
		}

		printTreap(t->l);
		std::cout << t->val << " ";
		printTreap(t->r);
	}

	void print() {
		printTreap(root);
		std::cout << '\n';
	}
};

