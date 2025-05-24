#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        sort(a.begin(), a.end()); // sắp xếp lại mảng
        // chia ra 2 số
        long long s1 = 0, s2 = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i % 2 == 0) // số chẵn thì cho vào s1
                s1 = s1 * 10 + a[i];
            else
                s2 = s2 * 10 + a[i];
        }
        cout << s1 + s2 << '\n';
    }
    return 0;
}
