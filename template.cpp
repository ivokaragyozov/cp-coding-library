#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define debug(x) cout << #x << " " << (x) << endl;
#define remax(a, b) a = max((a), (b));
#define remin(a, b) a = min((a), (b));

template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &x) {
    return out << x.first << ' ' << x.second;
}

template <typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &x) {
    return in >> x.first >> x.second;
}

template <typename T> istream &operator>>(istream &in, vector<T> &a) {
    for (auto &x : a) {
        in >> x;
    }
    return in;
};

template <typename T> ostream &operator<<(ostream &out, const vector<T> &a) {
    for (auto x : a) {
        out << x << ' ';
    }
    return out;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}
