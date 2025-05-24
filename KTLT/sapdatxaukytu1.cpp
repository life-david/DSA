#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool canRearrange(const string& s) {
    int freq[26] = {0};
    int n = s.length();

    for (char c : s) {
        freq[c - 'a']++;
    }

    int maxFreq = *max_element(freq, freq + 26);

    
    return maxFreq <= (n + 1) / 2;
}

int main() {
    int T;
    cin >> T;
    cin.ignore(); 

    while (T--) {
        string s;
        getline(cin, s);
        cout << (canRearrange(s) ? 1 : -1) << endl;
    }

    return 0;
}
