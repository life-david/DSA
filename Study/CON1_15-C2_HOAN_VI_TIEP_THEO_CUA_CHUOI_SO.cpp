#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int t;
    cin >> t;
    while (t--) {
        int stt;
        cin >> stt; // Nhập số thứ tự của test case

        int n;
        string s;
        cin >> s;
        n = s.size(); // Lấy độ dài chuỗi

        int ok = 1; // Biến đánh dấu nếu không tồn tại hoán vị kế tiếp
        int vt = 0; // Vị trí cần hoán đổi

        // Bắt đầu từ cuối chuỗi, tìm vị trí đầu tiên i sao cho s[i] > s[i-1]
        for (int i = n - 1; i > 0; i--) {
            if (s[i] > s[i - 1]) {
                vt = i - 1; // Lưu vị trí cần hoán đổi
                ok = 0;     // Đánh dấu là tồn tại hoán vị kế tiếp
                break;
            }
        }

        if (ok == 1) {
            // Nếu không có vị trí thỏa mãn => chuỗi đã là hoán vị lớn nhất
            cout << stt << " " << "BIGGEST" << endl;
        } else {
            int k = 0;
            // Tìm ký tự nhỏ nhất bên phải vt mà lớn hơn s[vt]
            for (int i = n - 1; i > vt; i--) {
                if (s[i] > s[vt]) {
                    k = i; // Lưu lại vị trí cần hoán đổi với vt
                    break;
                }
            }

            // Hoán đổi hai ký tự
            swap(s[vt], s[k]);

            // Đảo ngược đoạn sau vt để đảm bảo là hoán vị nhỏ nhất tiếp theo
            reverse(s.begin() + vt + 1, s.end());

            // In ra kết quả
            cout << stt << " " << s << endl;
        }
    }

    return 0; // Kết thúc chương trình
}
