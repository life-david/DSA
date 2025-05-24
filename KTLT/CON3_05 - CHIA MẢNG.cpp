#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> A(n);

        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }

        sort(A.begin(), A.end());

        int sum1 = accumulate(A.begin(), A.begin() + k, 0);
        int sum2 = accumulate(A.begin() + k, A.end(), 0);

        int sum3 = accumulate(A.begin(), A.begin() + (n - k), 0);
        int sum4 = accumulate(A.begin() + (n - k), A.end(), 0);

        cout << max(abs(sum2 - sum1), abs(sum4 - sum3)) << endl;
    }
    return 0;
}
