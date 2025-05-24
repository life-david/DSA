#include <bits/stdc++.h>
#define endl "\n"
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t; // Nhập số lượng test case

    while (t--)
    {
        int n, s, m;
        cin >> n >> s >> m; // n: số lượng mua tối đa mỗi ngày
                            // s: số ngày cần sống
                            // m: số lương thực cần dùng mỗi ngày

        // Tính tổng lượng lương thực cần để sống S ngày
        int totalFoodNeeded = s * m;

        // Tính số ngày có thể đi mua (trừ Chủ nhật)
        int buyingDays = s - s / 7;

        // Tính tổng lượng lương thực tối đa có thể mua được
        int totalFoodCanBuy = buyingDays * n;

        // Nếu không thể mua đủ lương thực → chết đói
        if (totalFoodNeeded > totalFoodCanBuy)
            cout << -1 << endl;
        else
        {
            // Tìm số ngày ít nhất cần đi mua để đủ sống
            for (int i = 1; i <= buyingDays; i++)
            {
                if (n * i >= totalFoodNeeded)
                {
                    cout << i << '\n'; // In ra số ngày mua tối thiểu
                    break;
                }
            }
        }
    }
}
