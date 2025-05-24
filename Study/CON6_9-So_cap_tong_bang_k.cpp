#include <iostream>
#include <unordered_map>
using namespace std;
int countPairs(int A[], int n, int k)
{
    unordered_map<int, int> freq;
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        int complement = k - A[i];
        if (freq[complement] > 0)
        {
            count += freq[complement];
        }
        freq[A[i]]++;
    }
    return count;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, k;
        cin >> n >> k;
        int A[100];
        for (int i = 0; i < n; ++i)
        {
            cin >> A[i];
        }
        cout << countPairs(A, n, k) << endl;
    }
    return 0;
}
