#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t; // Số lượng bộ test
    while (t--) {
        int M, N;
        cin >> M >> N; // Số hàng M và số cột N của ma trận

        // Đọc ma trận (mặc dù ma trận không cần thiết cho việc tính số đường đi)
        vector<vector<int>> A(M, vector<int>(N));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> A[i][j];
            }
        }

        // Tạo mảng DP để lưu trữ số đường đi đến từng ô
        vector<vector<long long>> dp(M, vector<long long>(N, 0));

        // Số đường đi đến A[0][0] là 1 (bắt đầu tại đây)
        dp[0][0] = 1;

        // Cập nhật giá trị cho hàng đầu tiên và cột đầu tiên
        for (int i = 1; i < M; ++i) dp[i][0] = 1;  // Chỉ có thể đi xuống dưới
        for (int j = 1; j < N; ++j) dp[0][j] = 1;  // Chỉ có thể đi sang phải

        // Cập nhật các ô còn lại bằng công thức DP
        for (int i = 1; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];  // Di chuyển từ trên hoặc từ trái
            }
        }

        // Số cách di chuyển đến A[M-1][N-1]
        cout << dp[M-1][N-1] << endl;
    }

    return 0;
}
