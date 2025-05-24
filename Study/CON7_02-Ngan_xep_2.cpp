#include <bits/stdc++.h>
using namespace std;

int main() {
    stack<int> stk; // Khai báo một ngăn xếp (stack) để lưu trữ các số nguyên
    int t;
    cin >> t;

    while (t > 0) {
        string s;
        cin >> s;
        t--; 

        if (s == "PUSH") { // Nếu lệnh là "PUSH"
            int n; // Biến lưu giá trị cần đẩy vào ngăn xếp
            cin >> n; // Nhập giá trị
            stk.push(n); // Đẩy giá trị vào ngăn xếp
        } 
        else if (s == "POP") { // Nếu lệnh là "POP"
            if (!stk.empty()) { // Kiểm tra nếu ngăn xếp không rỗng
                stk.pop(); // Loại bỏ phần tử trên cùng của ngăn xếp
            }
        } 
        else if (s == "PRINT") { // Nếu lệnh là "PRINT"
            if (!stk.empty()) { // Kiểm tra nếu ngăn xếp không rỗng
                cout << stk.top() << endl; // In ra phần tử trên cùng của ngăn xếp
            } else {
                cout << "NONE" << endl; // In "NONE" nếu ngăn xếp rỗng
            }
        }
    }

    return 0;
}
