#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> A(n);
        for (int i = 0; i < n; i++)
        {
            cin >> A[i]; // Nhập mảng A gồm n phần tử
        }

        // Sắp xếp mảng A tăng dần
        sort(A.begin(), A.end());

        // Tính tổng k phần tử nhỏ nhất và phần còn lại
        int sum1 = accumulate(A.begin(), A.begin() + k, 0); // tổng k phần tử đầu tiên (nhỏ nhất)
        int sum2 = accumulate(A.begin() + k, A.end(), 0);   // tổng phần còn lại

        // Tính tổng k phần tử lớn nhất và phần còn lại
        int sum3 = accumulate(A.begin(), A.begin() + (n - k), 0); // tổng n-k phần tử đầu tiên
        int sum4 = accumulate(A.begin() + (n - k), A.end(), 0);   // tổng k phần tử cuối (lớn nhất)

        // Xuất ra giá trị lớn nhất của hai cách chia tổng
        cout << max(abs(sum2 - sum1), abs(sum4 - sum3)) << endl;
    }

    return 0;
}
