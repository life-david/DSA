#include <bits/stdc++.h> // Thư viện chuẩn bao gồm tất cả các thư viện cần thiết
using namespace std;

int n, m;              // `n` là số đỉnh, `m` là số cạnh của đồ thị
vector<int> adj[1001]; // Danh sách kề để lưu đồ thị (tối đa 1000 đỉnh)
bool visited[1001];    // Mảng đánh dấu các đỉnh đã được thăm

// Hàm nhập dữ liệu đồ thị
void input()
{
    for (int i = 1; i <= n; i++)
    {
        adj[i].clear(); // Xoá danh sách kề của các đỉnh
    }
    memset(visited, 0, sizeof(visited)); // Đặt tất cả các đỉnh chưa được thăm

    for (int i = 0; i < m; i++)
    {                        // Lặp qua từng cạnh
        int x, y;            // `x` là đỉnh đầu, `y` là đỉnh cuối
        cin >> x >> y;       // Nhập cạnh giữa hai đỉnh `x` và `y`
        adj[x].push_back(y); // Thêm `y` vào danh sách kề của `x`
        // adj[y].push_back(x); // Thêm `x` vào danh sách kề của `y` (nếu đồ thị vô hướng)
    }
}

// Hàm duyệt đồ thị theo chiều sâu (DFS)
void DFS(int u)
{
    visited[u] = true; // Đánh dấu đỉnh `u` đã được thăm
    cout << u << " ";  // In ra đỉnh vừa được duyệt
    for (int x : adj[u])
    { // Duyệt qua các đỉnh kề của `u`
        if (!visited[x])
        {           // Nếu đỉnh `x` chưa được thăm
            DFS(x); // Gọi đệ quy để duyệt tiếp từ đỉnh `x`
        }
    }
}

int main()
{
    int t;    // Số lượng bộ test
    cin >> t; // Nhập số lượng bộ test
    while (t--)
    {                       // Lặp qua từng bộ test
        int u;              // Đỉnh bắt đầu duyệt DFS
        cin >> n >> m >> u; // Nhập số đỉnh, số cạnh và đỉnh bắt đầu
        input();            // Gọi hàm nhập dữ liệu đồ thị
        DFS(u);             // Gọi hàm DFS để duyệt đồ thị từ đỉnh `u`
        cout << endl;       // Xuống dòng sau khi duyệt xong
    }
}
