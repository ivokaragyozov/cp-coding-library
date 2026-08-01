#include <iostream>
#include <istream>
#include <ostream>
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
