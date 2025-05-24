#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> f(53); // Mảng `f` lưu số cách con ếch có thể nhảy lên các bậc thang, tối đa 52 bậc

// Hàm `conech` để tính trước số cách nhảy lên các bậc thang
void conech() {
    f[0] = 0; // Không có cách nào để nhảy lên bậc 0
    f[1] = 1; // Có 1 cách để nhảy lên bậc 1
    f[2] = 2; // Có 2 cách để nhảy lên bậc 2
    f[3] = 4; // Có 4 cách để nhảy lên bậc 3
    for (int i = 4; i <= 52; i++) { // Tính số cách nhảy lên các bậc từ 4 đến 52
        f[i] = f[i - 1] + f[i - 2] + f[i - 3]; // Công thức: tổng số cách nhảy từ bậc `i-1`, `i-2`, và `i-3`
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