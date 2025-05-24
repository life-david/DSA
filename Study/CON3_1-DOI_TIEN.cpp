#include <bits/stdc++.h>
using namespace std;

int A[10] = {1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};

int doitien(int N)
{
    int dem = 0;
    for (int i = 0; i < 10; i++)
    {
        while (N >= A[i])
        {
            N -= A[i];
            dem++;
        }
        if (N <= 0)
            break;
    }
    return dem;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;
        cout << doitien(N) << endl;
    }

    return 0;
}
