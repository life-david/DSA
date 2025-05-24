#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int k;
        string s;
        cin >> k >> s;
        
        // Đếm tần suất của các ký tự trong xâu
        unordered_map<char, int> freq;
        for (char c : s) {
            freq[c]++;
        }

        // Sắp xếp các tần suất theo thứ tự giảm dần
        priority_queue<int> pq;
        for (auto& p : freq) {
            pq.push(p.second);
        }

        // Loại bỏ k ký tự có tần suất cao nhất
        while (k > 0 && !pq.empty()) {
            int top = pq.top(); pq.pop();
            if (top > 1) {
                pq.push(top - 1);
            }
            k--;
        }

        // Tính tổng bình phương các tần suất còn lại
        int result = 0;
        while (!pq.empty()) {
            int top = pq.top(); pq.pop();
            result += top * top;
        }

        cout << result << endl;
    }

    return 0;
}
