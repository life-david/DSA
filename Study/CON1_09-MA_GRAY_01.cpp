#include <bits/stdc++.h>
using namespace std;

vector<string> gray(int n)
{
    if (n == 1)
        return {"0", "1"};
    vector<string> prev = gray(n - 1), res;
    for (string x : prev)
        res.push_back("0" + x);
    reverse(prev.begin(), prev.end());
    for (string x : prev)
        res.push_back("1" + x);
    return res;
}

int main()
{
    int T, n;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (string s : gray(n))
            cout << s << " ";
        cout << "\n";
    }
}
