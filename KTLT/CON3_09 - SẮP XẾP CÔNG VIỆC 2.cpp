#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t, n, id;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<pair<int, int>> jobs(n); // {deadline, profit}
        for (auto &j : jobs) cin >> id >> j.first >> j.second;
        sort(jobs.begin(), jobs.end(), [](auto &a, auto &b) {
            return a.second > b.second; // sort by profit descending
        });
        bitset<1005> slot;
        int cnt = 0, total = 0;
        for (auto &[d, p] : jobs) {
            while (d && slot[d]) --d;
            if (d && !slot[d]) {
                slot[d] = 1;
                ++cnt;
                total += p;
            }
        }
        cout << cnt << ' ' << total << '\n';
    }
}
