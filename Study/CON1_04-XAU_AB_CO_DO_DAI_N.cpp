#include <iostream>
#include <string>
#include <vector> // Thư viện vector (không cần thiết trong bài này nhưng có thể dùng nếu cần)
using namespace std; // Sử dụng toàn bộ không gian tên std

// Hàm đệ quy để sinh và in ra các xâu nhị phân
void generateStrings(int n, string current_string) {
    // Trường hợp cơ sở: Nếu xâu hiện tại đã đạt độ dài yêu cầu
    if (current_string.length() == n) {
        cout << current_string << " "; // In ra xâu hoàn chỉnh và một khoảng trắng
        return;
    }
    // Bước đệ quy: Thêm ký tự 'A' vào xâu và tiếp tục
    generateStrings(n, current_string + 'A');
    // Bước đệ quy: Thêm ký tự 'B' vào xâu và tiếp tục
    generateStrings(n, current_string + 'B');
}

int main() {
    ios_base::sync_with_stdio(false); // Tăng tốc độ nhập/xuất
    cin.tie(NULL); // Tắt đồng bộ hóa giữa cin và cout
    int T; // Số lượng bộ test
    cin >> T; // Nhập số lượng bộ test
    while (T--) { // Lặp qua từng bộ test
        int n; // Độ dài của xâu cần sinh
        cin >> n; // Nhập độ dài xâu
        // Bắt đầu sinh xâu nhị phân với xâu rỗng ban đầu
        generateStrings(n, "");
        // In xuống dòng sau khi in xong tất cả các xâu của bộ test hiện tại
        cout << endl;
    }
    return 0; // Kết thúc chương trình
}