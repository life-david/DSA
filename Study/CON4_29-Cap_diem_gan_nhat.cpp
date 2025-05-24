#include <bits/stdc++.h>
using namespace std;
double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        double ans = 1e9;
        double x1, y1, x2, y2;
        vector<double> x(n), y(n);
        for (int i = 0; i < n; i++)
        {
            cin >> x[i] >> y[i];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                ans = min(ans, distance(x[i], y[i], x[j], y[j]));
            }
        }
        cout << fixed << setprecision(6) << ans << "\n";
    }
    return 0;
}