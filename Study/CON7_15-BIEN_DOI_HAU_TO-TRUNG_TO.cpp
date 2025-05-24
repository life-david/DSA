#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;  // Nhập số lượng test case

	while(t--){
		string s;
		cin >> s;  // Nhập biểu thức hậu tố (postfix)
		stack<string> st;

		// Duyệt từng ký tự trong biểu thức hậu tố
		for(int i = 0; i < s.size(); i++){
			if(isalnum(s[i])){ // Nếu là ký tự chữ hoặc số (toán hạng)
				st.push(string(1, s[i]));  // Đưa vào stack dưới dạng chuỗi
			}
			else{ // Nếu là toán tử (+, -, *, /, ...)
				string op2 = st.top(); st.pop();  // Toán hạng 2
				string op1 = st.top(); st.pop();  // Toán hạng 1
				string tmp = "(" + op1 + s[i] + op2 + ")";  // Tạo biểu thức trung tố
				st.push(tmp);  // Đưa kết quả vào lại stack
			}
		}

		// Kết quả cuối cùng là biểu thức trung tố với đầy đủ dấu ngoặc
		cout << st.top() << endl;
	}
	return 0;
}
