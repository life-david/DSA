#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;  // Số lượng bộ test
    while (t--) {
        int n;
        cin >> n;  // Số phần tử của dãy
        vector<int> a(n), dp(n, 1);  // a lưu dãy số, dp lưu độ dài dãy con tăng dài nhất kết thúc tại a[i]

        // Đọc dãy số
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // Áp dụng thuật toán DP để tính độ dài dãy con tăng dài nhất
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (a[i] > a[j]) {  // Nếu a[i] > a[j], ta có thể nối a[i] vào dãy con tăng kết thúc tại a[j]
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        // Kết quả là giá trị lớn nhất trong mảng dp
        int ans = *max_element(dp.begin(), dp.end());
        cout << ans << endl;
    }
    return 0;
}
