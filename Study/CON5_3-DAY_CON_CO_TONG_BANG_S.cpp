#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k; // `n` là số lượng phần tử trong mảng, `k` là tổng cần kiểm tra
        cin >> n >> k; // Nhập `n` và `k`
        int a[n + 5], l[k + 5] = {}; // Mảng `a` lưu các phần tử, mảng `l` dùng để đánh dấu các tổng có thể đạt được
        for (int i = 1; i <= n; i++) // Nhập các phần tử của mảng `a`
            cin >> a[i];
        l[0] = 1; // Khởi tạo: tổng bằng 0 luôn có thể đạt được

        // Duyệt qua từng phần tử của mảng
        for (int i = 1; i <= n; i++)
        {
            // Duyệt ngược từ `k` về `a[i]` để kiểm tra các tổng có thể đạt được
            for (int j = k; j >= a[i]; j--)
            {
                // Nếu tổng `j` chưa đạt được (`l[j] == 0`) và tổng `j - a[i]` đã đạt được (`l[j - a[i]] == 1`)
                if (l[j] == 0 && l[j - a[i]] == 1)
                    l[j] = 1; // Đánh dấu tổng `j` có thể đạt được
            }
        }

        // Kiểm tra nếu tổng `k` có thể đạt được
        if (l[k] == 1)
            cout << "YES" << endl; // In "YES" nếu có dãy con có tổng bằng `k`
        else
            cout << "NO" << endl; // In "NO" nếu không có dãy con nào có tổng bằng `k`
    }
}