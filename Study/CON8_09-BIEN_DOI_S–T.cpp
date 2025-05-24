#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD = 1e9 + 7;

// Hàm tính số bước để biến T thành S theo các quy tắc đã cho
ll biendoi(ll S, ll T) {
    int step = 0; // Biến đếm số bước
    // Tiến hành vòng lặp cho đến khi T <= S
    while (T > S) {
        // Nếu T là số chẵn, chia T cho 2
        if (T % 2 == 0) {
            T = T / 2; // Chia T cho 2
        } else {
            // Nếu T là số lẻ, cộng 1 vào T
            T = T + 1; // Tăng T lên 1
        }
        step++; // Tăng số bước sau mỗi phép toán
    }
    // Nếu T đã nhỏ hơn hoặc bằng S, chỉ cần trừ để hoàn thành số bước
    if (T <= S) {
        step += (S - T); // Tính số bước còn lại để đưa T về S
    }
    return step; // Trả về số bước cần thiết
}

int main() {
    int t; // Số lượng test case
    cin >> t; // Nhập số lượng test case
    while (t--) { // Lặp qua tất cả các test case
        ll S, T; // Nhập S và T cho mỗi test case
        cin >> S >> T;
        ll res = biendoi(S, T);  // Gọi hàm biendoi để tính số bước
        cout << res << endl; // In kết quả
    }
    return 0; // Kết thúc chương trình
}
