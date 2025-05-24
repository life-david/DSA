#include <bits/stdc++.h>
using namespace std;
int dem_duong(int i, int j, int M, int N)
{
    if (i == M - 1 && j == N - 1)
        return 1;
    if (i >= M || j >= N)
        return 0;
    return dem_duong(i + 1, j, M, N) + dem_duong(i, j + 1, M, N);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int M, N;
        cin >> M >> N;
        int A[100][100];
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> A[i][j];
            }
        }
        cout << dem_duong(0, 0, M, N) << endl;
    }
    return 0;
}