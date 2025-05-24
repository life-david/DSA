#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> A(n), B(m);
        for (int i = 0; i < n; ++i)
            cin >> A[i];
        for (int i = 0; i < m; ++i)
            cin >> B[i];
        int maxA = A[0];
        for (int i = 1; i < n; ++i)
        {
            if (A[i] > maxA)
                maxA = A[i];
        }
        int minB = B[0];
        for (int i = 1; i < m; ++i)
        {
            if (B[i] < minB)
                minB = B[i];
        }
        cout << maxA * minB << endl;
    }
    return 0;
}
