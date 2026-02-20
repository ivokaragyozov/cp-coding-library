/* -------------------------- SuffixArray -------------------------- */
#pragma once
#include <bits/stdc++.h>

using namespace std;

class SuffixArray {
private:
    void build_suff_array() {
        int n = t.size();

        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = { t[i], i };
        }
        sort(a.begin(), a.end());

        vector<int> ranks(n);
        ranks[a[0].second] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first) {
                ranks[a[i].second] = ranks[a[i - 1].second];
            }
            else {
                ranks[a[i].second] = ranks[a[i - 1].second] + 1;
            }
        }

        for (int k = 0; (1 << k) < n; k++) {
            vector<pair<pair<int, int>, int>> v(n);

            for (int i = 0; i < n; i++) {
                v[i] = { { ranks[i], ranks[(i + (1 << k)) % n] }, i };
            }

            radix_sort(v);

            for (int i = 0; i < n; i++) {
                suffArr[i] = v[i].second;
            }

            ranks[suffArr[0]] = 0;
            for (int i = 1; i < n; i++) {
                if (v[i].first == v[i - 1].first) {
                    ranks[suffArr[i]] = ranks[suffArr[i - 1]];
                }
                else {
                    ranks[suffArr[i]] = ranks[suffArr[i - 1]] + 1;
                }
            }
        }
    }

    void build_lcp_array() {
        int n = t.size();

        vector<int> revSuff(n);
        for (int i = 0; i < n; i++) {
            revSuff[suffArr[i]] = i;
        }

        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            int pi = revSuff[i];
            int j = suffArr[pi - 1];

            while (i + k < n && j + k < n && t[i + k] == t[j + k]) {
                k++;
            }

            lcpArr[pi] = k;
            k = max(k - 1, 0);
        }
    }

public:
    string t;
    vector<int> suffArr, lcpArr;

    SuffixArray(const string& s) {
        t = s + '$';

        suffArr.resize(t.size());
        lcpArr.resize(t.size());

        build_suff_array();
        build_lcp_array();
    }

    void radix_sort(vector<pair<pair<int, int>, int>>& v) {
        int n = v.size();

        {
            vector<int> cnt(n, 0);
            for (auto& x : v) {
                cnt[x.first.second]++;
            }

            vector<int> ind(n, 0);
            for (int i = 1; i < n; i++) {
                ind[i] = ind[i - 1] + cnt[i - 1];
            }

            vector<pair<pair<int, int>, int>> newV(n);
            for (auto& x : v) {
                newV[ind[x.first.second]] = x;
                ind[x.first.second]++;
            }

            v = newV;
        }

        {
            vector<int> cnt(n, 0);
            for (auto& x : v) {
                cnt[x.first.first]++;
            }

            vector<int> ind(n, 0);
            for (int i = 1; i < n; i++) {
                ind[i] = ind[i - 1] + cnt[i - 1];
            }

            vector<pair<pair<int, int>, int>> newV(n);
            for (auto& x : v) {
                newV[ind[x.first.first]] = x;
                ind[x.first.first]++;
            }

            v = newV;
        }
    }

    bool contains(const string& p) {
        int n = t.size();
        int m = p.size();

        int low = 0, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;

            bool ok = true;
            for (int i = 0; i < m; i++) {
                if (t[(suffArr[mid] + i) % n] < p[i]) {
                    low = mid + 1;
                    ok = false;
                    break;
                }
                else if (t[(suffArr[mid] + i) % n] > p[i]) {
                    high = mid - 1;
                    ok = false;
                    break;
                }
            }

            if (ok) {
                return true;
            }
        }

        return false;
    }

    int count_occurances(const string& p) {
        int n = t.size();
        int m = p.size();

        int l, h;
        {
            int low = 0, high = n - 1;
            while (low <= high) {
                int mid = (low + high) / 2;

                bool ok = true;
                for (int i = 0; i < m; i++) {
                    if (t[(suffArr[mid] + i) % n] < p[i]) {
                        low = mid + 1;
                        ok = false;
                        break;
                    }
                    else if (t[(suffArr[mid] + i) % n] > p[i]) {
                        high = mid - 1;
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    high = mid - 1;
                }
            }

            l = high + 1;
        }

        {
            int low = 0, high = n - 1;
            while (low <= high) {
                int mid = (low + high) / 2;

                bool ok = true;
                for (int i = 0; i < m; i++) {
                    if (t[(suffArr[mid] + i) % n] < p[i]) {
                        low = mid + 1;
                        ok = false;
                        break;
                    }
                    else if (t[(suffArr[mid] + i) % n] > p[i]) {
                        high = mid - 1;
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    low = mid + 1;
                }
            }

            h = low - 1;
        }

        return h - l + 1;
    }

    int64_t count_different_substrings() {
        int n = t.size();

        int64_t ans = 0;
        for (int i = 1; i < n; i++) {
            ans += (int64_t)n - 1 - suffArr[i] - lcpArr[i];
        }

        return ans;
    }
};

/* -------------------------- SuffixArray -------------------------- */
