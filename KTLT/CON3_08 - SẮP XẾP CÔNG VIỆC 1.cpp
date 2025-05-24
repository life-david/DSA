#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<pair<int, int>> a(n);
        for (auto &p : a) cin >> p.first;
        for (auto &p : a) cin >> p.second;
        sort(a.begin(), a.end(), [](auto &x, auto &y) {
            return x.second < y.second;
        });
        int cnt = 1, end = a[0].second;
        for (int i = 1; i < n; ++i)
            if (a[i].first >= end)
                ++cnt, end = a[i].second;
        cout << cnt << '\n';
    }
}
