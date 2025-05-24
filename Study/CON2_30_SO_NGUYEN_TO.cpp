#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int S, P, N;
vector<int> primes, current, result_count;
vector<vector<int>> results;

bool is_prime(int x)
{
    if (x < 2)
        return false;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    return true;
}

void backtrack(int index, int sum, int count)
{
    if (sum > S || count > N)
        return;
    if (sum == S && count == N)
    {
        results.push_back(current);
        return;
    }
    for (int i = index; i < primes.size(); ++i)
    {
        current.push_back(primes[i]);
        backtrack(i + 1, sum + primes[i], count + 1);
        current.pop_back();
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> N >> P >> S;
        // Khởi tạo lại cho mỗi test
        primes.clear();
        current.clear();
        results.clear();

        for (int i = P + 1; i <= S; ++i)
            if (is_prime(i))
                primes.push_back(i);

        backtrack(0, 0, 0);

        // In kết quả
        cout << results.size() << endl;
        sort(results.begin(), results.end());
        for (auto &res : results)
        {
            for (int val : res)
                cout << val << " ";
            cout << endl;
        }
    }
    return 0;
}
