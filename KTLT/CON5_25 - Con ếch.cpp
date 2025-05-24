#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> f(53);

void conech() {
    f[0] = 0;
    f[1] = 1;
    f[2] = 2;
    f[3] = 4;
    for (int i = 4; i <= 52; i++) {
        f[i] = f[i - 1] + f[i - 2] + f[i - 3];
    }
}

int main() {
    int t;
    cin >> t;
    conech();
    while (t--) {
        int n;
        cin >> n;
        cout << f[n] << endl;
    }
    return 0;
}