#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; i++)
        {
            cin >> A[i];
        }
        sort(A.begin(), A.end());
        for (int i = 0; i < N; i++)
        {
            cout << A[i] << " ";
        }
        cout << endl
    }
    return 0;
}
