#include <bits/stdc++.h>
using namespace std;
void testCase()
{
    int n;
    cin >> n;
    vector<int> f(n + 1, 0); // f[i] lưu số lượng số bình phương nhỏ nhất để tổng thành i
    for (int i = 1; i <= n; ++i)
    {
        f[i] = i; // Khởi tạo: mỗi số đều có thể được tạo thành từ i số 1^2
        for (int j = 1; j <= sqrt(i); ++j)
        {
            // Thử tất cả các số bình phương nhỏ hơn hoặc bằng i
            f[i] = min(f[i], f[i - j * j] + 1); // Cập nhật giá trị nhỏ nhất
        }
    }
    cout << f[n]; // In ra kết quả là số lượng số bình phương ít nhất để tổng thành n
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