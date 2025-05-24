#include <bits/stdc++.h> // Thư viện tổng hợp
using namespace std;

int main() {
	int t;
	cin >> t; // Nhập số lượng test case

	while (t--) {
		queue<string> q; // Khởi tạo một hàng đợi lưu chuỗi nhị phân
		q.push("1");     // Bắt đầu với chuỗi đầu tiên là "1"

		int n;
		cin >> n; // Nhập số lượng chuỗi nhị phân cần in

		while (n--) {
			string s = q.front(); // Lấy chuỗi đầu tiên trong hàng đợi
			q.pop();              // Xoá chuỗi đó khỏi hàng đợi

			cout << s << " ";     // In ra chuỗi nhị phân hiện tại

			// Thêm hai chuỗi nhị phân tiếp theo vào hàng đợi
			q.push(s + "0");
			q.push(s + "1");
		}
		cout << endl; // Xuống dòng sau mỗi test case
	}
	return 0;
}
