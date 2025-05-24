#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD = 1e9 + 7;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string a, b;
        cin >> a >> b;
        int s1 = a.size();    // Độ dài chuỗi `a`
        int s2 = b.size();    // Độ dài chuỗi `b`
        int atp = 0, btp = 0; // Biến lưu giá trị thập phân của `a` và `b`

        // Chuyển đổi chuỗi nhị phân `a` sang số thập phân
        for (int i = s1 - 1; i >= 0; i--)
        {
            atp = atp + (a[i] - '0') * pow(2, s1 - i - 1); // `a[i] - '0'` chuyển ký tự thành số nguyên
        }

        // Chuyển đổi chuỗi nhị phân `b` sang số thập phân
        for (int i = s2 - 1; i >= 0; i--)
        {
            btp = btp + (b[i] - '0') * pow(2, s2 - i - 1);
        }

        cout << atp * btp << endl;
    }
    return 0;
}