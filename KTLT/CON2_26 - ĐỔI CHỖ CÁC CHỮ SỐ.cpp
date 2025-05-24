#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD = 1e9 + 7;
string timMax(string S, int K) {
    int n = S.length();
    for (int i = 0; i < n && K > 0; i++) {
        char max = S[i]; // Giả sử ký tự lớn nhất là ký tự hiện tại
        int vitri = i; // Lưu vị trí của ký tự lớn nhất
        
        // Tìm ký tự lớn nhất từ vị trí i đến cuối chuỗi
        for (int j = i + 1; j < n; j++) {
            if (S[j] >= max) { // Nếu tìm thấy ký tự lớn hơn hoặc bằng
                max = S[j]; // Cập nhật ký tự lớn nhất
                vitri = j; // Cập nhật vị trí của ký tự lớn nhất
            }
        }
        // Nếu vị trí của ký tự lớn nhất khác với vị trí hiện tại
        if (vitri != i) {
            swap(S[i], S[vitri]); // Hoán đổi ký tự tại vị trí i với ký tự lớn nhất
            K--; // Giảm số lần hoán đổi còn lại
        }
    }
    return S; 
}

int main() {
    int t; 
    cin >> t; 
    while (t--) { 
        string S;
        int K; 
        cin >> K >> S;
        string res = timMax(S, K);
        cout << res << endl;
    }
    return 0;
}