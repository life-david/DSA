#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9 + 7;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> s(n);
        ll res = 0;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        
        priority_queue<ll, vector<ll>, greater<ll>> noiday;
        for (int i = 0; i < n; i++) {
            noiday.push(s[i]);
        }
        
        while (noiday.size() > 1) {
            ll first = noiday.top();
            noiday.pop();
            ll second = noiday.top();
            noiday.pop();
            ll temp = (first + second) % mod;
            res = (res + temp) % mod;
            noiday.push(temp);
        }
        
        cout << res << endl;
    }
    return 0;
}