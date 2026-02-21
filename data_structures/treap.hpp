/* -------------------------- Treap -------------------------- */
#pragma once
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5;

template <typename T>
class Treap {
private:
    struct node;
    using pnode = node*;

    struct node {
        T key;
        int prior, subsize;
        pnode l, r;

        node() {
        }

        node(T _key) : key(_key) {
            prior = mt();
            subsize = 1;

            l = nullptr;
            r = nullptr;
        }
    };

    int nxtNode = 0;
    pnode root = nullptr;
    node nodes[MAX_N + 5];
    static mt19937 mt;

    int get_size(pnode t) const {
        return (t == nullptr ? 0 : t->subsize);
    }

    void pull(pnode t) {
        if (t == nullptr) {
            return;
        }

        t->subsize = get_size(t->l) + 1 + get_size(t->r);
    }

    pair<pnode, pnode> split(pnode t, T key) {
        if (t == nullptr) {
            return { nullptr, nullptr };
        }

        if (t->key <= key) {
            auto [l, r] = split(t->r, key);
            t->r = l;

            pull(t);

            return { t, r };
        }
        else {
            auto [l, r] = split(t->l, key);
            t->l = r;

            pull(t);

            return { l, t };
        }
    }

    pnode merge(pnode sm, pnode bg) {
        if (sm == nullptr) {
            return bg;
        }
        if (bg == nullptr) {
            return sm;
        }

        if (sm->prior > bg->prior) {
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

    pnode find_kth(pnode t, int k) {
        if (t == nullptr) {
            return nullptr;
        }

        if (get_size(t->l) == k - 1) {
            return t;
        }
        else if (get_size(t->l) < k - 1) {
            return find_kth(t->r, k - get_size(t->l) - 1);
        }
        else {
            return find_kth(t->l, k);
        }
    }

    void print_treap(pnode t) {
        if (t == nullptr) {
            return;
        }

        print_treap(t->l);
        cout << t->key << " ";
        print_treap(t->r);
    }

public:
    int get_size() const {
        return get_size(root);
    }

    void insert_val(T x) {
        nodes[nxtNode] = node(x);

        auto [l, r] = split(root, x);
        l = merge(l, &nodes[nxtNode]);
        root = merge(l, r);

        nxtNode++;
    }

    void delete_all(T x) {
        auto [l1, r1] = split(root, x);
        auto [l2, r2] = split(l1, x - 1);
        root = merge(l2, r1);
    }

    void delete_single(T x) {
        auto [l1, r1] = split(root, x);
        auto [l2, r2] = split(l1, x - 1);
        r2 = merge(r2->l, r2->r);
        r1 = merge(l2, r2);
        root = merge(l1, r1);
    }

    T find_kth(int k) {
        auto aux = find_kth(root, k);

        if (aux == nullptr) {
            return -1;
        }

        return aux->key;
    }

    int find_order(T x) {
        auto aux = split(root, x - 1);
        int ans = get_size(aux.first);
        root = merge(aux.first, aux.second);
        return ans;
    }

    void print() {
        print_treap(root);
        cout << '\n';
    }
};

template <typename T>
mt19937 Treap<T>::mt(69);
/* -------------------------- Treap -------------------------- */
