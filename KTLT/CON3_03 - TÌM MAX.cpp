#include <bits/stdc++.h>
using namespace std;

#define ll long long 
const int MOD = 1e9 + 7;

int main() {
    int T;
    cin >> T; 
    while (T--) {
        int N;
        cin >> N; 
        vector<int> A(N); 
        for (int i = 0; i < N; i++) {
            cin >> A[i]; 
        }
        
        sort(A.begin(), A.end()); 

        ll tong = 0; 
        for (int i = 0; i < N; i++) {
            tong = (tong + i * 1LL * A[i]) % MOD; 
        }

        cout << tong << endl; 
    }
    return 0;
}