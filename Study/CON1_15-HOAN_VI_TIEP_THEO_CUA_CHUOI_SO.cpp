#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int test_case = 1; test_case <= t; test_case++) {
        int stt;
        cin >> stt;
        string s;
        cin >> s;
        // Sử dụng hàm next_permutation để tìm hoán vị kế tiếp của chuỗi s
        if (next_permutation(s.begin(), s.end())) {
            cout << test_case << " " << s << endl;
        } else {
            cout << test_case << " BIGGEST" << endl;
        }
    }
    return 0;
}