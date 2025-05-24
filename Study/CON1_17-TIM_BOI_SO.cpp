#include<bits/stdc++.h>              // Thư viện tổng hợp, bao gồm tất cả các thư viện chuẩn của C++
using namespace std;                // Sử dụng không gian tên std để không cần viết std:: trước các hàm/thành phần

int main(){
    int T;
    cin >> T;                       // Nhập số lượng test case T
    while (T--) {                   // Lặp qua từng test case
        int N;
        cin >> N;                   // Nhập số nguyên dương N

        queue<string> q;           // Tạo hàng đợi để lưu các số dạng chuỗi
        q.push("9");               // Bắt đầu với số "9" (số đầu tiên chỉ chứa chữ số 9 và 0)

        while (!q.empty()) {       // Lặp cho đến khi hàng đợi trống
            string ht = q.front(); // Lấy phần tử đầu hàng đợi
            q.pop();               // Xóa phần tử đầu khỏi hàng đợi

            long long sht = stoll(ht); // Chuyển đổi chuỗi sang số nguyên kiểu long long

            if (sht % N == 0) {    // Nếu số hiện tại chia hết cho N
                cout << sht << endl;   // In ra kết quả
                break;                 // Dừng vòng lặp vì đã tìm được số thỏa mãn
            } else {
                // Nếu không chia hết, thêm vào hàng đợi hai chuỗi mới bằng cách nối thêm '0' và '9'
                q.push(ht + '0');
                q.push(ht + '9');
            }
        }
    }
}
