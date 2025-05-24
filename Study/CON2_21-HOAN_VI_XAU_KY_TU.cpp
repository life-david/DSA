#include <bits/stdc++.h>
using namespace std;
string s;
int a[1000], dd[1000] = {}; // a[] lưu chỉ số ký tự, dd[] đánh dấu đã dùng ký tự nào

void Try(int n)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (!dd[i]) // Nếu ký tự thứ i chưa được dùng
        {
            a[n] = i;              // Gán vị trí n của hoán vị là ký tự thứ i
            dd[i] = 1;             // Đánh dấu đã dùng ký tự thứ i
            if (n == s.size() - 1) // Nếu đã chọn đủ số ký tự
            {
                for (int i = 0; i < s.size(); i++)
                {
                    cout << s[a[i]]; // In ra một hoán vị
                }
                cout << " ";
            }
            else
            {
                Try(n + 1); // Đệ quy chọn ký tự tiếp theo
            }
            dd[i] = 0; // Bỏ đánh dấu để thử các trường hợp khác (quay lui)
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> s;
        Try(0);
        cout << "\n";
    }
}