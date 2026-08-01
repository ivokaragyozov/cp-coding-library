#include <iostream>
#include <istream>
#include <map>
#include <ostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& x) {
    return out << x.first << ' ' << x.second;
}

template <typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& x) {
    return in >> x.first >> x.second;
}

template <typename T>
istream& operator>>(istream& in, vector<T>& a) {
    for (auto& x : a) {
        in >> x;
    }
    return in;
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& a) {
    for (auto x : a) {
        out << x << ' ';
    }
    return out;
}

template <typename T>
ostream& operator<<(ostream& out, const set<T>& s) {
    for (const auto& x : s) {
        out << x << ' ';
    }
    return out;
}

template <typename T>
ostream& operator<<(ostream& out, const unordered_set<T>& s) {
    for (const auto& x : s) {
        out << x << ' ';
    }
    return out;
}

template <typename K, typename V>
ostream& operator<<(ostream& out, const map<K, V>& m) {
    for (const auto& [k, v] : m) {
        out << k << "->" << v << ' ';
    }
    return out;
}

template <typename K, typename V>
ostream& operator<<(ostream& out, const unordered_map<K, V>& m) {
    for (const auto& [k, v] : m) {
        out << k << "->" << v << ' ';
    }
    return out;
}

#define ll long long
#define debug(...)                                                                                 \
    cerr << "[" << #__VA_ARGS__ << "]:", [&](auto&&... args) {                                     \
        ((cerr << ' ' << args), ...);                                                              \
        cerr << endl;                                                                              \
    }(__VA_ARGS__)
#define remax(a, ...) a = max({ a, __VA_ARGS__ });
#define remin(a, ...) a = min({ a, __VA_ARGS__ });

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}
