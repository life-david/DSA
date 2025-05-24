#include <bits/stdc++.h> // Thư viện tổng hợp
using namespace std;

int main() {
    int t;
    cin >> t; // Nhập số lượng test case

    while (t--) {
        int n, k;
        cin >> n >> k; // Nhập độ dài mảng và giá trị cần tìm

        int xh = 0; // Biến đếm số lần xuất hiện của k
        int a[n] = {}; // Khai báo mảng a có n phần tử, khởi tạo tất cả bằng 0

        for (int i = 0; i < n; i++) {
            cin >> a[i]; // Nhập từng phần tử của mảng
        }

        for (int i = 0; i < n; i++) {
            if (a[i] == k) {
                cout << i + 1 << endl; // In ra vị trí (1-based) đầu tiên tìm được
                xh++; // Tăng biến đếm
                break; // Dừng ngay khi tìm thấy (nếu chỉ cần vị trí đầu tiên)
            }
        }

        if (xh == 0) {
            cout << "NO" << endl; // Nếu không tìm thấy, in "NO"
        }
    }
}
