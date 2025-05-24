#include <bits/stdc++.h>
using namespace std;
void testCase()
{
    int s, d;
    cin >> s >> d;
    if (s > 9 * d)
    {
        cout << -1; // Nếu tổng chữ số lớn hơn giá trị lớn nhất có thể tạo ra với d chữ số, in -1
        return;
    }
    int a[d] = {1}; // Khởi tạo mảng chữ số, chữ số đầu tiên là 1 để đảm bảo số không có số 0 ở đầu
    s--;            // Trừ đi 1 vì đã gán 1 cho chữ số đầu tiên (tức là đang xét tổng còn lại)
    // Phân phối tổng còn lại cho các chữ số từ cuối về đầu để số nhỏ nhất
    for (int i = d - 1; i >= 0; --i)
    {
        int x = min(s, 9 - a[i]); // Số lớn nhất có thể cộng thêm vào vị trí này mà không vượt quá 9
        a[i] += x;                // Cộng thêm vào chữ số hiện tại
        s -= x;                   // Giảm tổng còn lại
    }
    for (int i = 0; i < d; ++i)
    {
        cout << a[i]; // In ra số nhỏ nhất tìm được
    }
}

int main()
{
    int T = 1;
    cin >> T;
    while (T--)
    {
        testCase();
        cout << "\n";
    }
    return 0;
}