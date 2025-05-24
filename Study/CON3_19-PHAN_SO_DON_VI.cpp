#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;

void Test()
{
    long long p, q;
    cin >> p >> q;
    while (1)
    {
        if (q % p == 0)
        {
            cout << "1/" << q / p;
            return;
        }

        long long x = q / p + 1;
        cout << "1/" << x << " + ";
        p = p * x - q;
        q *= x;
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        Test();
        cout << endl;
    }
    return 0;
}